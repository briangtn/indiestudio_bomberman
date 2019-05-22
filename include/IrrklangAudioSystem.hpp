/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrklangAudioSystem.hpp
*/

/* Created the 13/05/2019 at 15:41 by jbulteau */

#ifndef INDIESTUDIO_IRRKLANGAUDIOSYSTEM_HPP
#define INDIESTUDIO_IRRKLANGAUDIOSYSTEM_HPP

#include <irrKlang.h>
#include "System.hpp"
#include "ASoundComponent.hpp"

namespace indie {

    namespace systems {

        class IrrklangAudioSystem : public jf::systems::ISystem {
        public:
            IrrklangAudioSystem();
            ~IrrklangAudioSystem();

        public:
            void onAwake() override;
            void onStart() override;
            void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
            void onStop() override;
            void onTearDown() override;

        public:
            irrklang::ISound *add2DSound(const std::string &sourceFile);
            irrklang::ISound *add3DSound(const std::string &sourceFile, jf::maths::Vector3D position);
            void removeSound(irrklang::ISound *sound);
            void playSounds(bool onlyEnabled = true);
            void playSounds(components::ASoundComponent::SoundType soundType, bool onlyEnabled = true);
            void pauseSounds(bool onlyEnabled = true);
            void pauseSounds(components::ASoundComponent::SoundType soundType, bool onlyEnabled = true);
            void restartSounds(bool onlyEnabled = true);
            void restartSounds(components::ASoundComponent::SoundType soundType, bool onlyEnabled = true);
            void setSoundsVolume(float volume, bool onlyEnabled = true);
            void setSoundsVolume(float volume, components::ASoundComponent::SoundType soundType, bool onlyEnabled = true);

        private:
            irrklang::ISoundEngine *_engine;
        };
    }
}

#endif //INDIESTUDIO_IRRKLANGAUDIOSYSTEM_HPP
