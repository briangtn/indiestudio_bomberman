/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** InputManager.cpp
*/

/* Created the 22/05/2019 at 15:57 by brian */

#include <string>
#include <map>
#include "input/InputManager.hpp"
#include "ECSWrapper.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "events/IrrlichtJoystickInputEvent.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "exceptions/InputManagerException.hpp"

std::map<std::string, indie::KeyAxis> indie::InputManager::keyAxes;
std::map<std::string, indie::JoystickAxis> indie::InputManager::joystickAxes;
std::map<irr::EKEY_CODE, bool> indie::InputManager::keysStates;
std::map<std::string, float> indie::InputManager::joysticksStates;
jf::internal::ID indie::InputManager::eventKeyInputID;
jf::internal::ID indie::InputManager::eventJoystickInputID;

void indie::InputManager::CreateAxis(const std::string &name, indie::KeyAxis axis)
{
    ECSWrapper ecs;

    if (keyAxes.find(name) != keyAxes.end())
        throw AxisAlreadyExistException(name);
    keyAxes.emplace(name, axis);
    if (axis.positiveKey != irr::EKEY_CODE::KEY_KEY_CODES_COUNT)
        keysStates.emplace(axis.positiveKey, false);
    if (axis.negativeKey != irr::EKEY_CODE::KEY_KEY_CODES_COUNT)
        keysStates.emplace(axis.negativeKey, false);

    if (!eventKeyInputID.isValid())
        eventKeyInputID = ecs.eventManager.addListener<void, events::IrrlichtKeyInputEvent>(nullptr, [](void *a, events::IrrlichtKeyInputEvent e){
            for (auto &key : InputManager::keysStates) {
                if (key.first == e.keyCode)
                    key.second = e.wasPressed;
            }
        });
}

void indie::InputManager::CreateAxis(const std::string &name, indie::JoystickAxis axis)
{
    ECSWrapper ecs;

    if (joystickAxes.find(name) != joystickAxes.end())
        throw AxisAlreadyExistException(name);
    joystickAxes.emplace(name, axis);
    joysticksStates.emplace(name, 0.0f);

    if (!eventJoystickInputID.isValid()) {
        eventJoystickInputID = ecs.eventManager.addListener<void, events::IrrlichtJoystickEvent>(nullptr, [](void *a, events::IrrlichtJoystickEvent e){
            for (auto &joystick : InputManager::joysticksStates) {
                auto finded = joystickAxes.find(joystick.first);
                if (finded == joystickAxes.end())
                    break;
                if (finded->second.id == e.data.Joystick) {
                    joystick.second = e.data.Axis[finded->second.axis] / 32767.0f * (finded->second.invert ? -1 : 1);
                    if (abs(joystick.second) < finded->second.deadZone)
                        joystick.second = 0;
                }
            }
        });
    }
}

float indie::InputManager::GetAxis(const std::string &name)
{
    float result = 0;
    auto findedKeyAxis = keyAxes.find(name);
    auto findedJoystickAxis = joystickAxes.find(name);
    bool finded = false;

    if (findedKeyAxis != keyAxes.end()) {
        auto finded = keysStates.find(findedKeyAxis->second.positiveKey);

        if (finded != keysStates.end())
            result += finded->second;
        finded = keysStates.find(findedKeyAxis->second.negativeKey);
        if (finded != keysStates.end())
            result -= finded->second;
        finded = true;
    }
    if (findedJoystickAxis != joystickAxes.end()) {
        ECSWrapper ecs;

        auto finded = joysticksStates.find(name);

        if (finded != joysticksStates.end()) {
            result += finded->second;
        }
        finded = true;
    }
    if (!finded)
        throw AxisNotFoundException(name);
    return result;
}
