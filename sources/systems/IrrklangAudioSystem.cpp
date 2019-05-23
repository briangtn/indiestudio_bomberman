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
    playSounds();
}

void indie::systems::IrrklangAudioSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTING && !component->getSpatialization()) {
                    ECSWrapper ecs;
                    component->setSound(ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().add2DSound(component->getSourceFile()));
                } else if (component->getState() == components::SoundComponent::STARTING && component->getSpatialization()) {
                    ECSWrapper ecs;
                    component->setSound(ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().add3DSound(component->getSourceFile(), component->getPosition()));
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

irrklang::ISound *indie::systems::IrrklangAudioSystem::add3DSound(const std::string &sourceFile, indie::maths::Vector3D position)
{
    return _engine->play3D(sourceFile.c_str(), irrklang::vec3df(position.x, position.y, position.z), false, true);
}

void indie::systems::IrrklangAudioSystem::removeSound(jf::components::ComponentHandler<components::SoundComponent> component)
{
    if (component->getSound() != nullptr)
        component->getSound()->drop();
    component->setSound(nullptr);
}

void indie::systems::IrrklangAudioSystem::playSounds(bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED) {
                    component->setShouldBePlayed(true);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::playSounds(components::SoundComponent::SoundType soundType, bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED && component->getSoundType() == soundType) {
                    component->setShouldBePlayed(true);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::pauseSounds(bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED) {
                    component->setShouldBePlayed(false);
                }
            }, onlyEnabled);
}

void indie::systems::IrrklangAudioSystem::pauseSounds(components::SoundComponent::SoundType soundType, bool onlyEnabled)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::SoundComponent>(
            [&](jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::SoundComponent> component) {
                if (component->getState() == components::SoundComponent::STARTED && component->getSoundType() == soundType) {
                    component->setShouldBePlayed(false);
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
                    component->setShouldBePlayed(true);
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
                    component->setShouldBePlayed(true);
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
