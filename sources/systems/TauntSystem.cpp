/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** TauntSystem.cpp
*/

/* Created the 03/06/2019 at 15:22 by jfrabel */

#include <input/InputManager.hpp>
#include <components/Animator.hpp>
#include "ECSWrapper.hpp"
#include "systems/TauntSystem.hpp"
#include "components/PlayerController.hpp"

void indie::systems::TauntSystem::onAwake()
{

}

void indie::systems::TauntSystem::onStart()
{

}

void indie::systems::TauntSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    ECSWrapper ecs;
    float elapsedTimeAsSecond = elapsedTime.count() / 1000000000.0f;
    ecs.entityManager.applyToEach<components::PlayerController>(
        [elapsedTimeAsSecond](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::PlayerController> pc) {

            if (pc->isTaunting()) {
                pc->setTauntTime(pc->getTauntTime() - elapsedTimeAsSecond);
                if (pc->getTauntTime() <= 0.0f) {
                    pc->setTauntTime(0.0f);
                    pc->setIsTaunting(false);
                }
            }

            //if (indie::InputManager::IsKeyPressed("taunt")) {
            if (indie::InputManager::IsKeyPressed(0, 1)) {
                pc->setIsTaunting(true);
                pc->setTauntTime(pc->getTauntDuration());
                auto animator = pc->getEntity()->getComponent<components::Animator>();
                if (animator.isValid()) {
                    animator->setCurrentAnimation(pc->getTauntAnimation());
                }
            }
        }
    );
}

void indie::systems::TauntSystem::onStop()
{

}

void indie::systems::TauntSystem::onTearDown()
{

}
