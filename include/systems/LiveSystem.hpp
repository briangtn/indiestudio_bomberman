/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** LiveSystem.hpp
*/

/* Created the 13/06/2019 at 10:07 by jfrabel */

#ifndef INDIESTUDIO_LIVESYSTEM_HPP
#define INDIESTUDIO_LIVESYSTEM_HPP

#include <list>
#include "System.hpp"
#include "components/LeaderBoard.hpp"

namespace indie {

    namespace systems {

        class LiveSystem : public jf::systems::ISystem {
        public:
            LiveSystem();
            ~LiveSystem() override;

        public:
            void onAwake() override;
            void onStart() override;
            void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
            void onStop() override;
            void onTearDown() override;

        public:
            void startNewGame();
            void startGame();
            bool isGameLaunched();
            components::LeaderBoard::PlayerLeaderBoard endGame();

        private:
            static constexpr float updateDelta = 0.2f;

        private:
            float _elapsedTime;
            bool _gameLaunched;
        };
    }
}

#endif //INDIESTUDIO_LIVESYSTEM_HPP
