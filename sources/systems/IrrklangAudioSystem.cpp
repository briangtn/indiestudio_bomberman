/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrklangAudioSystem.cpp
*/

/* Created the 13/05/2019 at 15:41 by jbulteau */

#include "ECSWrapper.hpp"
#include "IrrklangAudioExceptions.hpp"
#include "IrrklangAudioSystem.hpp"
#include "Sound2DComponent.hpp"

indie::systems::IrrklangAudioSystem::IrrklangAudioSystem()
{
    _engine = irrklang::createIrrKlangDevice();
    if (!_engine) {
        throw exceptions::IrrklangAudioDeviceException("Failed to create IrrKlang device.", "indie::systems::IrrklangAudioSystem::IrrklangAudioSystem");
    }
}

indie::systems::IrrklangAudioSystem::~IrrklangAudioSystem()
{
    _engine->drop();
}

void indie::systems::IrrklangAudioSystem::onAwake()
{

}

void indie::systems::IrrklangAudioSystem::onStart()
{
    playSounds();
}

void indie::systems::IrrklangAudioSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::Sound2DComponent>(
            [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<indie::components::Sound2DComponent> component){
                if (component->getState() == components::Sound2DComponent::STARTING) {
                    ECSWrapper ecs;

                    component->setSound(ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().add2DSound(component->getSourceFile()));
                }
                if (component->getShouldBePlayed() && component->getIsPaused()) {
                    component->setIsPaused(false);
                }
                if (!component->getShouldBePlayed() && !component->getIsPaused()) {
                    component->setIsPaused(true);
                }
            });
    _engine->update();
}

void indie::systems::IrrklangAudioSystem::onStop()
{
    pauseSounds(false);
}

void indie::systems::IrrklangAudioSystem::onTearDown()
{

}

irrklang::ISound *indie::systems::IrrklangAudioSystem::add2DSound(const std::string &sourceFile)
{
    return _engine->play2D(sourceFile.c_str(), false, true);
}

void indie::systems::IrrklangAudioSystem::removeSound(irrklang::ISound *sound)
{
    sound->drop();
}

void indie::systems::IrrklangAudioSystem::playSounds(bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::Sound2DComponent>(
            [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Sound2DComponent> component) {
                if (component->getState() == components::Sound2DComponent::STARTED) {
                    component->setShouldBePlayed(true);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::playSounds(components::Sound2DComponent::SoundType soundType, bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::Sound2DComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Sound2DComponent> component) {
                if (component->getState() == components::Sound2DComponent::STARTED && component->getSoundType() == soundType) {
                    component->setShouldBePlayed(true);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::pauseSounds(bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::Sound2DComponent>(
            [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Sound2DComponent> component) {
                if (component->getState() == components::Sound2DComponent::STARTED) {
                    component->setShouldBePlayed(false);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::pauseSounds(components::Sound2DComponent::SoundType soundType, bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::Sound2DComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Sound2DComponent> component) {
                if (component->getState() == components::Sound2DComponent::STARTED && component->getSoundType() == soundType) {
                    component->setShouldBePlayed(false);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::restartSounds(bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::Sound2DComponent>(
            [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Sound2DComponent> component) {
                if (component->getState() == components::Sound2DComponent::STARTED) {
                    component->setPlayPosition(0);
                    component->setShouldBePlayed(true);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::restartSounds(components::Sound2DComponent::SoundType soundType, bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::Sound2DComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Sound2DComponent> component) {
                if (component->getState() == components::Sound2DComponent::STARTED && component->getSoundType() == soundType) {
                    component->setPlayPosition(0);
                    component->setShouldBePlayed(true);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::setSoundsVolume(float volume, bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::Sound2DComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Sound2DComponent> component) {
                if (component->getState() == components::Sound2DComponent::STARTED) {
                    component->setVolume(volume);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::setSoundsVolume(float volume,
                                                          components::Sound2DComponent::SoundType soundType,
                                                          bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::Sound2DComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::Sound2DComponent> component) {
                if (component->getState() == components::Sound2DComponent::STARTED && component->getSoundType() == soundType) {
                    component->setVolume(volume);
                }
            }, onlyEnabled);
}
