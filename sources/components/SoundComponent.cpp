/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** SoundComponent.cpp
*/

/* Created the 13/05/2019 at 19:00 by jbulteau */

#include "SoundComponent.hpp"
#include "ECSWrapper.hpp"
#include "IrrklangAudioSystem.hpp"
#include "Events.hpp"
#include "SoundComponent.hpp"

/* ================================================================================================================ */
/* ----------------------------------------------------Ctor&Dtor--------------------------------------------------- */
/* ================================================================================================================ */

indie::components::SoundComponent::SoundComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType)
    : Component(entity)
    , _state(STARTING)
    , _sound(nullptr)
    , _sourceFile(sourceFile)
    , _soundType(soundType)
    , _spatialization(false)
    , _shouldBePlayed(false)
    , _position(0, 0, 0)
{
    EMIT_CREATE(SoundComponent);
    std::cout << "Creating " << sourceFile << std::endl;
}

indie::components::SoundComponent::SoundComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType, jf::maths::Vector3D position)
        : Component(entity)
        , _state(STARTING)
        , _sound(nullptr)
        , _sourceFile(sourceFile)
        , _soundType(soundType)
        , _spatialization(true)
        , _shouldBePlayed(false)
        , _position(position)
{
    EMIT_CREATE(SoundComponent);
    std::cout << "Creating " << sourceFile << std::endl;
}

indie::components::SoundComponent::~SoundComponent()
{
    ECSWrapper ecs;

    EMIT_DELETE(SoundComponent);
    ecs.systemManager.getSystem<systems::IrrklangAudioSystem>().removeSound(_sound);
    std::cout << "Destroying " << _sourceFile << std::endl;
}

/* ================================================================================================================ */
/* -----------------------------------------------Setters and Getters---------------------------------------------- */
/* ================================================================================================================ */

const indie::components::SoundComponent::SoundComponentState indie::components::SoundComponent::getState() const
{
    return _state;
}

const irrklang::ISound *indie::components::SoundComponent::getSound() const
{
    return _sound;
}

void indie::components::SoundComponent::setSound(irrklang::ISound *sound)
{
    _sound = sound;
    _state = STARTED;
    std::cout << "Setting sound " << _sourceFile << std::endl;
}

const std::string &indie::components::SoundComponent::getSourceFile() const
{
    return _sourceFile;
}

indie::components::SoundComponent::SoundType indie::components::SoundComponent::getSoundType() const
{
    return _soundType;
}

bool indie::components::SoundComponent::getSpatialization() const
{
    return _spatialization;
}

bool indie::components::SoundComponent::getIsPaused() const
{
    if (_sound) {
        return _sound->getIsPaused();
    }
    return false;
}

void indie::components::SoundComponent::setIsPaused(bool isPaused)
{
    if (_sound) {
        _sound->setIsPaused(isPaused);
    }
}

float indie::components::SoundComponent::getVolume() const
{
    if (_sound) {
        return _sound->getVolume();
    }
    return 0;
}

void indie::components::SoundComponent::setVolume(float volume)
{
    if (_sound) {
        _sound->setVolume(volume);
    }
}

bool indie::components::SoundComponent::getShouldBePlayed() const
{
    return _shouldBePlayed;
}

void indie::components::SoundComponent::setShouldBePlayed(bool shouldBePlayed)
{
    _shouldBePlayed = shouldBePlayed;
}

bool indie::components::SoundComponent::getIsLooped() const
{
    if (_sound) {
        return _sound->isLooped();
    }
    return false;
}

void indie::components::SoundComponent::setIsLooped(bool loop)
{
    if (_sound) {
        _sound->setIsLooped(loop);
    }
}

unsigned int indie::components::SoundComponent::getPlayPosition() const
{
    if (_sound) {
        return _sound->getPlayPosition();
    }
    return 0;
}

void indie::components::SoundComponent::setPlayPosition(unsigned int position)
{
    if (_sound) {
        _sound->setPlayPosition(position);
    }
}

const jf::maths::Vector3D indie::components::SoundComponent::getPosition() const
{
    if (_sound && _spatialization) {
        irrklang::vec3df position = _sound->getPosition();
        return jf::maths::Vector3D(position.X, position.Y, position.Z);
    }
    return _position;
}

void indie::components::SoundComponent::setPosition(const jf::maths::Vector3D &position)
{
    if (_sound && _spatialization) {
        _sound->setPosition(irrklang::vec3df(position.x, position.y, position.z));
    }
}

const jf::maths::Vector3D indie::components::SoundComponent::getVelocity() const
{
    if (_sound && _spatialization) {
        irrklang::vec3df velocity = _sound->getVelocity();
        return jf::maths::Vector3D(velocity.X, velocity.Y, velocity.Z);
    }
    return jf::maths::Vector3D(0, 0, 0);
}

void indie::components::SoundComponent::setVelocity(const jf::maths::Vector3D &velocity)
{
    if (_sound && _spatialization) {
        _sound->setVelocity(irrklang::vec3df(velocity.x, velocity.y, velocity.z));
    }
}
