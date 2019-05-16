/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Camera.cpp
*/

#include <IrrlichtManagerExceptions.hpp>
#include "IrrlichtManagerSystem.hpp"
#include "IrrlichtClosingWindowEvent.hpp"
#include "ECSWrapper.hpp"
#include "Events.hpp"
#include "Camera.hpp"

jf::components::Camera::Camera(entities::Entity &entity, float FOV)
    : Component(entity), _FOV(FOV)
{
    ECSWrapper ecs;

    ecs.eventManager.addListener<Camera, events::IrrlichtClosingWindowEvent>(this, [](Camera *camera, events::IrrlichtClosingWindowEvent e){
        camera->_sceneNode->drop();
        camera->_sceneNode = nullptr;
    });
    EMIT_CREATE(Camera);
}

jf::components::Camera::~Camera()
{
    if (_sceneNode != nullptr)
        _sceneNode->drop();
    EMIT_DELETE(Camera);
}

void jf::components::Camera::update()
{
    ECSWrapper ecs;
    irr::scene::ISceneManager *scene = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();

    jf::components::ComponentHandler<Transform> transform = getEntity()->getComponent<Transform>();
    irr::core::vector3df position(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z);
    irr::core::vector3df rotation(transform->getRotation().x, transform->getRotation().y, transform->getRotation().z);
    irr::core::vector3df scale(transform->getScale().x, transform->getScale().y, transform->getScale().z);

    if (_sceneNode == nullptr && scene != nullptr)
        _sceneNode = scene->addCameraSceneNode(nullptr);
    if (_sceneNode == nullptr)
        throw jf::exceptions::IrrlichtManagerCameraException("Cannot create scene node", "Camera");
    _sceneNode->setFOV(_FOV);
    _sceneNode->setPosition(position);
    _sceneNode->setRotation(rotation);
    _sceneNode->setScale(scale);
}

void jf::components::Camera::setFOV(float FOV)
{
    _FOV = FOV;
}

float jf::components::Camera::getFOV() const
{
    return _FOV;
}
