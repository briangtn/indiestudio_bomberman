/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrklangAudioSystem.cpp
*/

/* Created the 13/05/2019 at 15:41 by jbulteau */

#include <ECSWrapper.hpp>
#include "IrrklangAudioSystem.hpp"
#include "Sound2DComponent.hpp"

jf::systems::IrrklangAudioSystem::IrrklangAudioSystem()
{

}

jf::systems::IrrklangAudioSystem::~IrrklangAudioSystem()
{

}

void jf::systems::IrrklangAudioSystem::onAwake()
{
    _engine = irrklang::createIrrKlangDevice();
}

void jf::systems::IrrklangAudioSystem::onStart()
{
    playSounds();
}

void jf::systems::IrrklangAudioSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    ECSWrapper ecs;

    ecs.entityManager.applyToEach<components::Sound2DComponent>([](jf::entities::EntityHandler entity, components::ComponentHandler<components::Sound2DComponent> component){
        if (component->getState() == jf::components::Sound2DComponent::STARTING) {
            ECSWrapper ecs;

            component->setSound(ecs.systemManager.getSystem<jf::systems::IrrklangAudioSystem>().add2DSound(component->getSourceFile()));
        }
    });
    _engine->update();
}

void jf::systems::IrrklangAudioSystem::onStop()
{
    stopSounds();
}

void jf::systems::IrrklangAudioSystem::onTearDown()
{
    _engine->drop();
}

irrklang::ISound *jf::systems::IrrklangAudioSystem::add2DSound(const std::string &sourceFile)
{
    return _engine->play2D(sourceFile.c_str(), false, true);
}

void jf::systems::IrrklangAudioSystem::removeSound(irrklang::ISound *sound)
{
    sound->drop();
}

void jf::systems::IrrklangAudioSystem::playSounds(bool onlyEnabled)
{

}

void jf::systems::IrrklangAudioSystem::stopSounds(bool onlyEnabled)
{

}
