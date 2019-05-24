/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrlichtKeyInputEvent.hpp
*/

/* Created the 10/05/2019 at 10:19 by jfrabel */

#ifndef INDIESTUDIO_IRRLICHTCONTROLLERKEYJUSTCHANGEDEVENT_HPP
#define INDIESTUDIO_IRRLICHTCONTROLLERKEYJUSTCHANGEDEVENT_HPP

#include <irrlicht.h>

namespace indie {

    namespace events {

        struct IrrlichtControllerKeyJustChangedEvent {
            irr::u8 controllerID;
            irr::u8 keyCode;
            bool pressed;
        };
    }
}

#endif //INDIESTUDIO_IRRLICHTKEYINPUTEVENT_HPP
