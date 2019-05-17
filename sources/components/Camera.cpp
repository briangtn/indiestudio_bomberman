/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Camera.cpp
*/

#include <IrrlichtManagerExceptions.hpp>
#include "CameraException.hpp"
#include "IrrlichtManagerSystem.hpp"
#include "IrrlichtClosingWindowEvent.hpp"
#include "ECSWrapper.hpp"
#include "Events.hpp"
#include "Camera.hpp"

jf::components::Camera::Camera(entities::Entity &entity, float FOV)
    : Component(entity), _FOV(FOV)
{
    ECSWrapper ecs;

    _eventCloseID = ecs.eventManager.addListener<Camera, events::IrrlichtClosingWindowEvent>(this, [](Camera *camera, events::IrrlichtClosingWindowEvent e){
        camera->_cameraNode->remove();
        camera->_cameraNode = nullptr;
    });
    EMIT_CREATE(Camera);
}

jf::components::Camera::~Camera()
{
    EMIT_DELETE(Camera);

    ECSWrapper ecs;
    ecs.eventManager.removeListener(_eventCloseID);
    if (_cameraNode != nullptr)
        _cameraNode->remove();
}

void jf::components::Camera::updateCamera()
{
    ECSWrapper ecs;
    auto size = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getWindowDimension();
    irr::scene::ISceneManager *scene = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();

    jf::components::ComponentHandler<Transform> transform = getEntity()->getComponent<Transform>();
    irr::core::vector3df position(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z);
    irr::core::vector3df rotation(transform->getRotation().x, transform->getRotation().y, transform->getRotation().z);
    irr::core::vector3df scale(transform->getScale().x, transform->getScale().y, transform->getScale().z);

    if (_cameraNode == nullptr && scene != nullptr) {
        _cameraNode = scene->addCameraSceneNode(nullptr);
        _cameraNode->setProjectionMatrix(irr::core::CMatrix4<float>().buildProjectionMatrixOrthoLH(size.x, size.y, _cameraNode->getNearValue(), _cameraNode->getFarValue()), true);
        _cameraNode->bindTargetAndRotation(true);
    }
    if (_cameraNode == nullptr)
        throw jf::exceptions::CameraException("Cannot create scene node", "Camera");
    auto oldTargetOffset = _cameraNode->getTarget() - _cameraNode->getAbsolutePosition();
    auto newTargetOffset = _cameraNode->getTarget() - position;
    auto offset = oldTargetOffset - newTargetOffset;
    _cameraNode->setFOV(_FOV);
    _cameraNode->setPosition(position);
    _cameraNode->setRotation(rotation);
    _cameraNode->setScale(scale);
    _cameraNode->setTarget(_cameraNode->getTarget() + offset);
}

void jf::components::Camera::setFOV(float FOV)
{
    _FOV = FOV;
}

float jf::components::Camera::getFOV() const
{
    return _FOV;
}

irr::scene::ICameraSceneNode *jf::components::Camera::getCameraNode()
{
    return _cameraNode;
}
