/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** MovementSystem.hpp
*/

/* Created the 24/05/2019 at 13:53 by jfrabel */

#ifndef INDIESTUDIO_MOVEMENTSYSTEM_HPP
#define INDIESTUDIO_MOVEMENTSYSTEM_HPP

#include "System.hpp"

namespace indie {

    namespace systems {

        class MovementSystem : public jf::systems::ISystem {
        public:
            MovementSystem();
            ~MovementSystem() override ;

        public:
            void onAwake() override;
            void onStart() override;
            void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
            void onStop() override;
            void onTearDown() override;

        private:
            void updateRotator(const std::chrono::nanoseconds &elapsedTime) const;
            void updateHoverer(const std::chrono::nanoseconds &elapsedTime) const;
        };
    }
}

#endif //INDIESTUDIO_MOVEMENTSYSTEM_HPP
