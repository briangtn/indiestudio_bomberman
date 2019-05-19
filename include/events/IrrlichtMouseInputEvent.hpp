/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrlichtMouseInputEvent.hpp
*/

/* Created the 11/05/2019 at 15:59 by jfrabel */

#ifndef INDIESTUDIO_IRRLICHTMOUSEINPUTEVENT_HPP
#define INDIESTUDIO_IRRLICHTMOUSEINPUTEVENT_HPP

#include <irrlicht.h>

namespace indie {

    namespace events {

        struct IrrlichtMouseInputEvent {
            irr::SEvent::SMouseInput data;
        };

        struct IrrlichtLeftMouseButtonInputEvent {
            bool pressed;
            bool released;
        };

        struct IrrlichtRightMouseButtonInputEvent {
            bool pressed;
            bool released;
        };

        struct IrrlichtMiddleMouseButtonInputEvent {
            bool pressed;
            bool released;
        };

        struct IrrlichtMouseMovedInputEvent {
            int posX;
            int posY;
        };

        struct IrrlichtMouseWheelScrolledInputEvent {
            float delta;
        };
    }
}
#endif //INDIESTUDIO_IRRLICHTMOUSEINPUTEVENT_HPP
