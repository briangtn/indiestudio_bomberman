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
        try {
            generateAxis(baseName + elem.first, elem.second);
        } catch (indie::AxisAlreadyExistException &e) {}
    }
}

void indie::Controller::generateKey(std::string name, indie::Controller::KeyConfig config)
{
    switch (config.type) {
        case KEY:
            try {
                InputManager::RegisterKey(name, config.keyCode);
            } catch (indie::KeyAlreadyExistException &e) {}
            break;
        case CONTROLLERKEY:
            try {
                InputManager::RegisterKey(name, config.controllerId, config.controllerKeyId);
            } catch (indie::KeyAlreadyExistException &e) {}
    break;
        default:
            break;
    }
}

void indie::Controller::generateAxis(std::string name, indie::Controller::AxisConfig config)
{
    switch (config.type) {
        case KEY:
            InputManager::CreateAxis<KeyAxis>(name, config.keyAxis);
            break;
        case JOYSTICK:
            InputManager::CreateAxis<JoystickAxis>(name, config.joystickAxis);
            break;
        case CONTROLLERKEY:
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
