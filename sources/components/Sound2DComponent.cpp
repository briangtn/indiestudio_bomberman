/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** 2DSoundComponent.cpp
*/

/* Created the 13/05/2019 at 19:00 by jbulteau */

#include "ECSWrapper.hpp"
#include "IrrklangAudioSystem.hpp"
#include "Events.hpp"
#include "Sound2DComponent.hpp"

/* ================================================================================================================ */
/* ----------------------------------------------------Ctor&Dtor--------------------------------------------------- */
/* ================================================================================================================ */

indie::components::Sound2DComponent::Sound2DComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType)
    : Component(entity)
    , _state(STARTING)
    , _sound(nullptr)
    , _sourceFile(sourceFile)
    , _soundType(soundType)
    , _shouldBePlayed(false)
{
    EMIT_CREATE(Sound2DComponent);
}

indie::components::Sound2DComponent::~Sound2DComponent()
{
    ECSWrapper ecs;

    EMIT_DELETE(Sound2DComponent);
    ecs.systemManager.getSystem<systems::IrrklangAudioSystem>().removeSound(_sound);
}

/* ================================================================================================================ */
/* -----------------------------------------------Setters and Getters---------------------------------------------- */
/* ================================================================================================================ */

const indie::components::Sound2DComponent::Sound2DComponentState indie::components::Sound2DComponent::getState() const
{
    return _state;
}

const irrklang::ISound *indie::components::Sound2DComponent::getSound() const
{
    return _sound;
}

void indie::components::Sound2DComponent::setSound(irrklang::ISound *sound)
{
    _sound = sound;
    _state = STARTED;
}

const std::string &indie::components::Sound2DComponent::getSourceFile() const
{
    return _sourceFile;
}

indie::components::Sound2DComponent::SoundType indie::components::Sound2DComponent::getSoundType() const
{
    return _soundType;
}

bool indie::components::Sound2DComponent::getIsPaused() const
{
    if (_sound) {
        return _sound->getIsPaused();
    }
    return false;
}

void indie::components::Sound2DComponent::setIsPaused(bool isPaused)
{
    if (_sound) {
        _sound->setIsPaused(isPaused);
    }
}

float indie::components::Sound2DComponent::getVolume() const
{
    if (_sound) {
        return _sound->getVolume();
    }
    return 0;
}

void indie::components::Sound2DComponent::setVolume(float volume)
{
    if (_sound) {
        _sound->setVolume(volume);
    }
}

bool indie::components::Sound2DComponent::getShouldBePlayed() const
{
    return _shouldBePlayed;
}

void indie::components::Sound2DComponent::setShouldBePlayed(bool shouldBePlayed)
{
    _shouldBePlayed = shouldBePlayed;
}

bool indie::components::Sound2DComponent::getIsLooped() const
{
    if (_sound) {
        return _sound->isLooped();
    }
    return false;
}

void indie::components::Sound2DComponent::setIsLooped(bool loop)
{
    if (_sound) {
        _sound->setIsLooped(loop);
    }
}

unsigned int indie::components::Sound2DComponent::getPlayPosition() const
{
    if (_sound) {
        return _sound->getPlayPosition();
    }
    return 0;
}

void indie::components::Sound2DComponent::setPlayPosition(unsigned int position)
{
    if (_sound) {
        _sound->setPlayPosition(position);
    }
}