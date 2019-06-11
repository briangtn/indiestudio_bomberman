/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** InputManagerException.cpp
*/

/* Created the 21/05/2019 at 21:06 by brian */

#include "exceptions/InputManagerException.hpp"

indie::InputManagerException::InputManagerException(const std::string &what)
    : _what(what)
{

}

const char *indie::InputManagerException::what() const noexcept
{
    return _what.c_str();
}

indie::AxisNotFoundException::AxisNotFoundException(const std::string &inputName)
    : InputManagerException("Axis not found."), _inputName(inputName)
{

}

std::string indie::AxisNotFoundException::getInputName() const
{
    return _inputName;
}

indie::AxisAlreadyExistException::AxisAlreadyExistException(const std::string &inputName)
    : InputManagerException("Axis already exist."), _inputName(inputName)
{

}

std::string indie::AxisAlreadyExistException::getInputName() const
{
    return _inputName;
}

indie::InvalidAxisType::InvalidAxisType(const std::string &name)
    : InputManagerException("Invalid axis type"),
      _typeName(name)
{

}

std::string indie::InvalidAxisType::getAxisTypeName()
{
    return _typeName;
}

indie::KeyNotFoundException::KeyNotFoundException(const std::string &inputName)
    : InputManagerException("Key not found."), _inputName(inputName)
{

}

std::string indie::KeyNotFoundException::getName() const
{
    return _inputName;
}

indie::KeyAlreadyExistException::KeyAlreadyExistException(const std::string &inputName)
    : InputManagerException("Key already exist."), _inputName(inputName)
{

}

std::string indie::KeyAlreadyExistException::getName() const
{
    return _inputName;
}
