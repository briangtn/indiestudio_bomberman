/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Scene.cpp
*/

/* Created the 27/05/2019 at 15:27 by jbulteau */

#include "scenes/Scene.hpp"
#include "parser/Parser.hpp"

indie::scenes::Scene::Scene(const std::string &fileName)
    : _fileName(fileName), _listeners()
{

}

void indie::scenes::Scene::onStart()
{
    Parser::getInstance().loadScene(_fileName);
}

void indie::scenes::Scene::onStop()
{

}
