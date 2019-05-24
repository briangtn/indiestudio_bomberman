/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** MovementSystem.cpp
*/

/* Created the 24/05/2019 at 13:53 by jfrabel */

#include <cmath>
#include "ECSWrapper.hpp"
#include "systems/MovementSystem.hpp"
#include "components/Transform.hpp"
#include "components/Rotator.hpp"
#include "components/Hoverer.hpp"

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
