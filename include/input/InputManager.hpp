/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** InputManager.hpp
*/

/* Created the 22/05/2019 at 15:57 by brian */

#ifndef INDIESTUDIO_INPUTMANAGER_HPP
#define INDIESTUDIO_INPUTMANAGER_HPP

#include <irrlicht/Keycodes.h>
#include <irrlicht/IEventReceiver.h>
#include "ID.hpp"

namespace indie {

    struct KeyAxis {
        irr::EKEY_CODE positiveKey = irr::KEY_KEY_CODES_COUNT;
        irr::EKEY_CODE negativeKey = irr::KEY_KEY_CODES_COUNT;
    };

    struct JoystickAxis {
        irr::u8 id;
        irr::u16 axis;
        bool invert = false;
        float deadZone = 0.25;
    };

    using InputSetting = std::map<std::string, KeyAxis>;

    class InputManager {
    public:
        static void CreateAxis(const std::string &name, KeyAxis);
        static void CreateAxis(const std::string &name, JoystickAxis);
        static float GetAxis(const std::string &name);

        //static bool IsKeyPressed(irr::EKEY_CODE keyCode) const;

    private:
        static std::map<std::string, KeyAxis> keyAxes;
        static std::map<std::string, JoystickAxis> joystickAxes;
        static std::map<irr::EKEY_CODE, bool> keysStates;
        static std::map<std::string, float> joysticksStates;
        static jf::internal::ID eventKeyInputID;
        static jf::internal::ID eventJoystickInputID;
    };
}

#endif //INDIESTUDIO_INPUTMANAGER_HPP
