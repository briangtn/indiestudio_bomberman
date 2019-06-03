/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** MovementSystem.cpp
*/

/* Created the 24/05/2019 at 13:53 by jfrabel */

#include <cmath>
#include <components/BoxCollider.hpp>
#include <maths/Geometry3D.hpp>
#include <systems/IrrlichtManagerSystem.hpp>

#include "ECSWrapper.hpp"
#include "systems/MovementSystem.hpp"
#include "components/Transform.hpp"
#include "components/Rotator.hpp"
#include "components/Hoverer.hpp"
#include "components/PlayerController.hpp"
#include "input/InputManager.hpp"
#include "components/Camera.hpp"
#include "maths/Matrices.hpp"
#include "components/Animator.hpp"

indie::systems::MovementSystem::MovementSystem()
{

}

indie::systems::MovementSystem::~MovementSystem()
{

}

void indie::systems::MovementSystem::onAwake()
{

}

void indie::systems::MovementSystem::onStart()
{

}

void indie::systems::MovementSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    updateRotator(elapsedTime);
    updateHoverer(elapsedTime);
    updatePlayerMovement(elapsedTime);
}

void indie::systems::MovementSystem::onStop()
{

}

void indie::systems::MovementSystem::onTearDown()
{

}

void indie::systems::MovementSystem::updateRotator(const std::chrono::nanoseconds &elapsedTime) const
{
    ECSWrapper ecs;
    float elapsedTimeAsSecond = elapsedTime.count() / 1000000000.0f;
    ecs.entityManager.applyToEach<components::Transform, components::Rotator>(
        [elapsedTimeAsSecond](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Transform> tr, jf::components::ComponentHandler<components::Rotator> rotator) {
            auto rot = tr->getRotation();
            auto speed = rotator->getSpeed();
            tr->setRotation({rot.x + (speed.x * elapsedTimeAsSecond), rot.y + (speed.y * elapsedTimeAsSecond), rot.z + (speed.z * elapsedTimeAsSecond)});
        }
    );
}

void indie::systems::MovementSystem::updateHoverer(const std::chrono::nanoseconds &elapsedTime) const
{
    ECSWrapper ecs;
    float elapsedTimeAsSecond = elapsedTime.count() / 1000000000.0f;
    ecs.entityManager.applyToEach<components::Transform, components::Hoverer>(
        [elapsedTimeAsSecond](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Transform> tr, jf::components::ComponentHandler<components::Hoverer> hoverer) {
            auto speed = hoverer->getSpeed();
            auto amplitude = hoverer->getAmplitude();
            auto advancement = hoverer->getAdvancement();
            auto initialPos = tr->getPosition();
            initialPos.x -= (sinf(advancement.x) * amplitude.x);
            initialPos.y -= (sinf(advancement.y) * amplitude.y);
            initialPos.z -= (sinf(advancement.z) * amplitude.z);
            tr->setPosition({
                initialPos.x + (sinf(advancement.x + elapsedTimeAsSecond * speed.x) * amplitude.x),
                initialPos.y + (sinf(advancement.y + elapsedTimeAsSecond * speed.y) * amplitude.y),
                initialPos.z + (sinf(advancement.z + elapsedTimeAsSecond * speed.z) * amplitude.z)
            });
            hoverer->setAdvancement({
                advancement.x + elapsedTimeAsSecond * speed.x,
                advancement.y + elapsedTimeAsSecond * speed.y,
                advancement.z + elapsedTimeAsSecond * speed.z
            });
        }
    );
}

void indie::systems::MovementSystem::updatePlayerMovement(const std::chrono::nanoseconds &elapsedTime) const
{
    ECSWrapper ecs;
    float elapsedTimeAsSecond = elapsedTime.count() / 1000000000.0f;
    maths::Matrix4 rotation = maths::Matrix4::Rotation(0, 0, 0);
    auto cameras = ecs.entityManager.getEntitiesWith<components::Camera, components::Transform>();
    if (!cameras.empty()) {
        auto rot = cameras[0]->getComponent<components::Transform>()->getRotation();
        rotation = maths::Matrix4::Rotation(rot.x, rot.y, rot.z);
    }

    auto entitiesWithCollider = ecs.entityManager.getEntitiesWith<components::BoxCollider>();

    ecs.entityManager.applyToEach<components::Transform, components::PlayerController>(
        [elapsedTimeAsSecond, rotation, entitiesWithCollider](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Transform> tr, jf::components::ComponentHandler<components::PlayerController> pc) {

            bool canMove = !pc->isTaunting() && !pc->isPlacingBomb();

            if (!canMove) {
                pc->setIsWalking(false);
                return;
            }

            auto pos = tr->getPosition();
            auto speed = pc->getMovementSpeed();
            auto &xAxis = pc->getXMovementAxis();
            auto &yAxis = pc->getYMovementAxis();
            auto &zAxis = pc->getZMovementAxis();
            maths::Vector3D movementVector(0, 0, 0);
            if (!xAxis.empty())
                movementVector.x = indie::InputManager::GetAxis(xAxis);
            if (!yAxis.empty())
                movementVector.y = indie::InputManager::GetAxis(yAxis);
            if (!zAxis.empty())
                movementVector.z = indie::InputManager::GetAxis(zAxis);
            maths::Vector3D movement = movementVector * speed * elapsedTimeAsSecond;
            if (pc->isMovementRelativeToCamera())
                movement = maths::Matrix4::MultiplyVector(movement, rotation);
            if (pc->isLockMovementX())
                movement.x = 0;
            if (pc->isLockMovementY())
                movement.y = 0;
            if (pc->isLockMovementZ())
                movement.z = 0;
            tr->setPosition(pos + movement);

            auto animator = entity->getComponent<components::Animator>();
            if (!pc->isWalking() && movement.magnitudeSq() != 0 && animator.isValid()) {
                animator->setCurrentAnimation(pc->getWalkingAnimation());
            } else if (pc->isWalking() && movement.magnitudeSq() == 0 && animator.isValid()) {
                animator->setCurrentAnimation(pc->getIdleAnimation());
            }
            pc->setIsWalking(movement.magnitudeSq() != 0);

            maths::Vector3D rot = tr->getRotation();
            maths::Vector3D newRot = rot;
            if (pc->isAlwaysLookForward() && movement.magnitudeSq() != 0) {
                tr->lookAt(tr->getPosition() + movement);
                newRot = tr->getRotation();
            } else {
                auto rotSpeed = pc->getRotationSpeed();
                auto &xRotAxis = pc->getXRotationAxis();
                auto &yRotAxis = pc->getYRotationAxis();
                auto &zRotAxis = pc->getZRotationAxis();
                maths::Vector3D rotationAxes;
                if (!xRotAxis.empty())
                    rotationAxes.x = indie::InputManager::GetAxis(xRotAxis);
                if (!yRotAxis.empty())
                    rotationAxes.y = indie::InputManager::GetAxis(yRotAxis);
                if (!zRotAxis.empty())
                    rotationAxes.z = indie::InputManager::GetAxis(zRotAxis);
                newRot = newRot + rotationAxes * rotSpeed * elapsedTimeAsSecond;
            }
            if (pc->isLockRotationX())
                newRot.x = rot.x;
            if (pc->isLockRotationY())
                newRot.y = rot.y;
            if (pc->isLockRotationZ())
                newRot.z = rot.z;
            tr->setRotation(newRot);

            //Cancel movement and rotation if invalid
            auto playerCollider = entity->getComponent<components::BoxCollider>();
            if (playerCollider.isValid() && playerCollider->hasCollisions()) {
                tr->setPosition(pos);
                tr->setRotation(rot);
                return;
            }
        }
    );
}
