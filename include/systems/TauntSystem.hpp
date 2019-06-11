/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** TauntSystem.hpp
*/

/* Created the 03/06/2019 at 15:22 by jfrabel */

#ifndef INDIESTUDIO_TAUNTSYSTEM_HPP
#define INDIESTUDIO_TAUNTSYSTEM_HPP

#include "System.hpp"

namespace indie {

    namespace systems {

        class TauntSystem : public jf::systems::ISystem {
        public:
            TauntSystem() = default;
            ~TauntSystem() override = default;

            void onAwake() override;
            void onStart() override;
            void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
            void onStop() override;
            void onTearDown() override;
        };
    }
}

#endif //INDIESTUDIO_TAUNTSYSTEM_HPP
