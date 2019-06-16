/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** SplashScreenSystem.cpp
*/

/* Created the 16/06/2019 at 22:04 by jfrabel */

#include "scenes/SceneManager.hpp"
#include "ECSWrapper.hpp"
#include "systems/SplashScreenSystem.hpp"

indie::systems::SplashScreenSystem::SplashScreenSystem()
    : _remainingTime(splashScreenTime)
{

}

void indie::systems::SplashScreenSystem::onAwake()
{

}

void indie::systems::SplashScreenSystem::onStart()
{

}

void indie::systems::SplashScreenSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    _remainingTime -= (elapsedTime.count() / 1000000000.0f);
    if (_remainingTime <= 0.0f) {
        scenes::SceneManager::safeChangeScene("mainMenu");
        ECSWrapper ecs;
        ecs.systemManager.stopSystem<SplashScreenSystem>();
    }
}

void indie::systems::SplashScreenSystem::onStop()
{

}

void indie::systems::SplashScreenSystem::onTearDown()
{

}
