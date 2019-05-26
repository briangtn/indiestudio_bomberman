/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** main.cpp
*/

/* Created the 09/05/2019 at 21:39 by jfrabel */

#include <iostream>
#include "ECSWrapper.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "scenes/StaticTestScene.hpp"
#include "scenes/SceneManager.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "systems/IrrklangAudioSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "input/InputManager.hpp"

int runBomberman()
{
    ECSWrapper ecs;
    ecs.systemManager.addSystem<indie::systems::IrrlichtManagerSystem>();
    ecs.systemManager.startSystem<indie::systems::IrrlichtManagerSystem>();
    ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().activateJoysticks();
    ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().setFullScreenEnabled(false);

    ecs.systemManager.addSystem<indie::systems::IrrklangAudioSystem>();
    ecs.systemManager.startSystem<indie::systems::IrrklangAudioSystem>();

    ecs.systemManager.addSystem<indie::systems::MovementSystem>();
    ecs.systemManager.startSystem<indie::systems::MovementSystem>();

    indie::InputManager::CreateAxis("xAxis", {.id = 0, .axis = 0});
    indie::InputManager::CreateAxis("xAxis", indie::KeyAxis({.positiveKey = irr::KEY_KEY_D, .negativeKey = irr::KEY_KEY_Q}));
    indie::InputManager::CreateAxis("zAxis", {.id = 0, .axis = 1, .invert = true});
    indie::InputManager::CreateAxis("zAxis", indie::KeyAxis({.positiveKey = irr::KEY_KEY_Z, .negativeKey = irr::KEY_KEY_S}));
    indie::InputManager::CreateAxis("yAxis", {.id = 0, .positiveKey = 0b00000000, .negativeKey = 0b00000001});
    indie::InputManager::CreateAxis("yAxis", indie::KeyAxis({.positiveKey = irr::KEY_SPACE, .negativeKey = irr::KEY_LSHIFT}));

    std::vector<std::pair<std::string, indie::scenes::IScene *>> scenes;
    scenes.emplace_back("test", new indie::scenes::StaticTestScene());
    indie::scenes::SceneManager::addScenes(scenes);
    indie::scenes::SceneManager::changeScene("test");

    ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_R>>(nullptr, [](void *null, auto e) {
        if (e.wasPressed)
            indie::scenes::SceneManager::changeScene("test");
    });

    while (ecs.systemManager.getState<indie::systems::IrrlichtManagerSystem>() == jf::systems::AWAKING ||
           ecs.systemManager.getState<indie::systems::IrrlichtManagerSystem>() == jf::systems::STARTING ||
           ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().isWindowOpen()) {
        ecs.systemManager.tick();
        auto errors = ecs.systemManager.getErrors();
        if (!errors.empty()) {
            for (auto &err : errors) {
                std::cerr << "[ERROR] " << err.error << std::endl;
            }
            return 84;
        }
    }
    return 0;
}

int main()
{
    try {
        return runBomberman();
    } catch (const jf::ECSException &e) {
        std::cerr << "An error occurred while running the game: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "A standard error occurred while running the game: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while running the game." << std::endl;
    }
    return 84;
}