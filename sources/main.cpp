/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** main.cpp
*/

/* Created the 09/05/2019 at 21:39 by jfrabel */

#include <iostream>
#include <systems/TauntSystem.hpp>
#include "ECSWrapper.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "scenes/StaticTestScene.hpp"
#include "scenes/SceneManager.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "systems/IrrklangAudioSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "input/InputManager.hpp"
#include "events/IrrlichtKeyJustChangedEvent.hpp"
#include "parser/Parser.hpp"

int runBomberman()
{
    ECSWrapper ecs;
    std::vector<jf::internal::ID> listeners;

    indie::Parser::getInstance().loadSystems(SYSTEMS_FILE_PATH);
    ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().activateJoysticks();
    ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().setFullScreenEnabled(false);

    indie::InputManager::CreateAxis("xAxis", indie::JoystickAxis({0, 0}));
	indie::InputManager::CreateAxis("xAxis", indie::KeyAxis({irr::KEY_KEY_D, irr::KEY_KEY_Q}));
    indie::InputManager::CreateAxis("zAxis", indie::JoystickAxis({0, 1, true}));
    indie::InputManager::CreateAxis("zAxis", indie::KeyAxis({irr::KEY_KEY_Z, irr::KEY_KEY_S}));
    indie::InputManager::CreateAxis("yAxis", indie::ControllerKeyAxis({0, 0b00000000, 0b00000001}));
    indie::InputManager::CreateAxis("yAxis", indie::KeyAxis({irr::KEY_SPACE, irr::KEY_LSHIFT}));
    indie::InputManager::CreateAxis("xRotAxis", indie::JoystickAxis({0, 4}));
    indie::InputManager::CreateAxis("yRotAxis", indie::JoystickAxis({0, 3}));

    indie::InputManager::RegisterKey("taunt", 0, 1);

    indie::scenes::SceneManager::addScenes(indie::Parser::getInstance().loadScenes(SCENES_FOLDER_PATH));

    indie::scenes::SceneManager::changeScene("mainMenu");

    auto id = ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_R>>(nullptr, [](void *null, auto e) {
        if (e.wasPressed)
            indie::scenes::SceneManager::changeScene("mainMenu");
    });
    listeners.push_back(id);
	id = ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_T>>(nullptr, [](void *null, auto e) {
		if (e.wasPressed) {
			ECSWrapper ecs;
			ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().setFullScreenEnabled(!ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().isFullScreenEnabled());
		}
	});
    listeners.push_back(id);

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
    for (auto &elem : listeners) {
        ecs.eventManager.removeListener(elem);
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