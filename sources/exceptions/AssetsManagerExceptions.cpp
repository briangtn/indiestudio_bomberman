/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** AssetsManagerExceptions.cpp
*/

//
// Created by romainfouyer on 6/4/19.
//

#include "exceptions/AssetsManagerExceptions.hpp"

indie::exceptions::AssetsManagerExceptions::AssetsManagerExceptions(const std::string &err, const std::string &where)
    : ECSException(err, where)
{

}