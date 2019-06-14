/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Bombe
*/

#include "components/Bomb.hpp"

const std::map<int, std::pair<std::string, std::string>> indie::components::Bomb::_pathTextureBomb =
{
    {0, { "bomb_normal_model", "bomb_normal_texture"} },
    {1, {"bomb_fire_model", "bomb_fire_texture"} },
    {2, {"bomb_water_model", "bomb_water_texture"} },
    {3, {"bomb_plasma_model", "bomb_plasma_texture"} },
    {4, {"bomb_sexy_model", "bomb_sexy_texture"} }
};

indie::components::Bomb::Bomb(jf::entities::Entity &entity, const int &strength,\
const float &timeBeforeExplose, indie::components::BombType bomb, indie::components::PlayerType player)
    :   Component(entity),
        _strength(strength),
        _timeBeforeExplose(timeBeforeExplose),
        _bombID(bomb),
        _bombType(bomb),
        _Player(player)
{
    for (auto &it : _pathTextureBomb)
        if (it.first == _bombID) {
            _texturePath = it.second.second;
            _meshPath = it.second.first;
        }
    EMIT_CREATE(Bomb);
}

indie::components::Bomb::~Bomb()
{
    EMIT_DELETE(Bomb);
}

int indie::components::Bomb::getStrength() const
{
    return _strength;
}

void indie::components::Bomb::setStength(const int &newStrength)
{
    _strength = newStrength;
}

float indie::components::Bomb::getTimeBeforeExplose() const
{
    return _timeBeforeExplose;
}

void indie::components::Bomb::setTimeBeforeExplose(const int &newTimeBeforeExplose)
{
    _timeBeforeExplose = newTimeBeforeExplose;
}

indie::components::BombType indie::components::Bomb::getBombType() const
{
    return _bombType;
}

void indie::components::Bomb::setBombType(indie::components::BombType newBombType)
{
    _bombType = newBombType;
}

std::string indie::components::Bomb::getTexturePath() const
{
    return _texturePath;
}

void indie::components::Bomb::setTexturePath(const std::string &newTexturePath)
{
    _texturePath = newTexturePath;
}

std::string indie::components::Bomb::getTextureMesh() const
{
    return _meshPath;
}

void indie::components::Bomb::setTextureMesh(const std::string &newMeshPath)
{
    _meshPath = newMeshPath;
}

void indie::components::Bomb::setInitialPosition(const indie::maths::Vector3D &vectPos)
{
    _vectPos = vectPos;
}

indie::maths::Vector3D indie::components::Bomb::getInitialPosition() const
{
    return _vectPos;
}

void indie::components::Bomb::setPlayerType(const PlayerType &player)
{
    _Player = player;
}

indie::components::PlayerType indie::components::Bomb::getPlayerType() const
{
    return _Player;
}