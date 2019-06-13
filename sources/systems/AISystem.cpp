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
    ecs.systemManager.getSystem<indie::systems::AISystem>().setTimePassed(0);

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
                                             jf::entities::EntityHandler &target, jf::entities::EntityHandler entity)
{
    jf::components::ComponentHandler<indie::components::MoveToTarget> moveComp = entity->getComponent<indie::components::MoveToTarget>();
    moveComp->setSpeed(component->getMovementSpeed());
    moveComp->setTarget(target->getComponent<indie::components::Transform>()->getPosition());
    component->setHasTarget(true);
}

void indie::systems::AISystem::powerupLogic(jf::components::ComponentHandler<indie::components::AIController> &component,
                                            jf::entities::EntityHandler &bonuses, jf::entities::EntityHandler &entity)
{
    component->setFullNodePath(ai::AStar::findPath(ai::AIView::getViewGrid(), ai::get2DPositionFromWorldPos(entity->getComponent<indie::components::Transform>()->getPosition()), 
ai::get2DPositionFromWorldPos(bonuses->getComponent<indie::components::Transform>()->getPosition())));
    if (component->getState() != component->getLastState() || !component->getHasTarget())
        askNewTarget(component, bonuses, entity);
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

    //bomb first; with SURVIVE STATE;
    /*
    if (!bombs.empty() && indanger())
        state = indie::components::AIController::SURVIVE;
    */
    /*if (!bonuses.empty() && (bonuses.front()->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 900)
        state = indie::components::AIController::POWERUP;
    else if (!players.empty() && (players.front()->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 900)
        state = indie::components::AIController::FOCUS;
    else if (!bonuses.empty() && (bonuses.front()->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 3600)
        state = indie::components::AIController::POWERUP;
    else if (!players.empty() && (players.front()->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 3600)
        state = indie::components::AIController::FOCUS;
    else
        state = indie::components::AIController::SEARCH;

    if (component->getState() != indie::components::AIController::POWERUP);
        randomHandling(state, bonuses, players);*/
    //component->setState(state);
    if (!bonuses.empty())
        component->setState(indie::components::AIController::POWERUP);
    else
        component->setState(indie::components::AIController::UNKNOWN);
}

std::pair<bool, std::vector<int>> indie::systems::AISystem::inDanger()
{

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