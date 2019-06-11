/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Scene.cpp
*/

/* Created the 27/05/2019 at 15:27 by jbulteau */

#include <iostream>
#include "scenes/Scene.hpp"
#include "parser/Parser.hpp"
#include "ECSWrapper.hpp"
#include "parser/Parser.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "components/Transform.hpp"
#include "components/Animator.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "map/Map.hpp"
#include "ai/AiView.hpp"
#include "components/BonusSpawner.hpp"
#include "events/AskingForBonusSpawnEvent.hpp"

indie::scenes::Scene::Scene(const std::string &fileName)
    : _fileName(fileName), _listeners()
{
}

void indie::scenes::Scene::onStart()
{
    Parser::getInstance().loadScene(std::string(SCENES_FOLDER_PATH) + "/" + _fileName);
    ECSWrapper ecs;

    auto id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_W>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("default");
        }
    });
    _listeners.emplace_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_X>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("idle");
        }
    });
    _listeners.emplace_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_C>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("walk");
        }
    });
    _listeners.emplace_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_V>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("taunt");
        }
    });
    _listeners.emplace_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_B>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("place bomb");
        }
    });
    _listeners.emplace_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_N>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("die");
        }
    });
    _listeners.emplace_back(id);

    auto mapWidth = 15;
    auto mapHeight = 15;
    indie::Map::generateMap(mapWidth, mapHeight, 421, false);

    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_M>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            indie::systems::IrrlichtManagerSystem::drawGizmos(!indie::systems::IrrlichtManagerSystem::getDrawGizmos());
        }
    });

    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_P>>(nullptr, [mapWidth, mapHeight](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            indie::ai::AIView::recomputeViewGrid(mapWidth, mapHeight);
            auto &viewGrid = indie::ai::AIView::getViewGrid();
            std::cout << "View Grid:" << std::endl;
            for (int z = 0; z < mapHeight; ++z) {
                for (int x = 0; x < mapWidth; ++x) {
                    std::cout << static_cast<int>(viewGrid[z][x]) << " ";
                }
                std::cout << std::endl;
            }
            auto &collisionGrid = indie::ai::AIView::getCollisionGrid();
            std::cout << "Collision Grid:" << std::endl;
            for (int z = 0; z < mapHeight; ++z) {
                for (int x = 0; x < mapWidth; ++x) {
                    std::cout << std::boolalpha << collisionGrid[z][x] << " ";
                }
                std::cout << std::endl;
            }
        }
    });

    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_J>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.eventManager.emit(events::AskingForBonusSpawnEvent({{10, 1, 0}, components::BonusSpawner::BONUS_SPAWNER_T_RANDOM, components::BONUS_T_NB}));
        }
    });

    _listeners.emplace_back(id);
}

void indie::scenes::Scene::onStop()
{
    ECSWrapper ecs;
    for (auto &id : _listeners)
        ecs.eventManager.removeListener(id);
    _listeners.clear();
}
