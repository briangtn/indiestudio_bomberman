/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Scene.cpp
*/

/* Created the 27/05/2019 at 15:27 by jbulteau */

#include "scenes/Scene.hpp"

indie::scenes::Scene::Scene(const std::string &name, const std::string &fileName)
    : _name(name), _fileName(fileName), _listeners()
{

}

void indie::scenes::Scene::onStart()
{

}

void indie::scenes::Scene::onStop()
{

}
