/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** GameManager.cpp
*/

/* Created the 13/06/2019 at 19:49 by jfrabel */

#include "Events.hpp"
#include "components/GameManager.hpp"

indie::components::GameManager::GameManager(jf::entities::Entity &entity)
    : Component(entity)
{
    EMIT_CREATE(GameManager);
}

indie::components::GameManager::~GameManager()
{
    EMIT_DELETE(GameManager);
}
