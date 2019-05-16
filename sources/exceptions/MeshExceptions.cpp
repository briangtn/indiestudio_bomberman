/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** MeshExceptions
*/

#include "MeshExceptions.hpp"

jf::exceptions::MeshExceptions::MeshExceptions(const std::string &err, const std::string &where)
    : ECSException(err, where)
{
}