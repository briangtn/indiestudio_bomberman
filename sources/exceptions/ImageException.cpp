/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** ImageException.cpp
*/

#include "exceptions/ImageException.hpp"

indie::ImageException::ImageException(const std::string &what)
    : _what(what)
{
}

const char* indie::ImageException::what() const noexcept
{
    return _what.c_str();
}