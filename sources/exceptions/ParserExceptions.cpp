/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** ParserExceptions.cpp
*/

/* Created the 27/05/2019 at 16:39 by jbulteau */

#include "exceptions/ParserExceptions.hpp"

indie::exceptions::ParserException::ParserException(const std::string &err, const std::string &where)
    : ECSException(err, where)
{

}

indie::exceptions::ParserDeviceException::ParserDeviceException(const std::string &err, const std::string &where)
    : ParserException(err, where)
{

}

indie::exceptions::ParserInvalidFileException::ParserInvalidFileException(const std::string &err,
                                                                          const std::string &where)
    : ParserException(err, where)
{

}
