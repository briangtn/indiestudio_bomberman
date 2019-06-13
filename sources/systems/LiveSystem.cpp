/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** LiveSystem.cpp
*/

/* Created the 13/06/2019 at 10:07 by jfrabel */

#include "systems/LiveSystem.hpp"
#include "ECSWrapper.hpp"
#include "components/PlayerAlive.hpp"

indie::systems::LiveSystem::LiveSystem()
    : _elapsedTime(0)
{

}

indie::systems::LiveSystem::~LiveSystem()
{

}

void indie::systems::LiveSystem::onAwake()
{

}

void indie::systems::LiveSystem::onStart()
{

}

void indie::systems::LiveSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    float elapsedTimeAsSeconds = elapsedTime.count() / 1000000000.0f;
    _elapsedTime += elapsedTimeAsSeconds;
    if (_elapsedTime >= updateDelta) {
        ECSWrapper ecs;
        auto entityWithLives = ecs.entityManager.getEntitiesWith<indie::components::PlayerAlive>();
        for (auto &entity : entityWithLives) {
            auto playerAliveComponent = entity->getComponent<components::PlayerAlive>();
            if (playerAliveComponent->getLives() <= 0) {

            }
        }
        _elapsedTime -= updateDelta;
    }
}

void indie::systems::LiveSystem::onStop()
{

}

void indie::systems::LiveSystem::onTearDown()
{

}

void indie::systems::LiveSystem::startNewGame()
{

}

void indie::systems::LiveSystem::endGame()
{

}
