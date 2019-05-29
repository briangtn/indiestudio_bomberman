/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** DestroyOnTimeSystem
*/

#include "systems/DestroyOnTimeSystem.hpp"

indie::systems::DestroyOnTimeSystem::DestroyOnTimeSystem()
{

}

indie::systems::DestroyOnTimeSystem::~DestroyOnTimeSystem()
{

}

void indie::systems::DestroyOnTimeSystem::onAwake()
{
    // refaire comme le bombManagerSystem //
    // avec le component exploseonTime //
}

void indie::systems::DestroyOnTimeSystem::onStart()
{

}

void indie::systems::DestroyOnTimeSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    std::cout << elapsedTime.count() << std::endl;
}

void indie::systems::DestroyOnTimeSystem::onTearDown()
{

}

void indie::systems::DestroyOnTimeSystem::onStop()
{

}