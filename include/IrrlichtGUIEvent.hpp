/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrlichtGUIEvent.hpp
*/

/* Created the 12/05/2019 at 13:03 by jfrabel */

#ifndef INDIESTUDIO_IRRLICHTGUIEVENT_HPP
#define INDIESTUDIO_IRRLICHTGUIEVENT_HPP

#include <irrlicht.h>

/*!
 * @namespace jf
 * @brief The jfecs library namespace
 */
namespace jf {

    namespace events {

        struct IrrlichtGUIEvent {
            irr::SEvent::SGUIEvent data;
        };

    }
}

#endif //INDIESTUDIO_IRRLICHTGUIEVENT_HPP
