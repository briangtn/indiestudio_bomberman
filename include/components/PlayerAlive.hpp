/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PlayerAlive.hpp
*/

/* Created the 13/06/2019 at 08:17 by jfrabel */

#ifndef INDIESTUDIO_PLAYERALIVE_HPP
#define INDIESTUDIO_PLAYERALIVE_HPP

#include "Component.hpp"

namespace indie {

    namespace components {

        class PlayerAlive : public jf::components::Component {
        public:
            PlayerAlive(jf::entities::Entity &entity, int lives = 1);
            ~PlayerAlive() override;

            int getLives() const;
            void setLives(int lives);

            bool isMarkedAsDead() const;
            void setMarkedAsDead(bool markedAsDead);

        private:
            int _lives;
            bool _markedAsDead;
        };
    }
}

#endif //INDIESTUDIO_PLAYERALIVE_HPP
