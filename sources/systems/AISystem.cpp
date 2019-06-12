/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** AISystem
*/

#include "systems/AISystem.hpp"
#include "components/AIController.hpp"
#include "events/IrrlichtAnimationEndEvent.hpp"
#include "ECSWrapper.hpp"
#include "ai/AiView.hpp"

indie::systems::AISystem::AISystem() : _timePassed(0)
{
}

indie::systems::AISystem::~AISystem()
{
}

void indie::systems::AISystem::onAwake()
{

}

void indie::systems::AISystem::onStart()
{

}

void indie::systems::AISystem::onStop()
{

}

void indie::systems::AISystem::onTearDown()
{

}

void indie::systems::AISystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    _timePassed += elapsedTime.count();
    if (_timePassed < 500000000)
        return;
    _timePassed = 0;

    ECSWrapper ecs;
    ecs.entityManager.applyToEach<components::AIController>(&AILogic);
}

void indie::systems::AISystem::AILogic(jf::entities::EntityHandler entity,
    jf::components::ComponentHandler<indie::components::AIController> component)
{
    if (component->getState() != indie::components::AIController::POWERUP)
        chooseState(component);
}

void indie::systems::AISystem::chooseState(jf::components::ComponentHandler<indie::components::AIController> component)
{
    ai::AIView::AICellViewGrid grid = ai::AIView::getViewGrid();

    for (auto &row : grid) {
        for (auto &col : row) {
            
        }
    }
}