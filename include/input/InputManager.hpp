/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** InputManager.hpp
*/

/* Created the 22/05/2019 at 15:57 by brian */

#ifndef INDIESTUDIO_INPUTMANAGER_HPP
#define INDIESTUDIO_INPUTMANAGER_HPP

#include <map>
#include <irrlicht.h>
#include <iostream>
#include "ID.hpp"
#include "exceptions/InputManagerException.hpp"

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
        float offset = 0;
    };

    using InputSetting = std::map<std::string, KeyAxis>;

    class InputManager {
    public:
        static void RegisterKeyInputEvent();
        static void RegisterJoystickInputEvent();
        static void RegisterControllerKeyInputEvent();
        static void CreateAxis(const std::string &name, KeyAxis);
        static void CreateAxis(const std::string &name, JoystickAxis);
        static void CreateAxis(const std::string &name, ControllerKeyAxis);

        template<typename A>
        static void CreateAxis(const std::string &name, A axis)
        {
            if (!isValidAxisTypeId<A>())
                throw InvalidAxisType(typeid(A).name());
            CreateAxis(name, axis);
        }

        template<typename A, typename B, typename... Others>
        static void CreateAxis(const std::string &name, A axis, B nextAxis, Others... axes)
        {
            CreateAxis<A>(name, axis);
            CreateAxis<B, Others...>(name, nextAxis, axes...);
        }

        static void RegisterKey(irr::EKEY_CODE key);
        static void RegisterKey(irr::u8 controllerId, irr::u8 keyId);
        static void RegisterKey(const std::string &name, irr::EKEY_CODE key);
        static void RegisterKey(const std::string &name, irr::u8 controllerId, irr::u8 keyId);

        static void MapKey(const std::string &name, irr::EKEY_CODE key);
        static void MapKey(const std::string &name, irr::u8 controllerId, irr::u8 keyId);
        static void UnmapKey(const std::string &name);

        static bool IsKeyPressed(irr::EKEY_CODE key);
        static bool IsKeyPressed(irr::u8 controllerId, irr::u8 keyId);

        static bool IsKeyPressed(const std::string &name);

        template<typename A>
        static void DeleteAxis(std::map<std::string, A> &map, const std::string &name)
        {
            if (map.find(name) == map.end())
                throw AxisNotFoundException(name);
            map.erase(name);
        }

        template<typename A>
        static void DeleteAxis(const std::string &name, bool checkBeforeDelete = false)
        {
            const std::type_info &ti = typeid(A);

            try {
                if (ti == typeid(KeyAxis)) {
                    DeleteAxis<KeyAxis>(keyAxes, name);
                } else if (ti == typeid(JoystickAxis)) {
                    if (joystickAxes.find(name) == joystickAxes.end())
                        throw AxisNotFoundException(name);
                    joysticksStates.erase(name);
                    joystickAxes.erase(name);
                } else if (ti == typeid(ControllerKeyAxis)) {
                    auto find = controllerKeyAxes.find(name);
                    if (find == controllerKeyAxes.end())
                        throw AxisNotFoundException(name);
                    controllerKeyStates.erase((find->second.id << 8) + find->second.positiveKey);
                    controllerKeyStates.erase((find->second.id << 8) + find->second.negativeKey);
                    controllerKeyAxes.erase(name);
                } else {
                    throw InvalidAxisType(ti.name());
                }
            } catch(AxisNotFoundException e) {
                if (!checkBeforeDelete)
                    throw AxisNotFoundException(e.getInputName());
            }
        }

        template<typename A, typename B, typename... Others>
        static void DeleteAxis(const std::string &name, bool checkBeforeDelete = false)
        {
            DeleteAxis<A>(name, checkBeforeDelete);
            DeleteAxis<B, Others...>(name, checkBeforeDelete);
        }

        template<typename A>
        static void EditAxis(const std::string &name, A axis, bool checkBeforeDelete = false)
        {
            DeleteAxis<A>(name, checkBeforeDelete);
            CreateAxis<A>(name, axis);
        }

        template<typename A, typename B, typename... Others>
        static void EditAxis(const std::string &name, A axis, B nextAxis, Others... others, bool checkBeforeDelete = false)
        {
            DeleteAxis<A, B, Others...>(name, checkBeforeDelete);
            CreateAxis<A, B, Others...>(name, axis, nextAxis, others...);
        }

        static float GetAxis(const std::string &name);

    private:

        template<typename A>
        static bool isValidAxisTypeId()
        {
            const std::type_info &ti = typeid(A);

            if (ti == typeid(KeyAxis))
                return (true);
            else if (ti == typeid(JoystickAxis))
                return (true);
            else if (ti == typeid(ControllerKeyAxis))
                return (true);
            return (false);
        }

    private:
        static std::map<std::string, KeyAxis> keyAxes;
        static std::map<std::string, JoystickAxis> joystickAxes;
        static std::map<std::string, ControllerKeyAxis> controllerKeyAxes;
        static std::map<std::string, irr::EKEY_CODE> nameToKey;
        static std::map<std::string, irr::u16> nameToControllerKey;
        static std::map<irr::EKEY_CODE, bool> keysStates;
        static std::map<std::string, float> joysticksStates;
        static std::map<irr::u16, bool> controllerKeyStates;
        static jf::internal::ID eventKeyInputID;
        static jf::internal::ID eventJoystickInputID;
        static jf::internal::ID eventControlleKeyInputID;
    };
}

#endif //INDIESTUDIO_INPUTMANAGER_HPP
