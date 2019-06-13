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
      _previousPos({0, 0}),
      _isTaunting(false),
      _needToTaunt(false),
      _isPlacingBomb(false),
      _needToUseBomb(false),
      _state(UNKNOWN),
      _lastState(UNKNOWN)
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
    _isPlacingBomb = assign;
}

void indie::components::AIController::setState(indie::components::AIController::state assign)
{
    _state = assign;
}

void indie::components::AIController::setNeedToTaunt(bool assign)
{
    _needToTaunt = assign;
}

void indie::components::AIController::setNeedToUseBomb(bool assign)
{
    _needToUseBomb = assign;
}

void indie::components::AIController::setLastState(indie::components::AIController::state assign)
{
    _lastState = assign;
}

void indie::components::AIController::setPreviousPos(std::pair<int, int> assign)
{
    _previousPos = assign;
}

std::pair<int, int> indie::components::AIController::getPreviousPos() const
{
    return _previousPos;
}

indie::components::AIController::state indie::components::AIController::getLastState() const
{
    return _lastState;
}

bool indie::components::AIController::getNeedToUseBomb() const
{
    return _needToUseBomb;
}

bool indie::components::AIController::getNeedToTaunt() const
{
    return _needToTaunt;
}

indie::maths::Vector3D indie::components::AIController::getTarget() const
{
    return _target;
}

bool indie::components::AIController::getIsTaunting() const
{
    return _isTaunting;
}

bool indie::components::AIController::getIsPlacingBomb() const
{
    return _isPlacingBomb;
}

indie::components::AIController::state indie::components::AIController::getState() const
{
    return _state;
}

int indie::components::AIController::getBombForce() const
{
    return _bombForce;
}

void indie::components::AIController::setBombForce(int bombForce)
{
    _bombForce = bombForce;
}

int indie::components::AIController::getMaxBomb() const
{
    return _maxBomb;
}

void indie::components::AIController::setMaxBomb(int maxBomb)
{
    _maxBomb = maxBomb;
}

indie::components::PlayerType indie::components::AIController::getPlayerType() const
{
    return _playerType;
}

void indie::components::AIController::setPlayerType(indie::components::PlayerType playerType)
{
    _playerType = playerType;
}

float indie::components::AIController::getMovementSpeed() const
{
    return _movementSpeed;
}

void indie::components::AIController::setMovementSpeed(float movementSpeed)
{
    _movementSpeed = movementSpeed;
}
