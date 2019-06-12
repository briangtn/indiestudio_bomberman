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
    if (_timePassed < 500000000)
        return;
    _timePassed = 0;

    ECSWrapper ecs;
    ecs.entityManager.applyToEach<components::AIController>(&AILogic);
}

void indie::systems::AISystem::AILogic(jf::entities::EntityHandler entity,
    jf::components::ComponentHandler<indie::components::AIController> component)
{
    chooseState(component, entity);
    //TO DO MOVE JULIAN OK IF COMponent->getisTaunting() == false

    switch (component->getState()) {
        case indie::components::AIController::FOCUS : focusLogic();
        case indie::components::AIController::TAUNT : tauntLogic(component);
        case indie::components::AIController::POWERUP : powerupLogic();
        case indie::components::AIController::SEARCH : searchLogic();
    }
    if (component->getIsTaunting())
        return;
        //TODO DON T MOVE TO JULIAN MOVER
}

void indie::systems::AISystem::focusLogic()
{

}

void indie::systems::AISystem::tauntLogic(jf::components::ComponentHandler<indie::components::AIController> &component)
{
    component->setNeedToTaunt(true);
}

void indie::systems::AISystem::powerupLogic()
{

}

void indie::systems::AISystem::searchLogic()
{

}

void indie::systems::AISystem::chooseState(jf::components::ComponentHandler<indie::components::AIController> &component,
jf::entities::EntityHandler &entity)
{
    ECSWrapper ecs;
    indie::components::AIController::state state = indie::components::AIController::UNKNOWN;
    ai::AIView::AICellViewGrid grid = ai::AIView::getViewGrid();
    maths::Vector3D playerPos = entity->getComponent<indie::components::Transform>()->getPosition();

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
    //get bomb pos;

    //bomb first; with SURVIVE STATE;
    /*
    if (!bombs.empty() && indanger())
        state = indie::components::AIController::SURVIVE;
    */
    if (!bonuses.empty() && (bonuses.front()->getComponent<components::Transform>()->getPosition() - playerPos).magnitudeSq() < 900)
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
        randomHandling(state, bonuses, players);
    component->setState(state);
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