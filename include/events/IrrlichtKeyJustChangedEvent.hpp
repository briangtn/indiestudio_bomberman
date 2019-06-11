/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrlichtKeyInputEvent.hpp
*/

/* Created the 10/05/2019 at 10:19 by jfrabel */

#ifndef INDIESTUDIO_IRRLICHTKEYJUSTCHANGEDEVENT_HPP
#define INDIESTUDIO_IRRLICHTKEYJUSTCHANGEDEVENT_HPP

#include <irrlicht.h>

namespace indie {

    namespace events {

        struct IrrlichtKeyJustChangedEvent {
            irr::EKEY_CODE keyCode;
            bool pressed;
        };
    }
}

#endif //INDIESTUDIO_IRRLICHTKEYINPUTEVENT_HPP
