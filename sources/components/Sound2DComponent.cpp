/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** 2DSoundComponent.cpp
*/

/* Created the 13/05/2019 at 19:00 by jbulteau */

#include <ECSWrapper.hpp>
#include <IrrklangAudioSystem.hpp>
#include "Events.hpp"
#include "Sound2DComponent.hpp"

/* ================================================================================================================ */
/* ----------------------------------------------------Ctor&Dtor--------------------------------------------------- */
/* ================================================================================================================ */

jf::components::Sound2DComponent::Sound2DComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType)
    : Component(entity), _state(STARTING), _sourceFile(sourceFile), _soundType(soundType), _shouldBePlayed(false)
{
    EMIT_CREATE(Sound2DComponent);
}

jf::components::Sound2DComponent::~Sound2DComponent()
{
    ECSWrapper ecs;

    ecs.systemManager.getSystem<jf::systems::IrrklangAudioSystem>().removeSound(_sound);
    EMIT_DELETE(Sound2DComponent);
}

/* ================================================================================================================ */
/* -----------------------------------------------Setters and Getters---------------------------------------------- */
/* ================================================================================================================ */

const jf::components::Sound2DComponent::Sound2DComponentState jf::components::Sound2DComponent::getState() const
{
    return _state;
}

const irrklang::ISound *jf::components::Sound2DComponent::getSound() const
{
    return _sound;
}

void jf::components::Sound2DComponent::setSound(irrklang::ISound *sound)
{
    _sound = sound;
    _state = STARTED;
}

const std::string &jf::components::Sound2DComponent::getSourceFile() const
{
    return _sourceFile;
}

jf::components::Sound2DComponent::SoundType jf::components::Sound2DComponent::getSoundType() const
{
    return _soundType;
}

bool jf::components::Sound2DComponent::getIsPaused() const
{
    return _sound->getIsPaused();
}

void jf::components::Sound2DComponent::setIsPaused(bool isPaused)
{
    _sound->setIsPaused(isPaused);
}

float jf::components::Sound2DComponent::getVolume() const
{
    return _sound->getVolume();
}

void jf::components::Sound2DComponent::setVolume(float volume)
{
    _sound->setVolume(volume);
}

bool jf::components::Sound2DComponent::getShouldBePlayed() const
{
    return _shouldBePlayed;
}

void jf::components::Sound2DComponent::setShouldBePlayed(bool shouldBePlayed)
{
    _shouldBePlayed = shouldBePlayed;
}

bool jf::components::Sound2DComponent::getIsLooped() const
{
    return _sound->isLooped();
}

void jf::components::Sound2DComponent::setIsLooped(bool loop)
{
    _sound->setIsLooped(loop);
}
