/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** ASoundComponent.cpp
*/

/* Created the 13/05/2019 at 19:00 by jbulteau */

#include "ECSWrapper.hpp"
#include "IrrklangAudioSystem.hpp"
#include "Events.hpp"
#include "ASoundComponent.hpp"

/* ================================================================================================================ */
/* ----------------------------------------------------Ctor&Dtor--------------------------------------------------- */
/* ================================================================================================================ */

indie::components::ASoundComponent::ASoundComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType)
    : Component(entity)
    , _state(STARTING)
    , _sound(nullptr)
    , _sourceFile(sourceFile)
    , _soundType(soundType)
    , _shouldBePlayed(false)
{
    EMIT_CREATE(ASoundComponent);
}

indie::components::ASoundComponent::~ASoundComponent()
{
    ECSWrapper ecs;

    EMIT_DELETE(ASoundComponent);
    ecs.systemManager.getSystem<systems::IrrklangAudioSystem>().removeSound(_sound);
}

/* ================================================================================================================ */
/* -----------------------------------------------Setters and Getters---------------------------------------------- */
/* ================================================================================================================ */

const indie::components::ASoundComponent::SoundComponentState indie::components::ASoundComponent::getState() const
{
    return _state;
}

const irrklang::ISound *indie::components::ASoundComponent::getSound() const
{
    return _sound;
}

void indie::components::ASoundComponent::setSound(irrklang::ISound *sound)
{
    _sound = sound;
    _state = STARTED;
}

const std::string &indie::components::ASoundComponent::getSourceFile() const
{
    return _sourceFile;
}

indie::components::ASoundComponent::SoundType indie::components::ASoundComponent::getSoundType() const
{
    return _soundType;
}

bool indie::components::ASoundComponent::getIsPaused() const
{
    if (_sound) {
        return _sound->getIsPaused();
    }
    return false;
}

void indie::components::ASoundComponent::setIsPaused(bool isPaused)
{
    if (_sound) {
        _sound->setIsPaused(isPaused);
    }
}

float indie::components::ASoundComponent::getVolume() const
{
    if (_sound) {
        return _sound->getVolume();
    }
    return 0;
}

void indie::components::ASoundComponent::setVolume(float volume)
{
    if (_sound) {
        _sound->setVolume(volume);
    }
}

bool indie::components::ASoundComponent::getShouldBePlayed() const
{
    return _shouldBePlayed;
}

void indie::components::ASoundComponent::setShouldBePlayed(bool shouldBePlayed)
{
    _shouldBePlayed = shouldBePlayed;
}

bool indie::components::ASoundComponent::getIsLooped() const
{
    if (_sound) {
        return _sound->isLooped();
    }
    return false;
}

void indie::components::ASoundComponent::setIsLooped(bool loop)
{
    if (_sound) {
        _sound->setIsLooped(loop);
    }
}

unsigned int indie::components::ASoundComponent::getPlayPosition() const
{
    if (_sound) {
        return _sound->getPlayPosition();
    }
    return 0;
}

void indie::components::ASoundComponent::setPlayPosition(unsigned int position)
{
    if (_sound) {
        _sound->setPlayPosition(position);
    }
}

const jf::maths::Vector3D indie::components::ASoundComponent::getPosition() const
{
    return jf::maths::Vector3D(0, 0, 0);
}

void indie::components::ASoundComponent::setPosition(const jf::maths::Vector3D &position)
{

}

const jf::maths::Vector3D indie::components::ASoundComponent::getVelocity() const
{
    return jf::maths::Vector3D(0, 0, 0);
}

void indie::components::ASoundComponent::setVelocity(const jf::maths::Vector3D &velocity)
{

}
