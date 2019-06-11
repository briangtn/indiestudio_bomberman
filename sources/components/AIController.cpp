/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** AIController
*/

#include "ECSWrapper.hpp"
#include "events/IrrlichtAnimationEndEvent.hpp"
#include "components/AIController.hpp"

indie::components::AIController::AIController(jf::entities::Entity &entity)
    : Component(entity), 
      _target(0, 0, 0),
      _isTaunting(false),
      _isPlacingBombs(false),
      _state(UNKNOWN)
{
    ECSWrapper ecs;

    ecs.eventManager.addListener<void, events::IrrlichtAnimationEndEvent>(nullptr, [&](void *a, events::IrrlichtAnimationEndEvent e) {
        if (getEntity()->getID() == e.entityId) {
            if (e.animationName == "taunt")
                setIsTaunting(false);
            else if (e.animationName == "place bomb")
                setIsPlacingBombs(false);
        }      
    });
}

indie::components::AIController::~AIController()
{
}

void indie::components::AIController::setTargetVector(indie::maths::Vector3D assign)
{
    _target = assign;
}

void indie::components::AIController::setIsTaunting(bool assign)
{
    _isTaunting = assign;
}

void indie::components::AIController::setIsPlacingBombs(bool assign)
{
    _isPlacingBombs = assign;
}

indie::maths::Vector3D indie::components::AIController::getTarget() const
{
    return _target;
}

bool indie::components::AIController::getIsTaunting() const
{
    return _isTaunting;
}

bool indie::components::AIController::getIsPlacingBombs() const
{
    return _isPlacingBombs;
}

indie::components::AIController::state indie::components::AIController::getState() const
{
    return _state;
}