/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** AnimatorException.cpp
*/

/* Created the 28/05/2019 at 16:55 by jfrabel */

#include "exceptions/AnimatorException.hpp"

indie::exceptions::AnimatorException::AnimatorException(const std::string &err, const std::string &where)
    : ECSException(err, where)
{

}
