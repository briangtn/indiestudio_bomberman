/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PlayerController.cpp
*/

/* Created the 26/05/2019 at 11:34 by jfrabel */

#include <iomanip>
#include "Events.hpp"
#include "components/PlayerController.hpp"

indie::components::PlayerController::PlayerController(jf::entities::Entity &entity)
    : Component(entity),
      _xMovementAxis(""),
      _yMovementAxis(""),
      _zMovementAxis(""),
      _lockMovementX(false),
      _lockMovementY(true),
      _lockMovementZ(false),
      _movementRelativeToCamera(true),
      _movementSpeed(10.0f),
      _xRotationAxis(""),
      _yRotationAxis(""),
      _zRotationAxis(""),
      _lockRotationX(true),
      _lockRotationY(false),
      _lockRotationZ(true),
      _alwaysLookForward(true),
      _rotationSpeed(25.0f),
      _isWalking(false),
      _idleAnimation("idle"),
      _walkingAnimation("walk"),
      _isTaunting(false),
      _tauntDuration(0.8f),
      _tauntTime(0.0f),
      _tauntButton(""),
      _tauntAnimation("taunt"),
      _isPlacingBomb(false),
      _bombPlacementDuration(1.0f),
      _bombPlacementTime(0.0f),
      _bombPlacementButton(""),
      _bombPlacementAnimation("place bomb"),
      _bombForce(1),
      _maxBomb(3),
      _playerType(P1)
{
    EMIT_CREATE(PlayerController);
}

indie::components::PlayerController::PlayerController(
    jf::entities::Entity &entity,
    const indie::components::PlayerController::PlayerControllerSettings &settings)
    : Component(entity),
      _xMovementAxis(settings.verticalMovementAxis),
      _yMovementAxis(""),
      _zMovementAxis(settings.horizontalMovementAxis),
      _lockMovementX(false),
      _lockMovementY(true),
      _lockMovementZ(false),
      _movementRelativeToCamera(true),
      _movementSpeed(10.0f),
      _xRotationAxis(""),
      _yRotationAxis(""),
      _zRotationAxis(""),
      _lockRotationX(true),
      _lockRotationY(false),
      _lockRotationZ(true),
      _alwaysLookForward(true),
      _rotationSpeed(25.0f),
      _isWalking(false),
      _idleAnimation("idle"),
      _walkingAnimation("walk"),
      _isTaunting(false),
      _tauntDuration(0.8f),
      _tauntTime(0.0f),
      _tauntButton(settings.tauntButton),
      _tauntAnimation("taunt"),
      _isPlacingBomb(false),
      _bombPlacementDuration(1.0f),
      _bombPlacementTime(0.0f),
      _bombPlacementButton(settings.bombButton),
      _bombPlacementAnimation("place bomb"),
      _bombForce(1),
      _maxBomb(3),
      _playerType(P1)
{
    EMIT_CREATE(PlayerController);
}


indie::components::PlayerController::PlayerController(
    jf::entities::Entity &entity,
    const std::string &xAxis, const std::string &yAxis, const std::string &zAxis)
    : Component(entity),
      _xMovementAxis(xAxis),
      _yMovementAxis(yAxis),
      _zMovementAxis(zAxis),
      _lockMovementX(false),
      _lockMovementY(false),
      _lockMovementZ(false),
      _movementRelativeToCamera(true),
      _movementSpeed(10.0f),
      _xRotationAxis(""),
      _yRotationAxis(""),
      _zRotationAxis(""),
      _lockRotationX(false),
      _lockRotationY(false),
      _lockRotationZ(false),
      _alwaysLookForward(true),
      _rotationSpeed(25.0f),
      _isWalking(false),
      _idleAnimation("idle"),
      _walkingAnimation("walk"),
      _isTaunting(false),
      _tauntDuration(0.8f),
      _tauntTime(0.0f),
      _tauntButton(""),
      _tauntAnimation("taunt"),
      _isPlacingBomb(false),
      _bombPlacementDuration(1.0f),
      _bombPlacementTime(0.0f),
      _bombPlacementButton(""),
      _bombPlacementAnimation("place bomb"),
      _bombForce(1),
      _maxBomb(3),
      _playerType(P1)
{
    EMIT_CREATE(PlayerController);
}

indie::components::PlayerController::PlayerController(
    jf::entities::Entity &entity,
    const std::string &xAxis, const std::string &yAxis, const std::string &zAxis,
    bool lockX, bool lockY, bool lockZ)
    : Component(entity),
      _xMovementAxis(xAxis),
      _yMovementAxis(yAxis),
      _zMovementAxis(zAxis),
      _lockMovementX(lockX),
      _lockMovementY(lockY),
      _lockMovementZ(lockZ),
      _movementRelativeToCamera(true),
      _movementSpeed(10.0f),
      _xRotationAxis(""),
      _yRotationAxis(""),
      _zRotationAxis(""),
      _lockRotationX(false),
      _lockRotationY(false),
      _lockRotationZ(false),
      _alwaysLookForward(true),
      _rotationSpeed(25.0f),
      _isWalking(false),
      _idleAnimation("idle"),
      _walkingAnimation("walk"),
      _isTaunting(false),
      _tauntDuration(0.8f),
      _tauntTime(0.0f),
      _tauntButton(""),
      _tauntAnimation("taunt"),
      _isPlacingBomb(false),
      _bombPlacementDuration(1.0f),
      _bombPlacementTime(0.0f),
      _bombPlacementButton(""),
      _bombPlacementAnimation("place bomb"),
      _bombForce(1),
      _maxBomb(3),
      _playerType(P1)
{
    EMIT_CREATE(PlayerController);
}

indie::components::PlayerController::~PlayerController()
{
    EMIT_DELETE(PlayerController);
}

const std::string &indie::components::PlayerController::getXMovementAxis() const
{
    return _xMovementAxis;
}

void indie::components::PlayerController::setXMovementAxis(const std::string &xMovementAxis)
{
    _xMovementAxis = xMovementAxis;
}

const std::string &indie::components::PlayerController::getYMovementAxis() const
{
    return _yMovementAxis;
}

void indie::components::PlayerController::setYMovementAxis(const std::string &yMovementAxis)
{
    _yMovementAxis = yMovementAxis;
}

const std::string &indie::components::PlayerController::getZMovementAxis() const
{
    return _zMovementAxis;
}

void indie::components::PlayerController::setZMovementAxis(const std::string &zMovementAxis)
{
    _zMovementAxis = zMovementAxis;
}

bool indie::components::PlayerController::isLockMovementX() const
{
    return _lockMovementX;
}

void indie::components::PlayerController::setLockMovementX(bool lockMovementX)
{
    _lockMovementX = lockMovementX;
}

bool indie::components::PlayerController::isLockMovementY() const
{
    return _lockMovementY;
}

void indie::components::PlayerController::setLockMovementY(bool lockMovementY)
{
    _lockMovementY = lockMovementY;
}

bool indie::components::PlayerController::isLockMovementZ() const
{
    return _lockMovementZ;
}

void indie::components::PlayerController::setLockMovementZ(bool lockMovementZ)
{
    _lockMovementZ = lockMovementZ;
}

bool indie::components::PlayerController::isMovementRelativeToCamera() const
{
    return _movementRelativeToCamera;
}

void indie::components::PlayerController::setMovementRelativeToCamera(bool movementRelativeToCamera)
{
    _movementRelativeToCamera = movementRelativeToCamera;
}

float indie::components::PlayerController::getMovementSpeed() const
{
    return _movementSpeed;
}

void indie::components::PlayerController::setMovementSpeed(float movementSpeed)
{
    _movementSpeed = movementSpeed;
}

const std::string &indie::components::PlayerController::getXRotationAxis() const
{
    return _xRotationAxis;
}

void indie::components::PlayerController::setXRotationAxis(const std::string &xRotationAxis)
{
    _xRotationAxis = xRotationAxis;
}

const std::string &indie::components::PlayerController::getYRotationAxis() const
{
    return _yRotationAxis;
}

void indie::components::PlayerController::setYRotationAxis(const std::string &yRotationAxis)
{
    _yRotationAxis = yRotationAxis;
}

const std::string &indie::components::PlayerController::getZRotationAxis() const
{
    return _zRotationAxis;
}

void indie::components::PlayerController::setZRotationAxis(const std::string &zRotationAxis)
{
    _zRotationAxis = zRotationAxis;
}

bool indie::components::PlayerController::isLockRotationX() const
{
    return _lockRotationX;
}

void indie::components::PlayerController::setLockRotationX(bool lockRotationX)
{
    _lockRotationX = lockRotationX;
}

bool indie::components::PlayerController::isLockRotationY() const
{
    return _lockRotationY;
}

void indie::components::PlayerController::setLockRotationY(bool lockRotationY)
{
    _lockRotationY = lockRotationY;
}

bool indie::components::PlayerController::isLockRotationZ() const
{
    return _lockRotationZ;
}

void indie::components::PlayerController::setLockRotationZ(bool lockRotationZ)
{
    _lockRotationZ = lockRotationZ;
}

bool indie::components::PlayerController::isAlwaysLookForward() const
{
    return _alwaysLookForward;
}

void indie::components::PlayerController::setAlwaysLookForward(bool alwaysLookForward)
{
    _alwaysLookForward = alwaysLookForward;
}

float indie::components::PlayerController::getRotationSpeed() const
{
    return _rotationSpeed;
}

void indie::components::PlayerController::setRotationSpeed(float rotationSpeed)
{
    _rotationSpeed = rotationSpeed;
}

bool indie::components::PlayerController::isWalking() const
{
    return _isWalking;
}

void indie::components::PlayerController::setIsWalking(bool isWalking)
{
    _isWalking = isWalking;
}

const std::string &indie::components::PlayerController::getIdleAnimation() const
{
    return _idleAnimation;
}

void indie::components::PlayerController::setIdleAnimation(const std::string &idleAnimation)
{
    _idleAnimation = idleAnimation;
}

const std::string &indie::components::PlayerController::getWalkingAnimation() const
{
    return _walkingAnimation;
}

void indie::components::PlayerController::setWalkingAnimation(const std::string &walkingAnimation)
{
    _walkingAnimation = walkingAnimation;
}
bool indie::components::PlayerController::isTaunting() const
{
    return _isTaunting;
}

void indie::components::PlayerController::setIsTaunting(bool isTaunting)
{
    _isTaunting = isTaunting;
}

float indie::components::PlayerController::getTauntTime() const
{
    return _tauntTime;
}

void indie::components::PlayerController::setTauntTime(float tauntTime)
{
    _tauntTime = tauntTime;
}

const std::string &indie::components::PlayerController::getTauntButton() const
{
    return _tauntButton;
}

void indie::components::PlayerController::setTauntButton(const std::string &tauntButton)
{
    _tauntButton = tauntButton;
}

const std::string &indie::components::PlayerController::getTauntAnimation() const
{
    return _tauntAnimation;
}

void indie::components::PlayerController::setTauntAnimation(const std::string &tauntAnimation)
{
    _tauntAnimation = tauntAnimation;
}

bool indie::components::PlayerController::isPlacingBomb() const
{
    return _isPlacingBomb;
}

void indie::components::PlayerController::setIsPlacingBomb(bool isPlacingBomb)
{
    _isPlacingBomb = isPlacingBomb;
}

float indie::components::PlayerController::getBombPlacementTime() const
{
    return _bombPlacementTime;
}

void indie::components::PlayerController::setBombPlacementTime(float bombPlacementTime)
{
    _bombPlacementTime = bombPlacementTime;
}

const std::string &indie::components::PlayerController::getBombPlacementButton() const
{
    return _bombPlacementButton;
}

void indie::components::PlayerController::setBombPlacementButton(const std::string &bombPlacementButton)
{
    _bombPlacementButton = bombPlacementButton;
}

const std::string &indie::components::PlayerController::getBombPlacementAnimation() const
{
    return _bombPlacementAnimation;
}

void indie::components::PlayerController::setBombPlacementAnimation(const std::string &bombPlacementAnimation)
{
    _bombPlacementAnimation = bombPlacementAnimation;
}

float indie::components::PlayerController::getTauntDuration() const
{
    return _tauntDuration;
}

void indie::components::PlayerController::setTauntDuration(float tauntDuration)
{
    _tauntDuration = tauntDuration;
}

float indie::components::PlayerController::getBombPlacementDuration() const
{
    return _bombPlacementDuration;
}

void indie::components::PlayerController::setBombPlacementDuration(float bombPlacementDuration)
{
    _bombPlacementDuration = bombPlacementDuration;
}

int indie::components::PlayerController::getBombForce() const
{
    return _bombForce;
}

void indie::components::PlayerController::setBombForce(int bombForce)
{
    _bombForce = bombForce;
}

int indie::components::PlayerController::getMaxBomb() const
{
    return _maxBomb;
}

void indie::components::PlayerController::setMaxBomb(int maxBomb)
{
    _maxBomb = maxBomb;
}

indie::components::PlayerType indie::components::PlayerController::getPlayerType() const
{
    return _playerType;
}

void indie::components::PlayerController::setPlayerType(indie::components::PlayerType playerType)
{
    _playerType = playerType;
}

indie::components::PlayerController &indie::components::PlayerController::operator>>(std::ostream &file)
{
    file << R"(        <component type="PlayerController">)" << std::endl;
    if (!_xMovementAxis.empty()) {
        file << R"(            <argument name="xMove" value=")" << _xMovementAxis << R"("/>)" << std::endl;
    }
    if (!_yMovementAxis.empty()) {
        file << R"(            <argument name="yMove" value=")" << _yMovementAxis << R"("/>)" << std::endl;
    }
    if (!_zMovementAxis.empty()) {
        file << R"(            <argument name="zMove" value=")" << _zMovementAxis << R"("/>)" << std::endl;
    }
    file << R"(            <argument name="lockXMove" value=")" << std::boolalpha << _lockMovementX << R"("/>)" << std::endl;
    file << R"(            <argument name="lockYMove" value=")" << std::boolalpha << _lockMovementY << R"("/>)" << std::endl;
    file << R"(            <argument name="lockZMove" value=")" << std::boolalpha << _lockMovementZ << R"("/>)" << std::endl;
    file << R"(            <argument name="relativeMove" value=")" << std::boolalpha << _movementRelativeToCamera << R"("/>)" << std::endl;
    file << R"(            <argument name="moveSpeed" value=")" << _movementSpeed << R"("/>)" << std::endl;
    if (!_xRotationAxis.empty()) {
        file << R"(            <argument name="xRotate" value=")" << _xRotationAxis << R"("/>)" << std::endl;
    }
    if (!_yRotationAxis.empty()) {
        file << R"(            <argument name="yRotate" value=")" << _yRotationAxis << R"("/>)" << std::endl;
    }
    if (!_zRotationAxis.empty()) {
        file << R"(            <argument name="zRotate" value=")" << _zRotationAxis << R"("/>)" << std::endl;
    }
    file << R"(            <argument name="lockXRotate" value=")" << std::boolalpha << _lockRotationX << R"("/>)" << std::endl;
    file << R"(            <argument name="lockYRotate" value=")" << std::boolalpha << _lockRotationY << R"("/>)" << std::endl;
    file << R"(            <argument name="lockZRotate" value=")" << std::boolalpha << _lockRotationZ << R"("/>)" << std::endl;
    file << R"(            <argument name="lookForward" value=")" << std::boolalpha << _alwaysLookForward << R"("/>)" << std::endl;
    file << R"(            <argument name="rotateSpeed" value=")" << _rotationSpeed << R"("/>)" << std::endl;
    if (!_idleAnimation.empty()) {
        file << R"(            <argument name="idleAnimation" value=")" << _idleAnimation << R"("/>)" << std::endl;
    }
    if (!_walkingAnimation.empty()) {
        file << R"(            <argument name="walkingAnimation" value=")" << _walkingAnimation << R"("/>)" << std::endl;
    }
    file << R"(            <argument name="isWalking" value=")" << std::boolalpha << _isWalking << R"("/>)" << std::endl;
    file << R"(            <argument name="isTaunting" value=")" << std::boolalpha << _isTaunting << R"("/>)" << std::endl;
    file << R"(            <argument name="tauntTime" value=")" << _tauntTime << R"("/>)" << std::endl;
    if (!_tauntButton.empty()) {
        file << R"(            <argument name="tauntButton" value=")" << _tauntButton << R"("/>)" << std::endl;
    }
    if (!_tauntAnimation.empty()) {
        file << R"(            <argument name="tauntAnimation" value=")" << _tauntAnimation << R"("/>)" << std::endl;
    }
    file << R"(            <argument name="tauntDuration" value=")" << _tauntDuration << R"("/>)" << std::endl;
    file << R"(            <argument name="isPlacingBomb" value=")" << std::boolalpha << _isPlacingBomb << R"("/>)" << std::endl;
    file << R"(            <argument name="bombTime" value=")" << _bombPlacementTime << R"("/>)" << std::endl;
    if (!_bombPlacementButton.empty()) {
        file << R"(            <argument name="bombButton" value=")" << _bombPlacementButton << R"("/>)" << std::endl;
    }
    if (!_bombPlacementAnimation.empty()) {
        file << R"(            <argument name="bombAnimation" value=")" << _bombPlacementAnimation << R"("/>)" << std::endl;
    }
    file << R"(            <argument name="bombDuration" value=")" << _bombPlacementDuration << R"("/>)" << std::endl;
    file << R"(            <argument name="bombForce" value=")" << _bombForce << R"("/>")" << std::endl;
    file << R"(            <argument name="maxBomb" value=")" << _maxBomb << R"("/>")" << std::endl;
    file << "        </component>" << std::endl;
    return *this;
}