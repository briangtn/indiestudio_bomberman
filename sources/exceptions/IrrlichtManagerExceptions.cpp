/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrlichtManagerExceptions.cpp
*/

/* Created the 10/05/2019 at 11:09 by jfrabel */

#include "IrrlichtManagerExceptions.hpp"

jf::exceptions::IrrlichtManagerException::IrrlichtManagerException(const std::string &err, const std::string &where)
    : ECSException(err, where)
{

}

jf::exceptions::IrrlichtManagerDeviceException::IrrlichtManagerDeviceException(const std::string &err,
                                                                               const std::string &where)
    : IrrlichtManagerException(err, where)
{

}

jf::exceptions::IrrlichtManagerVideoDriverException::IrrlichtManagerVideoDriverException(const std::string &err,
                                                                                         const std::string &where)
    : IrrlichtManagerException(err, where)
{

}

jf::exceptions::IrrlichtManagerSceneManagerException::IrrlichtManagerSceneManagerException(const std::string &err,
                                                                                           const std::string &where)
    : IrrlichtManagerException(err, where)
{

}

jf::exceptions::IrrlichtManagerGUIEnvironmentException::IrrlichtManagerGUIEnvironmentException(const std::string &err,
                                                                                               const std::string &where)
    : IrrlichtManagerException(err, where)
{

}