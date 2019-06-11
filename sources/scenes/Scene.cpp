/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Scene.cpp
*/

/* Created the 27/05/2019 at 15:27 by jbulteau */

#include "scenes/Scene.hpp"
#include "parser/Parser.hpp"
#include "ECSWrapper.hpp"
#include "parser/Parser.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "components/Transform.hpp"
#include "components/Animator.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "map/Map.hpp"

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

    indie::Map::generateMap(15, 15, 42, false);

    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_M>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            indie::systems::IrrlichtManagerSystem::drawGizmos(!indie::systems::IrrlichtManagerSystem::getDrawGizmos());
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
