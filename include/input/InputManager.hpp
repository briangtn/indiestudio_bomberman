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
        irr::EKEY_CODE positiveKey;
        irr::EKEY_CODE negativeKey;
    };

    struct ControllerKeyAxis {
        irr::u8 id;
        irr::u8 positiveKey;
        irr::u8 negativeKey;
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
        static void CreateAxis(const std::string &name, ControllerKeyAxis);
        static void CreateAxis(const std::string &name, KeyAxis, JoystickAxis);

        static void RegisterKey(irr::EKEY_CODE key);
        static void RegisterKey(irr::u8 controllerId, irr::u8 keyId);

        static bool IsKeyPressed(irr::EKEY_CODE key);
        static bool IsKeyPressed(irr::u8 controllerId, irr::u8 keyId);

        static float GetAxis(const std::string &name);


    private:
        static std::map<std::string, KeyAxis> keyAxes;
        static std::map<std::string, JoystickAxis> joystickAxes;
        static std::map<std::string, ControllerKeyAxis> controllerKeyAxes;
        static std::map<irr::EKEY_CODE, bool> keysStates;
        static std::map<std::string, float> joysticksStates;
        static std::map<irr::u16, bool> controllerKeyStates;
        static jf::internal::ID eventKeyInputID;
        static jf::internal::ID eventJoystickInputID;
        static jf::internal::ID eventControlleKeyInputID;
    };
}

#endif //INDIESTUDIO_INPUTMANAGER_HPP
