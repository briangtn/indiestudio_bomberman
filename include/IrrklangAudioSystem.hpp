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
#include <bits/unique_ptr.h>
#include "System.hpp"

/*!
 * @namespace jf
 * @brief The jfecs library
 */
namespace jf {

    namespace systems {

        class IrrklangAudioSystem : public ISystem {
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
            void removeSound(irrklang::ISound *sound);
            void playSounds(bool onlyEnabled = true);
            void stopSounds(bool onlyEnabled = true);

        private:
            irrklang::ISoundEngine *_engine;
        };
    }
}

#endif //INDIESTUDIO_IRRKLANGAUDIOSYSTEM_HPP
