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
    : InputManagerException("Input not found."), _inputName(inputName)
{

}

std::string indie::AxisNotFoundException::getInputName() const
{
    return _inputName;
}

indie::AxisAlreadyExistException::AxisAlreadyExistException(const std::string &inputName)
    : InputManagerException("Input already exist."), _inputName(inputName)
{

}

std::string indie::AxisAlreadyExistException::getInputName() const
{
    return _inputName;
}
