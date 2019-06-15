/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** BombExplosionEvent
*/

#ifndef BOMBEXPLOSIONEVENT_HPP_
#define BOMBEXPLOSIONEVENT_HPP_

#include "components/Bomb.hpp"

namespace indie {

    namespace events {

        struct BombExplosionEvent{
            indie::components::PlayerType pType;
        };
    }
};

#endif /* !BOMBEXPLOSIONEVENT_HPP_ */
