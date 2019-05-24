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
#include "events/IrrlichtKeyJustChangedEvent.hpp"
#include "events/IrrlichtControllerKeyJustChangedEvent.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "exceptions/InputManagerException.hpp"

std::map<std::string, indie::KeyAxis> indie::InputManager::keyAxes;
std::map<std::string, indie::JoystickAxis> indie::InputManager::joystickAxes;
std::map<std::string, indie::ControllerKeyAxis> indie::InputManager::controllerKeyAxes;
std::map<irr::EKEY_CODE, bool> indie::InputManager::keysStates;
std::map<std::string, float> indie::InputManager::joysticksStates;
std::map<irr::u16, bool> indie::InputManager::controllerKeyStates;
jf::internal::ID indie::InputManager::eventKeyInputID;
jf::internal::ID indie::InputManager::eventJoystickInputID;
jf::internal::ID indie::InputManager::eventControlleKeyInputID;

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

    RegisterKeyInputEvent();
}

void indie::InputManager::CreateAxis(const std::string &name, indie::JoystickAxis axis)
{
    ECSWrapper ecs;

    if (joystickAxes.find(name) != joystickAxes.end())
        throw AxisAlreadyExistException(name);
    joystickAxes.emplace(name, axis);
    joysticksStates.emplace(name, 0.0f);

    RegisterJoystickInputInputEvent();
}

void indie::InputManager::CreateAxis(const std::string &name, indie::ControllerKeyAxis axis)
{
    ECSWrapper ecs;

    if (controllerKeyAxes.find(name) != controllerKeyAxes.end())
        throw AxisAlreadyExistException(name);
    controllerKeyAxes.emplace(name, axis);
    controllerKeyStates.emplace((axis.id << 8) + axis.positiveKey, false);
    controllerKeyStates.emplace((axis.id << 8) + axis.negativeKey, false);

    RegisterControllerKeyInputEvent();
}

void indie::InputManager::CreateAxis(const std::string &name, indie::KeyAxis keyAxis, indie::JoystickAxis joyAxis)
{
    CreateAxis(name, keyAxis);
    CreateAxis(name, joyAxis);
}

float indie::InputManager::GetAxis(const std::string &name)
{
    float result = 0;
    auto findedKeyAxis = keyAxes.find(name);
    auto findedJoystickAxis = joystickAxes.find(name);
    auto findedControllerKeyAxis = controllerKeyAxes.find(name);
    bool isFinded = false;

    if (findedKeyAxis != keyAxes.end()) {
        auto finded = keysStates.find(findedKeyAxis->second.positiveKey);

        if (finded != keysStates.end())
            result += finded->second;
        finded = keysStates.find(findedKeyAxis->second.negativeKey);
        if (finded != keysStates.end())
            result -= finded->second;
        isFinded = true;
    }
    if (findedControllerKeyAxis != controllerKeyAxes.end()) {
        irr::u8 controllerId = findedControllerKeyAxis->second.id;
        irr::u8 keyId = findedControllerKeyAxis->second.positiveKey;
        auto finded = controllerKeyStates.find((controllerId << 8) + keyId);

        if (finded != controllerKeyStates.end())
            result += finded->second;
        keyId = findedControllerKeyAxis->second.negativeKey;
        finded = controllerKeyStates.find((controllerId << 8) + keyId);
        if (finded != controllerKeyStates.end())
            result -= finded->second;
        isFinded = true;
    }
    if (findedJoystickAxis != joystickAxes.end()) {
        ECSWrapper ecs;

        auto finded = joysticksStates.find(name);

        if (finded != joysticksStates.end()) {
            result += finded->second;
        }
        isFinded = true;
    }
    if (!isFinded)
        throw AxisNotFoundException(name);
    return (result < -1) ? -1 : ((result > 1) ? 1 : result);
}

void indie::InputManager::RegisterKey(irr::EKEY_CODE key)
{
    keysStates.emplace(key, false);

    RegisterKeyInputEvent();
}

void indie::InputManager::RegisterKey(irr::u8 controllerId, irr::u8 keyId)
{
    controllerKeyStates.emplace((controllerId << 8) + keyId, false);

    RegisterControllerKeyInputEvent();
}

bool indie::InputManager::IsKeyPressed(irr::EKEY_CODE key)
{
    return keysStates[key];
}

bool indie::InputManager::IsKeyPressed(irr::u8 controllerId, irr::u8 keyId)
{
    return controllerKeyStates[(controllerId << 8) + keyId];
}

void indie::InputManager::RegisterKeyInputEvent()
{
    ECSWrapper ecs;
    if (!eventKeyInputID.isValid())
        eventKeyInputID = ecs.eventManager.addListener<void, events::IrrlichtKeyInputEvent>(nullptr, [](void *a, events::IrrlichtKeyInputEvent e){
            ECSWrapper ecs;

            for (auto &key : InputManager::keysStates) {
                if (key.first == e.keyCode) {
                    if (key.second != e.wasPressed) {
                        ecs.eventManager.emit(events::IrrlichtKeyJustChangedEvent({key.first, e.wasPressed}));
                    }
                    key.second = e.wasPressed;
                }
            }
        });
}

void indie::InputManager::RegisterJoystickInputInputEvent()
{
    ECSWrapper ecs;

    if (!eventJoystickInputID.isValid()) {
        eventJoystickInputID = ecs.eventManager.addListener<void, events::IrrlichtJoystickEvent>(nullptr, [](void *a, events::IrrlichtJoystickEvent e) {
            for (auto &joystick : InputManager::joysticksStates) {
                auto finded = joystickAxes.find(joystick.first);
                if (finded == joystickAxes.end())
                    break;
                if (finded->second.id == e.data.Joystick) {
                    joystick.second = e.data.Axis[finded->second.axis] / 32767.0f * (finded->second.invert ? -1 : 1);
                    joystick.second += finded->second.offset;
                    if (abs(joystick.second) < finded->second.deadZone)
                        joystick.second = 0;
                }
            }
        });
    }
}

void indie::InputManager::RegisterControllerKeyInputEvent()
{
    ECSWrapper ecs;

    if (!eventControlleKeyInputID.isValid()) {
        eventControlleKeyInputID = ecs.eventManager.addListener<void, events::IrrlichtJoystickEvent>(nullptr, [](void *a, events::IrrlichtJoystickEvent e) {
            ECSWrapper ecs;
            for (auto &key : InputManager::controllerKeyStates) {
                irr::u8 id = key.first >> 8;
                irr::u8 keyId = key.first & 0x0f;
                if (id == e.data.Joystick) {
                    bool pressed = e.data.IsButtonPressed(keyId);
                    if (key.second != pressed)
                        ecs.eventManager.emit(events::IrrlichtControllerKeyJustChangedEvent({id, keyId, pressed}));
                    key.second = pressed;
                }
            }
        });
    }
}

