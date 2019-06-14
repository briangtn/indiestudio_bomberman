/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** AISystem
*/

#include "systems/AISystem.hpp"
#include "components/AIController.hpp"
#include "events/IrrlichtAnimationEndEvent.hpp"
#include "ECSWrapper.hpp"
#include "ai/AiView.hpp"
#include "components/Transform.hpp"
#include "components/PlayerController.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include "components/MoveToTarget.hpp"
#include "components/Bomb.hpp"
#include "components/BoxCollider.hpp"

indie::systems::AISystem::AISystem() : _timePassed(0)
{
}

indie::systems::AISystem::~AISystem()
{
}

void indie::systems::AISystem::onAwake()
{

}

void indie::systems::AISystem::onStart()
{

}

void indie::systems::AISystem::onStop()
{

}

void indie::systems::AISystem::onTearDown()
{

}

void indie::systems::AISystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    _timePassed += elapsedTime.count();

    ECSWrapper ecs;
    ecs.entityManager.applyToEach<components::AIController>(&AILogic);
    if (_timePassed >= 500000000) {
        _timePassed -= 500000000;
    }
}

int indie::systems::AISystem::getTimePassed() const
{
    return _timePassed;
}

void indie::systems::AISystem::setTimePassed(int assign)
{
    _timePassed = assign;
}

bool indie::systems::AISystem::hasMoved(jf::entities::EntityHandler entity, 
    jf::components::ComponentHandler<indie::components::AIController> component)
{
    if (static_cast<int>(entity->getComponent<indie::components::Transform>()->getPosition().x) / 10 != component->getPreviousPos().first || 
    static_cast<int>(entity->getComponent<indie::components::Transform>()->getPosition().z) / 10 != component->getPreviousPos().second )
        return (true);
    return (false);
}

void indie::systems::AISystem::AILogic(jf::entities::EntityHandler entity,
    jf::components::ComponentHandler<indie::components::AIController> component)
{
    ECSWrapper ecs;
    if (ecs.systemManager.getSystem<indie::systems::AISystem>().getTimePassed() < 500000000 && !hasMoved(entity, component))
        return;
    component->setPreviousPos(std::pair<int, int>(static_cast<int>(entity->getComponent<indie::components::Transform>()->getPosition().x) / 10
                            ,static_cast<int>(entity->getComponent<indie::components::Transform>()->getPosition().z) *-1 / 10));

    maths::Vector3D playerPos = entity->getComponent<indie::components::Transform>()->getPosition();
    jf::components::ComponentHandler<indie::components::MoveToTarget> moveComp = entity->getComponent<indie::components::MoveToTarget>();

    auto bonuses = ecs.entityManager.getEntitiesWith<indie::components::BonusEffector>();
    std::sort(bonuses.begin(), bonuses.end(), [&playerPos](jf::entities::EntityHandler bonusA, jf::entities::EntityHandler bonusB){
        return (bonusA->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 
(bonusB->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq();
    });
    auto players = ecs.entityManager.getEntitiesWith<indie::components::AIController, indie::components::PlayerController>();
    std::sort(players.begin(), players.end(), [&playerPos](jf::entities::EntityHandler playerA, jf::entities::EntityHandler playerB){
        return (playerA->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 
(playerB->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq();
    });
    auto bombs = ecs.entityManager.getEntitiesWith<indie::components::Bomb>();
    std::sort(bombs.begin(), bombs.end(), [&playerPos](jf::entities::EntityHandler bombA, jf::entities::EntityHandler bombB){
        return (bombA->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 
(bombB->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq();
    });

    component->setLastState(component->getState());
    chooseState(component, entity, bonuses, players, bombs);
    if (component->getIsTaunting() == false && component->getIsPlacingBomb() == false)
        moveComp->setFollowTarget(true);

    switch (component->getState()) {
        case indie::components::AIController::SURVIVE : surviveLogic(component, entity);
        case indie::components::AIController::FOCUS : focusLogic();
        case indie::components::AIController::TAUNT : tauntLogic(component);
        case indie::components::AIController::POWERUP : powerupLogic(component, bonuses[0], entity);
        case indie::components::AIController::SEARCH : searchLogic();
    }
    if (component->getIsTaunting() || component->getIsPlacingBomb())
        moveComp->setFollowTarget(false);
}

void indie::systems::AISystem::focusLogic()
{
}

void indie::systems::AISystem::tauntLogic(jf::components::ComponentHandler<indie::components::AIController> &component)
{
    component->setNeedToTaunt(true);
}

void indie::systems::AISystem::askNewTarget(jf::components::ComponentHandler<indie::components::AIController> &component, 
                                             const indie::maths::Vector3D &target, jf::entities::EntityHandler entity)
{
    jf::components::ComponentHandler<indie::components::MoveToTarget> moveComp = entity->getComponent<indie::components::MoveToTarget>();
    moveComp->setSpeed(component->getMovementSpeed());
    moveComp->setTarget(target);
    component->setHasTarget(true);
}

std::pair<bool, std::pair<int, int>> indie::systems::AISystem::determineSafeCell(ai::AIView::AICellViewGrid &grid, jf::entities::EntityHandler &entity)
{
    std::pair<bool, std::pair<int, int>> res = {true, {0, 0}};
    std::vector<std::pair<int, int>> potentialSafeCell;
    ai::AStar::Node::position playerPos = ai::get2DPositionFromWorldPos(entity->getComponent<indie::components::Transform>()->getPosition());

    int xMin = playerPos.x - 3 < 0 ? 0 : playerPos.x - 3;
    int xMax = playerPos.x + 3 > 14 ? 14 : playerPos.x + 3;
    int yMin = playerPos.y - 3 < 0 ? 0 : playerPos.y - 3;
    int yMax = playerPos.y + 3 > 14 ? 14 : playerPos.y + 3;

    for (int i = yMin; i < yMax; i++) {
        for (int a = xMin; a < xMax; a++) {
            if (!(grid[i][a] & ai::AIView::AI_CELL_BLAST)) {
                if (!(entity->getComponent<indie::components::BoxCollider>()->getLayer() & BREAKABLE_BLOCK_LAYER)) { //j'ai le wall pass
                    potentialSafeCell.emplace_back(i, a);
                } else if (!(grid[i][a] & ai::AIView::AI_CELL_TYPE_BREAKABLE_WALL) && !(grid[i][a] & ai::AIView::AI_CELL_TYPE_UNBREAKABLE_WALL) /* && noCrates */) {
                    potentialSafeCell.emplace_back(i, a);
                }
            }
        }
    }
    //sort
    if (potentialSafeCell.empty()) {
        res.first = false;
        return (res);
    }
    res.second.first = potentialSafeCell[0].first;
    res.second.second = potentialSafeCell[0].second;
    return (res);
}

void indie::systems::AISystem::surviveLogic(jf::components::ComponentHandler<indie::components::AIController> &component,
                                            jf::entities::EntityHandler &entity)
{
    ai::AIView::AICellViewGrid grid = ai::AIView::getViewGrid();
    if (component->getState() != component->getLastState() || !component->getHasTarget()) {
        std::pair<bool, std::pair<int, int>> res = determineSafeCell(grid, entity);
        maths::Vector3D target(res.second.first == 0 ? 0 : res.second.first + 10, -5, res.second.second == 0 ? 0 : res.second.second * -1 + 10);
        if (res.first == true)
            askNewTarget(component, target, entity);
        else {
            //Bombs
            tauntLogic(component);
        }
    }
}

void indie::systems::AISystem::powerupLogic(jf::components::ComponentHandler<indie::components::AIController> &component,
                                            jf::entities::EntityHandler &bonuses, jf::entities::EntityHandler &entity)
{
    component->setFullNodePath(ai::AStar::findPath(ai::AIView::getViewGrid(), ai::get2DPositionFromWorldPos(entity->getComponent<indie::components::Transform>()->getPosition()), 
ai::get2DPositionFromWorldPos(bonuses->getComponent<indie::components::Transform>()->getPosition())));
    if (component->getState() != component->getLastState() || !component->getHasTarget())
        askNewTarget(component, bonuses->getComponent<indie::components::Transform>()->getPosition(), entity);
}

void indie::systems::AISystem::searchLogic()
{

}

void indie::systems::AISystem::chooseState(jf::components::ComponentHandler<indie::components::AIController> &component,
jf::entities::EntityHandler &entity,
std::vector<jf::entities::EntityHandler> &bonuses,
std::vector<jf::entities::EntityHandler> &players,
std::vector<jf::entities::EntityHandler> &bombs)
{
    ECSWrapper ecs;
    indie::components::AIController::state state = indie::components::AIController::UNKNOWN;
    ai::AIView::AICellViewGrid grid = ai::AIView::getViewGrid();
    maths::Vector3D playerPos = entity->getComponent<indie::components::Transform>()->getPosition();
    indie::ai::AIView::AICellViewGrid map = ai::AIView::getViewGrid();

    if (!bombs.empty() && inDanger(map, playerPos))
        state = indie::components::AIController::SURVIVE;
    else if (!bonuses.empty() && (bonuses.front()->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 900)
        state = indie::components::AIController::POWERUP;
    /*else if (!players.empty() && (players.front()->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 900)
        state = indie::components::AIController::FOCUS;
    else if (!bonuses.empty() && (bonuses.front()->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 3600)
        state = indie::components::AIController::POWERUP;
    else if (!players.empty() && (players.front()->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 3600)
        state = indie::components::AIController::FOCUS;
    else
        state = indie::components::AIController::SEARCH;

    if (component->getState() != indie::components::AIController::POWERUP);
        randomHandling(state, bonuses, players);*/
    component->setState(state);
}

bool indie::systems::AISystem::inDanger(indie::ai::AIView::AICellViewGrid &map, maths::Vector3D &playerPos)
{
    indie::ai::AStar::Node::position pos = ai::get2DPositionFromWorldPos(playerPos);
    if (map[pos.y][pos.x] & ai::AIView::AI_CELL_BLAST)
        return (true);
    return (false);
}

void indie::systems::AISystem::randomHandling(indie::components::AIController::state &state, 
std::vector<jf::entities::EntityHandler> bonuses, 
std::vector<jf::entities::EntityHandler> players)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 100);
    int number = distribution(generator);

    if (number == 42)
        state = indie::components::AIController::TAUNT;
    else if (state == indie::components::AIController::SURVIVE && number <= 5) {
        if (!bonuses.empty())
            state = indie::components::AIController::POWERUP;
    } else if (state == indie::components::AIController::POWERUP && number <= 35) {
        if (!players.empty())
            state = indie::components::AIController::FOCUS;
    }

}