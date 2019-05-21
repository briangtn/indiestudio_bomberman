/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** InputManager.cpp
*/

/* Created the 21/05/2019 at 19:35 by brian */

#include "input/InputManager.hpp"
#include "exceptions/InputManagerException.hpp"

indie::InputManager *indie::InputManager::instance = nullptr;

indie::InputManager::InputManager()
{

}

indie::InputManager *indie::InputManager::get()
{
    if (InputManager::instance == nullptr)
        InputManager::instance = new InputManager();
    return InputManager::instance;
}

indie::Input indie::InputManager::getInput(const std::string &inputName) const
{
    auto finded = _inputs.find(inputName);

    if (finded == _inputs.end())
        throw InputNotFoundException(inputName);
    return finded->second;
}

float indie::InputManager::getAxis(const std::string &inputName, const std::string &axisName) const
{
    return 0;
}

void indie::InputManager::registerInput(const std::string &inputName, const indie::Input &input)
{
    if (_inputs.find(inputName) != _inputs.end())
        throw InputAlreadyExistException(inputName);
    _inputs.emplace(std::pair<std::string, indie::Input>(inputName, input));
}
