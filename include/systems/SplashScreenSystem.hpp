/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** SplashScreenSystem.hpp
*/

/* Created the 16/06/2019 at 22:04 by jfrabel */

#ifndef INDIESTUDIO_SPLASHSCREENSYSTEM_HPP
#define INDIESTUDIO_SPLASHSCREENSYSTEM_HPP

#include "System.hpp"

namespace indie {

    namespace systems {

        class SplashScreenSystem : public jf::systems::ISystem {
        public:
            SplashScreenSystem();
            void onAwake() override;
            void onStart() override;
            void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
            void onStop() override;
            void onTearDown() override;

        private:
            static constexpr float splashScreenTime = 1.5f;

        private:
            float _remainingTime;
        };
    }
}

#endif //INDIESTUDIO_SPLASHSCREENSYSTEM_HPP
