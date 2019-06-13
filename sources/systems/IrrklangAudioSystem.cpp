/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrklangAudioSystem.cpp
*/

/* Created the 13/05/2019 at 15:41 by jbulteau */

#include "components/SoundComponent.hpp"
#include "ECSWrapper.hpp"
#include "maths/Vectors.hpp"
#include "exceptions/IrrklangAudioExceptions.hpp"
#include "systems/IrrklangAudioSystem.hpp"

indie::systems::IrrklangAudioSystem::IrrklangAudioSystem()
{
    _engine = irrklang::createIrrKlangDevice();
    if (!_engine) {
        throw exceptions::IrrklangAudioDeviceException("Failed to create IrrKlang device.", "indie::systems::IrrklangAudioSystem::IrrklangAudioSystem");
    }
}

indie::systems::IrrklangAudioSystem::~IrrklangAudioSystem()
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
        [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
            if (component->getState() == components::SoundComponent::STARTED) {
                ECSWrapper ecs;
                ecs.systemManager.getSystem<IrrklangAudioSystem>().removeSound(component);
            }
        }, false);
    _engine->drop();
}

void indie::systems::IrrklangAudioSystem::onAwake()
{

}

void indie::systems::IrrklangAudioSystem::onStart()
{
}

void indie::systems::IrrklangAudioSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTING && !component->getSpatialization()) {
                    ECSWrapper ecs;
                    component->setSound(ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().add2DSound(component->getSourceFile(), component->getIsLooped(), component->getIsPaused()));
                } else if (component->getState() == components::SoundComponent::STARTING && component->getSpatialization()) {
                    ECSWrapper ecs;
                    component->setSound(ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().add3DSound(component->getSourceFile(), component->getPosition(), component->getIsLooped(), component->getIsPaused()));
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

irrklang::ISound *indie::systems::IrrklangAudioSystem::add2DSound(const std::string &sourceFile, bool playLooped, bool startPaused)
{
    return _engine->play2D(sourceFile.c_str(), playLooped, startPaused, true);
}

irrklang::ISound *indie::systems::IrrklangAudioSystem::add3DSound(const std::string &sourceFile, indie::maths::Vector3D position,
                                                                  bool playLooped, bool startPaused)
{
    return _engine->play3D(sourceFile.c_str(), irrklang::vec3df(position.x, position.y, position.z), playLooped, startPaused, true);
}

void indie::systems::IrrklangAudioSystem::removeSound(jf::components::ComponentHandler<components::SoundComponent> component)
{
    if (component->getSound() != nullptr) {
        component->getSound()->stop();
        component->getSound()->drop();
    }
    component->setSound(nullptr);
}

void indie::systems::IrrklangAudioSystem::playSounds(bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED) {
                    component->setIsPaused(false);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::playSounds(components::SoundComponent::SoundType soundType, bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED && component->getSoundType() == soundType) {
                    component->setIsPaused(false);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::pauseSounds(bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED) {
                    component->setIsPaused(true);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::pauseSounds(components::SoundComponent::SoundType soundType, bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED && component->getSoundType() == soundType) {
                    component->setIsPaused(true);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::restartSounds(bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED) {
                    component->setPlayPosition(0);
                    component->setIsPaused(false);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::restartSounds(components::SoundComponent::SoundType soundType, bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED && component->getSoundType() == soundType) {
                    component->setPlayPosition(0);
                    component->setIsPaused(false);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::setSoundsVolume(float volume, bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED) {
                    component->setVolume(volume);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::setSoundsVolume(float volume,
                                                          components::SoundComponent::SoundType soundType,
                                                          bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED && component->getSoundType() == soundType) {
                    component->setVolume(volume);
                }
            }, onlyEnabled);
}
