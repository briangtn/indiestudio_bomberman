/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrlichtAudioExceptions.cpp
*/

/* Created the 22/05/2019 at 18:41 by jbulteau */

#include "IrrklangAudioExceptions.hpp"

indie::exceptions::IrrklangAudioException::IrrklangAudioException(const std::string &err, const std::string &where)
    : ECSException(err, where)
{

}

indie::exceptions::IrrklangAudioDeviceException::IrrklangAudioDeviceException(const std::string &err,
                                                                              const std::string &where)
    : IrrklangAudioException(err, where)
{

}
