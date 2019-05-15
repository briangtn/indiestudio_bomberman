//
// Created by brian on 5/14/19.
//

#include "IrrlichtManagerSystem.hpp"
#include "ECSWrapper.hpp"
#include "Events.hpp"
#include "Camera.hpp"

jf::components::Camera::Camera(entities::Entity &entity, float FOV)
    : Component(entity)
{
    ECSWrapper ecs;
    irr::scene::ISceneManager *scene = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();

    _sceneNode = scene->addCameraSceneNode(nullptr);
    _sceneNode->setFOV(FOV);
    EMIT_CREATE(Camera);
}

jf::components::Camera::~Camera()
{
    EMIT_DELETE(Camera);
}

void jf::components::Camera::update()
{
    jf::components::ComponentHandler<Transform> transform = getEntity()->getComponent<Transform>();
    irr::core::vector3df position(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z);
    irr::core::vector3df rotation(transform->getRotation().x, transform->getRotation().y, transform->getRotation().z);
    irr::core::vector3df scale(transform->getScale().x, transform->getScale().y, transform->getScale().z);

    _sceneNode->setPosition(position);
    _sceneNode->setRotation(rotation);
    _sceneNode->setScale(scale);
}
