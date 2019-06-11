/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** AISystem
*/

#include "systems/AISystem.hpp"
#include "events/IrrlichtAnimationEndEvent.hpp"
#include "ECSWrapper.hpp"

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
    if (_timePassed >= 500000000) {
        _timePassed = 0;
        //logic here
    }
}