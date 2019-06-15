/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PlayerAlive.cpp
*/

/* Created the 13/06/2019 at 08:17 by jfrabel */

#include "Events.hpp"
#include "components/PlayerAlive.hpp"

indie::components::PlayerAlive::PlayerAlive(jf::entities::Entity &entity, int lives)
    : Component(entity), _lives(lives), _markedAsDead(false)
{
    EMIT_CREATE(PlayerAlive);
}

indie::components::PlayerAlive::~PlayerAlive()
{
    EMIT_DELETE(PlayerAlive);
}

int indie::components::PlayerAlive::getLives() const
{
    return _lives;
}

void indie::components::PlayerAlive::setLives(int lives)
{
    _lives = lives;
}

bool indie::components::PlayerAlive::isMarkedAsDead() const
{
    return _markedAsDead;
}

void indie::components::PlayerAlive::setMarkedAsDead(bool markedAsDead)
{
    _markedAsDead = markedAsDead;
}

indie::components::PlayerAlive &indie::components::PlayerAlive::operator>>(std::ostream &file)
{
    file << R"(        <component type="PlayerAlive">)" << std::endl;
    file << R"(            <argument name="lives" value=")" << _lives << R"("/>)" << std::endl;
    file << R"(            <argument name="markedAsDead" value=")" << std::boolalpha << _markedAsDead << R"("/>)" << std::endl;
    file << R"(        </component>)" << std::endl;
    return *this;
}
