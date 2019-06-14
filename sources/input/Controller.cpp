/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Controller.cpp
*/

/* Created the 11/06/2019 at 00:39 by brian */

#include "input/Controller.hpp"

indie::Controller::Controller(const std::string &imagePath,
                              std::map<std::string, indie::Controller::AxisConfig> axes,
                              std::map<std::string, indie::Controller::KeyConfig> keys)
                              : _imagePath(imagePath),
                                _axes(axes),
                                _keys(keys)
{

}

const std::string &indie::Controller::getImagePath() const
{
    return _imagePath;
}

void indie::Controller::setImagePath(const std::string &imagePath)
{
    _imagePath = imagePath;
}

void indie::Controller::addAxis(std::string name, indie::Controller::AxisConfig config)
{
    _axes.emplace(name, config);
}

void indie::Controller::addAxis(const std::string &name, indie::KeyAxis axis)
{
    AxisConfig config = {KEY, axis, {0, 0}, {0, 0}};

    _axes.emplace(name, config);
}

void indie::Controller::addAxis(const std::string &name, indie::ControllerKeyAxis axis)
{
    irr::EKEY_CODE defaultCode = irr::KEY_KEY_CODES_COUNT;
    AxisConfig config = {CONTROLLERKEY, {defaultCode, defaultCode}, axis, {0, 0}};

    _axes.emplace(name, config);
}

void indie::Controller::addAxis(const std::string &name, indie::JoystickAxis axis)
{
    irr::EKEY_CODE defaultCode = irr::KEY_KEY_CODES_COUNT;
    AxisConfig config = {JOYSTICK, {defaultCode, defaultCode}, {0, 0}, axis};

    _axes.emplace(name, config);
}

void indie::Controller::addKey(std::string name, indie::Controller::KeyConfig config)
{
    _keys.emplace(name, config);
}

void indie::Controller::addKey(const std::string &name, irr::EKEY_CODE keyCode)
{
    KeyConfig config = {KEY, keyCode, 0, 0};

    _keys.emplace(name, config);
}

void indie::Controller::addKey(const std::string &name, irr::u8 controllerId, irr::u8 keyId)
{
    KeyConfig config = {CONTROLLERKEY, irr::KEY_KEY_CODES_COUNT, controllerId, keyId};

    _keys.emplace(name, config);
}

const std::map<std::string, indie::Controller::AxisConfig> &indie::Controller::getAxes() const
{
    return _axes;
}

const std::map<std::string, indie::Controller::KeyConfig> &indie::Controller::getKeys() const
{
    return _keys;
}

void indie::Controller::generateKeysAndAxes(const std::string &baseName)
{
    generateKeys(baseName);
    generateAxes(baseName);
}

void indie::Controller::generateKeys(const std::string &baseName)
{
    for (auto &elem : _keys) {
        generateKey(baseName + elem.first, elem.second);
    }
}

void indie::Controller::generateAxes(const std::string &baseName)
{
    for (auto &elem : _axes) {
        generateAxis(baseName + elem.first, elem.second);
    }
}

void indie::Controller::generateKey(std::string name, indie::Controller::KeyConfig config)
{
    try {
        InputManager::UnmapKey(name);
    } catch (KeyNotFoundException e) {
        std::cout << "Touche not found" << std::endl;
    }
    switch (config.type) {
        case KEY:
            InputManager::RegisterKey(name, config.keyCode);
            break;
        case CONTROLLERKEY:
            InputManager::RegisterKey(name, config.controllerId, config.controllerKeyId);
            break;
        default:
            break;
    }
}

void indie::Controller::generateAxis(std::string name, indie::Controller::AxisConfig config)
{
    InputManager::DeleteAxis<KeyAxis, JoystickAxis, ControllerKeyAxis>(name, true);
    switch (config.type) {
        case KEY:
            std::cout << name << std::endl;
            InputManager::CreateAxis<KeyAxis>(name, config.keyAxis);
            break;
        case JOYSTICK:
            std::cout << name << std::endl;
            InputManager::CreateAxis<JoystickAxis>(name, config.joystickAxis);
            break;
        case CONTROLLERKEY:
            std::cout << name << std::endl;
            InputManager::CreateAxis<ControllerKeyAxis>(name, config.controllerKeyAxis);
            break;
    }
}

void indie::Controller::setControllerId(irr::u8 id)
{
    for (auto &elem : _axes) {
        if (elem.second.type == JOYSTICK)
            elem.second.joystickAxis.id = id;
        else if (elem.second.type == CONTROLLERKEY)
            elem.second.controllerKeyAxis.id = id;
    }
    for (auto &elem : _keys) {
        if (elem.second.type == CONTROLLERKEY)
            elem.second.controllerId = id;
    }
}
