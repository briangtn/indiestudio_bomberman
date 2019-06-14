/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** main.cpp
*/

/* Created the 09/05/2019 at 21:39 by jfrabel */

#include <iostream>
#include "systems/TauntSystem.hpp"
#include "systems/TauntSystem.hpp"
#include "systems/BonusSystem.hpp"
#include "ECSWrapper.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "scenes/PlayerConfigScene.hpp"
#include "scenes/ControllerConfigScene.hpp"
#include "scenes/SceneManager.hpp"
#include "scenes/EndScene.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "systems/IrrklangAudioSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "input/InputManager.hpp"
#include "events/IrrlichtKeyJustChangedEvent.hpp"
#include "parser/Parser.hpp"
#include "systems/BombManagerSystem.hpp"
#include "systems/DestroyOnTimeSystem.hpp"
#include "components/Bomb.hpp"
#include "assets_manager/AssetsManager.hpp"

int runBomberman()
{
    ECSWrapper ecs;
    std::vector<jf::internal::ID> listeners;

    indie::Parser::getInstance().loadSystems(SYSTEMS_FILE_PATH);
    indie::scenes::PlayerConfigScene::InitControllers();
    ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().activateJoysticks();

    auto &assetsManager = indie::AssetsManager::getInstance();
    assetsManager.addTexturePack("default", "resources/resources_packs/default/");
    assetsManager.loadTexturePack("default");

    indie::scenes::SceneManager::addScenes(indie::Parser::getInstance().loadScenes(SCENES_FOLDER_PATH));
    indie::scenes::SceneManager::addSingleScene("playerConfig", new indie::scenes::PlayerConfigScene());
    indie::scenes::SceneManager::addSingleScene("controllerConfig", new indie::scenes::ControllerConfigScene());
    indie::scenes::SceneManager::addSingleScene("endScene", new indie::scenes::EndScene());
    ecs.systemManager.addSystem<indie::systems::BombManagerSystem>();
    ecs.systemManager.startSystem<indie::systems::BombManagerSystem>();

    indie::scenes::SceneManager::changeScene("mainMenu");

    auto id = ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_R>>(nullptr, [](void *null, auto e) {
        if (e.wasPressed)
            indie::scenes::SceneManager::changeScene("endScene");
    });
    listeners.push_back(id);

    while (ecs.systemManager.getState<indie::systems::IrrlichtManagerSystem>() == jf::systems::AWAKING ||
           ecs.systemManager.getState<indie::systems::IrrlichtManagerSystem>() == jf::systems::STARTING ||
           ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().isWindowOpen()) {
        ecs.systemManager.tick();
        ecs.entityManager.applySafeDelete();
        indie::scenes::SceneManager::triggerSafeFunctions();
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
