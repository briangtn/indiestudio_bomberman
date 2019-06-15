/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** BombException
*/

#include "exceptions/BombException.hpp"

indie::exceptions::BombException::BombException(const std::string &err, const std::string &where)
    : ECSException(err, where)
{

}