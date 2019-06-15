/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** AIController
*/

#include "ECSWrapper.hpp"
#include "events/IrrlichtAnimationEndEvent.hpp"
#include "events/HasReachedTarget.hpp"
#include "components/AIController.hpp"
#include "systems/BombManagerSystem.hpp"
#include "events/BombExplosionEvent.hpp"

indie::components::AIController::AIController(jf::entities::Entity &entity)
    : Component(entity), 
      _target(0, 0, 0),
      _previousPos({0, 0}),
      _isTaunting(false),
      _needToTaunt(false),
      _isPlacingBomb(false),
      _needToUseBomb(false),
      _hasTarget(false),
      _state(UNKNOWN),
      _lastState(UNKNOWN),
      _fullNodePath(),
      _hasBombWaitingToExplode(false),
      _movementSpeed(30),
      _bombForce(2),
      _maxBomb(3),
      _playerType(P1)
{
    ECSWrapper ecs;

    _endAnimationListenerEventId = ecs.eventManager.addListener<AIController, events::IrrlichtAnimationEndEvent>(this, [](AIController *a, events::IrrlichtAnimationEndEvent e) {
        if (a->getEntity()->getID() == e.entityId) {
            if (e.animationName == "taunt")
                a->setIsTaunting(false);
            else if (e.animationName == "place bomb")
                a->setIsPlacingBombs(false);
        }      
    });
    _reachTargetListenerEventId = ecs.eventManager.addListener<AIController, events::HasReachedTarget>(this, [](AIController *a, events::HasReachedTarget e){
        if (a->getEntity()->getID() == e.mtt->getEntity()->getID()) {
            if ((a->getHasTarget() && e.mtt->getTarget() == a->getFinalTarget(a->getFullNodePath())) || a->getState() == SURVIVE) {
                a->setHasTarget(false);
                return;
            } else {
                ECSWrapper ecs;
                a->setHasTarget(false);
                a->setHasBombWaitingToExplode(true);
                ecs.systemManager.getSystem<indie::systems::BombManagerSystem>().createBomb(a->getEntity());
                auto animator = a->getEntity()->getComponent<components::Animator>();

                if (animator.isValid()) {
                    animator->setCurrentAnimation("place bomb");
                    a->setIsPlacingBombs(true);
                } else {
                    a->setIsPlacingBombs(false);
                }
            }
        }
    });
    _bombExplosion = ecs.eventManager.addListener<AIController, events::BombExplosionEvent>(this, [](AIController *a, events::BombExplosionEvent e){
        if (e.pType == a->getPlayerType()) {
            a->setHasBombWaitingToExplode(false);
        }
    });
    EMIT_CREATE(AIController);
}

indie::components::AIController::~AIController()
{
    EMIT_DELETE(AIController);
    ECSWrapper ecs;
    ecs.eventManager.removeListener(_endAnimationListenerEventId);
    ecs.eventManager.removeListener(_reachTargetListenerEventId);
    ecs.eventManager.removeListener(_bombExplosion);
}

indie::maths::Vector3D indie::components::AIController::getFinalTarget(std::vector<ai::AStar::Node> fullPath) const
{
    if (fullPath.empty())
        return {0, 0, 0};
    return (fullPath.back().toWorldPos());
}

void indie::components::AIController::setHasBombWaitingToExplode(bool assign)
{
    _hasBombWaitingToExplode = assign;
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

void indie::components::AIController::setFullNodePath(std::vector<ai::AStar::Node> assign)
{
    _fullNodePath = assign;
}

void indie::components::AIController::setHasTarget(bool assign)
{
    _hasTarget = assign;
}

bool indie::components::AIController::getHasTarget() const
{
    return _hasTarget;
}

bool indie::components::AIController::getHasBombWaitingToExplode() const
{
    return _hasBombWaitingToExplode;
}

std::vector<indie::ai::AStar::Node> indie::components::AIController::getFullNodePath() const
{
    return _fullNodePath;
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

indie::components::AIController &indie::components::AIController::operator>>(std::ostream &file)
{
    file << R"(        <component type="AIController">)" << std::endl;
    file << R"(        </component>)" << std::endl;
    return *this;
}
