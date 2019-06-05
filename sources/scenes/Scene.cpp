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

#include "events/IrrlichtKeyInputEvent.hpp"
#include "components/Transform.hpp"

indie::scenes::Scene::Scene(const std::string &fileName)
    : _fileName(fileName), _listeners()
{
}

void indie::scenes::Scene::onStart()
{
    Parser::getInstance().loadScene("../resources/scenes/test.xml", *this);
    ECSWrapper ecs;

    auto id = ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_Q>>(nullptr, [](void *null, auto e) {
        ECSWrapper ecs;
        auto tr = ecs.entityManager.getEntityByName("camera")->getComponent<indie::components::Transform>();
        auto oldPos = tr->getPosition();
        auto oldRot = tr->getRotation();
        if (e.shiftActivated) {
            oldRot.y -= 1;
        } else {
            oldPos.x -= 1;
        }
        tr->setPosition(oldPos);
        tr->setRotation(oldRot);
    });
    _listeners.push_back(id);
    id = ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_D>>(nullptr, [](void *null, auto e) {
        ECSWrapper ecs;
        auto tr = ecs.entityManager.getEntityByName("camera")->getComponent<indie::components::Transform>();
        auto oldPos = tr->getPosition();
        auto oldRot = tr->getRotation();
        if (e.shiftActivated) {
            oldRot.y += 1;
        } else {
            oldPos.x += 1;
        }
        tr->setPosition(oldPos);
        tr->setRotation(oldRot);
    });
    _listeners.push_back(id);
    id = ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_Z>>(nullptr, [](void *null, auto e) {
        ECSWrapper ecs;
        auto tr = ecs.entityManager.getEntityByName("camera")->getComponent<indie::components::Transform>();
        auto oldPos = tr->getPosition();
        if (e.shiftActivated) {
            oldPos.y += 1;
        } else {
            oldPos.z += 1;
        }
        tr->setPosition(oldPos);
    });
    _listeners.push_back(id);
    id = ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_S>>(nullptr, [](void *null, auto e) {
        ECSWrapper ecs;
        auto tr = ecs.entityManager.getEntityByName("camera")->getComponent<indie::components::Transform>();
        auto oldPos = tr->getPosition();
        if (e.shiftActivated) {
            oldPos.y -= 1;
        } else {
            oldPos.z -= 1;
        }
        tr->setPosition(oldPos);
    });
    _listeners.push_back(id);
}

void indie::scenes::Scene::onStop()
{
    ECSWrapper ecs;
    for (auto &id : _listeners)
        ecs.eventManager.removeListener(id);
    _listeners.clear();
}

void indie::scenes::Scene::setListeners(const std::vector<jf::internal::ID> &listeners)
{
    _listeners = listeners;
}
