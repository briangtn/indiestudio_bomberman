/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** SplashScreenScene.cpp
*/

/* Created the 16/06/2019 at 22:02 by jfrabel */

#include "components/Transform.hpp"
#include "components/GUI/Image.hpp"
#include "ECSWrapper.hpp"
#include "scenes/SplashScreenScene.hpp"

void indie::scenes::SplashScreenScene::onStart()
{
    ECSWrapper ecs;
    auto backgroundEntity = ecs.entityManager.createEntity("splashArt");
    backgroundEntity->assignComponent<indie::components::Image>("splash_screen");
    auto backgroundTransform = backgroundEntity->assignComponent<indie::components::Transform>();
    backgroundTransform->setPosition({0, 0, -1});
}

void indie::scenes::SplashScreenScene::onStop()
{

}

indie::scenes::SaveState indie::scenes::SplashScreenScene::save(bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}

indie::scenes::SaveState
indie::scenes::SplashScreenScene::save(const std::string &saveName, bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}
