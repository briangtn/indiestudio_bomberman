/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** MovementSystem.cpp
*/

/* Created the 24/05/2019 at 13:53 by jfrabel */

#include <cmath>
#include "components/BoxCollider.hpp"
#include "maths/Geometry3D.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
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
#include "components/AIController.hpp"
#include "components/DynamicCamera.hpp"
#include <cfloat>
#include "events/HasReachedTarget.hpp"

#include <limits>

indie::systems::MovementSystem::MovementSystem(): _mapSize(), _viewGridCache(), _pathsCache(), _timeBeforeCacheComputation(recomputeCacheDeltaTime)
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
    updateMoveToTargetMovement(elapsedTime);
    updateDynamicCameras(elapsedTime);
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
    auto cameras = ecs.entityManager.getEntitiesWith<components::Camera, components::Transform>();
    maths::Vector3D rot;
    if (!cameras.empty()) {
        rot = cameras[0]->getComponent<components::Transform>()->getRotation();
    }

    ecs.entityManager.applyToEach<components::Transform, components::PlayerController>(
        [elapsedTimeAsSecond, rot](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Transform> tr, jf::components::ComponentHandler<components::PlayerController> pc) {

            bool canMove = !pc->isTaunting() && !pc->isPlacingBomb();

            if (!canMove) {
                pc->setIsWalking(false);
                return;
            }

            auto playerCollider = entity->getComponent<components::BoxCollider>();
            std::vector<jf::internal::ID> disabledBombs;
            if (playerCollider.isValid()) {
                auto collisions = playerCollider->getCollisions();
                for (auto &collision : collisions) {
                    auto collider = collision->getComponent<components::BoxCollider>();
                    if ((collider->getLayer() & BOMB_LAYER) && !(collider->getLayer() & ~BOMB_LAYER)) {
                        disabledBombs.push_back(collision->getID());
                    }
                }
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
            if (pc->isMovementRelativeToCamera()) {
                maths::Matrix4 rotation = maths::Matrix4::Rotation(pc->isLockRotationX() ? 0 : rot.x, pc->isLockRotationY() ? 0 : rot.y, pc->isLockRotationZ() ? 0 : rot.z);
                movement = maths::Matrix4::MultiplyVector(movement, rotation);
            }
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
            if (playerCollider.isValid()) {
                auto collisions = playerCollider->getCollisions();
                bool hasCollisions = false;
                for (auto &collision : collisions) {
                    hasCollisions = true;
                    for (auto &bombId : disabledBombs) {
                        if (collision->getID() == bombId)
                            hasCollisions = false;
                    }
                    if (hasCollisions)
                        break;
                }
                if (hasCollisions) {
                    tr->setPosition(pos);
                    tr->setRotation(rot);
                }
            }
        }
    );
}

void indie::systems::MovementSystem::updateMoveToTargetMovement(const std::chrono::nanoseconds &elapsedTime)
{
    float elapsedTimeAsSeconds = elapsedTime.count() / 1000000000.0f;
    _timeBeforeCacheComputation -= elapsedTimeAsSeconds;
    if (_timeBeforeCacheComputation <= 0.0f) {
        recomputeCaches();
        _timeBeforeCacheComputation += recomputeCacheDeltaTime;
    }
    for (auto &tuple : _pathsCache) {
        auto &mtt = std::get<0>(tuple);
        auto &tr = std::get<1>(tuple);
        auto &path = std::get<2>(tuple);
        jf::components::ComponentHandler<components::Animator> animator;
        if (mtt.isValid()) {
            animator = mtt->getEntity()->getComponent<components::Animator>();
        }
        if (!path.empty() && mtt.isValid() && tr.isValid() && mtt->isFollowTarget() && !mtt->hasReachedTarget()) {
            auto nextNode = path.top();

            float speed = mtt->getSpeed();
            maths::Vector3D movementVector = (nextNode.toWorldPos() - tr->getPosition()).normalized();

            tr->setPosition(tr->getPosition() + movementVector * speed * elapsedTimeAsSeconds);
            maths::Vector3D rot = tr->getRotation();
            tr->lookAt(tr->getPosition() + movementVector);
            tr->setRotation({rot.x, tr->getRotation().y, rot.z});

            if (animator.isValid() && animator->getCurrentAnimation() == "idle") {
                animator->setCurrentAnimation("walk");
            }

            while ((tr->getPosition() - nextNode.toWorldPos()).magnitudeSq() <= nodeValidatedInRadius * nodeValidatedInRadius) {
                path.pop();
                if (path.empty()) {
                    ECSWrapper ecs;
                    mtt->setReachedTarget(true);
                    ecs.eventManager.emit(events::HasReachedTarget({mtt}));
                    break;
                } else {
                    nextNode = path.top();
                }
            }
        } else if (animator.isValid() && animator->getCurrentAnimation() == "walk") {
            animator->setCurrentAnimation("idle");
        }
    }
}

void indie::systems::MovementSystem::updateDynamicCameras(const std::chrono::nanoseconds &elapsedTime) const
{
    ECSWrapper ecs;
    float elapsedTimeAsSeconds = elapsedTime.count() / 1000000000.0f;
    auto players = ecs.entityManager.getEntitiesWith<components::PlayerController, components::Transform>();
    auto bots = ecs.entityManager.getEntitiesWith<components::AIController, components::Transform>();
    std::list<jf::components::ComponentHandler<components::Transform>> trs;
    for (auto &player : players)
        trs.push_front(player->getComponent<components::Transform>());
    for (auto &bot : bots)
        trs.push_front(bot->getComponent<components::Transform>());
    maths::Vector3D minTr(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    maths::Vector3D maxTr(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
    for (auto &tr : trs) {
        auto trPos = tr->getPosition();
        if (trPos.x < minTr.x)
            minTr.x = trPos.x;
        if (trPos.y < minTr.y)
            minTr.y = trPos.y;
        if (trPos.z < minTr.z)
            minTr.z = trPos.z;
        if (trPos.x > maxTr.x)
            maxTr.x = trPos.x;
        if (trPos.y > maxTr.y)
            maxTr.y = trPos.y;
        if (trPos.z > maxTr.z)
            maxTr.z = trPos.z;
    }
    ecs.entityManager.applyToEach<components::DynamicCamera, components::Transform>([&elapsedTimeAsSeconds, &minTr, &maxTr](jf::entities::EntityHandler entity, auto dynamicCamera, auto tr) {
        maths::Vector3D minCorner = minTr - maths::Vector3D(10 * dynamicCamera->getBlockBorders(), 0, 10 * dynamicCamera->getBlockBorders());
        maths::Vector3D maxCorner = maxTr + maths::Vector3D(10 * dynamicCamera->getBlockBorders(), 0, 10 * dynamicCamera->getBlockBorders());
        float diagonal = (maxCorner - minCorner).magnitude();
        float zoomMultiplyer = diagonal / 250.0f;
        maths::Vector3D targetedPos((maxCorner.x + minCorner.x) / 2, 150 * zoomMultiplyer, (maxCorner.z + minCorner.z) / 2 - 50.0f * zoomMultiplyer);
        targetedPos.y = targetedPos.y < 100 ? 100 : targetedPos.y;
        auto movementSpeed = dynamicCamera->getMovementSpeed();
        auto cameraPosition = tr->getPosition();
        auto direction = targetedPos - cameraPosition;
        if (direction.magnitudeSq() >= 10)
            tr->setPosition(cameraPosition + direction.normalized() * movementSpeed * elapsedTimeAsSeconds);
    });
}

void indie::systems::MovementSystem::recomputeCaches()
{
    ai::AIView::recomputeViewGrid(static_cast<int>(_mapSize.x), static_cast<int>(_mapSize.y));
    _viewGridCache = ai::AIView::getViewGrid();
    _pathsCache.clear();
    ECSWrapper ecs;
    ecs.entityManager.applyToEach<components::MoveToTarget, components::Transform>(
        [&](jf::entities::EntityHandler entity, auto mtt, auto tr) {
            int playerX = std::round(tr->getPosition().x / 10.0f);
            int playerZ = -std::round(tr->getPosition().z / 10.0f);
            int targetX = std::round(mtt->getTarget().x / 10.0f);
            int targetZ = -std::round(mtt->getTarget().z / 10.0f);
            auto collider = entity->getComponent<components::BoxCollider>();
            bool canGoThroughCrate = !collider.isValid() || !(collider->getLayer() & BREAKABLE_BLOCK_LAYER);
            auto path = ai::AStar::findPath(_viewGridCache, {playerX, playerZ}, {targetX, targetZ}, canGoThroughCrate);
            if (path.empty() && !mtt->hasReachedTarget() && mtt->isFollowTarget()) {
                ECSWrapper ecs;
                mtt->setReachedTarget(true);
                ecs.eventManager.emit(events::HasReachedTarget({mtt}));
            }
            _pathsCache.push_front(std::make_tuple(mtt, tr, path));
        }
    );
}

const indie::maths::Vector2D &indie::systems::MovementSystem::getMapSize() const
{
    return _mapSize;
}

void indie::systems::MovementSystem::setMapSize(const indie::maths::Vector2D &mapSize)
{
    _mapSize = mapSize;
}