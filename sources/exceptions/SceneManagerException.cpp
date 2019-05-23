/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** SceneManagerException.cpp
*/

/* Created the 22/05/2019 at 15:13 by jfrabel */

#include "exceptions/SceneManagerException.hpp"

indie::exceptions::SceneManagerException::SceneManagerException(const std::string &err, const std::string &where)
    : ECSException(err, where)
{

}
