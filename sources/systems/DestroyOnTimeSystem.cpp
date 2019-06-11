/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** DestroyOnTimeSystem
*/

#include "systems/DestroyOnTimeSystem.hpp"

indie::systems::DestroyOnTimeSystem::DestroyOnTimeSystem()
{
    
}

indie::systems::DestroyOnTimeSystem::~DestroyOnTimeSystem()
{

}

void indie::systems::DestroyOnTimeSystem::onAwake()
{

}

void indie::systems::DestroyOnTimeSystem::onStart()
{

}

void indie::systems::DestroyOnTimeSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    ECSWrapper ecs;
    std::vector<jf::internal::ID> toDelete;

    ecs.entityManager.applyToEach<components::DestroyOnTime>(
        [elapsedTime, &toDelete](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::DestroyOnTime> destroy) {
            if (destroy->getTimeBeforeDestroy() <= 0) {
                toDelete.emplace_back(destroy->getEntity()->getID());
            }
            else {
                destroy->setTimeBeforeDestroy(destroy->getTimeBeforeDestroy() - elapsedTime.count() / 1000000000.0f);
            }
    });
    for (auto &id : toDelete)
        ecs.entityManager.deleteEntity(id);
}

void indie::systems::DestroyOnTimeSystem::onTearDown()
{

}

void indie::systems::DestroyOnTimeSystem::onStop()
{

}