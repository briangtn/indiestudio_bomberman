/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrlichtKeyInputEvent.hpp
*/

/* Created the 10/05/2019 at 10:19 by jfrabel */

#ifndef INDIESTUDIO_IRRLICHTKEYINPUTEVENT_HPP
#define INDIESTUDIO_IRRLICHTKEYINPUTEVENT_HPP

#include <irrlicht.h>

#define EMIT_SPECIFIC_KEY(key, pressed, shift, ctrl) (ecs.eventManager.emit(jf::events::IrrlichtSpecifiedKeyInputEvent<(key)>({(pressed), !(pressed), (shift), (ctrl)})))

/*!
 * @namespace jf
 * @brief The jfecs library namespace
 */
namespace jf {

    namespace events {

        class IrrlichtKeyInputEvent {
        public:
            irr::EKEY_CODE keyCode;
            bool wasPressed;
            bool wasReleased;
            bool shiftActivated;
            bool ctrlActivated;
        };

        template<irr::EKEY_CODE code>
        class IrrlichtSpecifiedKeyInputEvent {
        public:
            static const irr::EKEY_CODE keyCode = code;
            bool wasPressed;
            bool wasReleased;
            bool shiftActivated;
            bool ctrlActivated;
        };
    }
}

#endif //INDIESTUDIO_IRRLICHTKEYINPUTEVENT_HPP
