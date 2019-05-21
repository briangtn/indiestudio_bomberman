/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Input.cpp
*/

/* Created the 21/05/2019 at 19:38 by brian */

#include "input/Input.hpp"

indie::Input::Input(std::map<std::string, indie::Axis> axes)
    :   _axes(std::move(axes))
{

}
