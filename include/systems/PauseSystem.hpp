/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PauseSystem.hpp
*/

/* Created the 15/06/2019 at 18:04 by brian */

#ifndef INDIESTUDIO_PAUSESYSTEM_HPP
#define INDIESTUDIO_PAUSESYSTEM_HPP

#include "System.hpp"
#include "ID.hpp"

namespace indie {
    namespace systems {
        class PauseSystem : public jf::systems::ISystem {
        public:
            PauseSystem();
            ~PauseSystem() override;

            void onAwake() override;
            void onStart() override;
            void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
            void onStop() override;
            void onTearDown() override;
            void destroyButtons();

        private:
            jf::internal::ID _pauseButtonEventID;
            jf::internal::ID _saveEventID;

        };
    };
};

#endif //INDIESTUDIO_PAUSESYSTEM_HPP
