/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrlichtJoystickInputEvent.hpp
*/

/* Created the 11/05/2019 at 15:45 by jfrabel */

#ifndef INDIESTUDIO_IRRLICHTJOYSTICKINPUTEVENT_HPP
#define INDIESTUDIO_IRRLICHTJOYSTICKINPUTEVENT_HPP

#include <irrlicht.h>

/*!
 * @namespace jf
 * @brief The jfecs library namespace
 */
namespace jf {

    namespace events {

        struct IrrlichtJoystickEvent {
            irr::SEvent::SJoystickEvent data;
        };

    }
}
#endif //INDIESTUDIO_IRRLICHTJOYSTICKINPUTEVENT_HPP
