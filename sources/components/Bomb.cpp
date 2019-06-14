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
const float &timeBeforeExplode, indie::components::BombType bomb, indie::components::PlayerType player)
    :   Component(entity),
        _strength(strength),
        _timeBeforeExplode(timeBeforeExplode),
        _bombID(bomb),
        _bombType(bomb),
        _player(player)
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

void indie::components::Bomb::setStrength(const int &newStrength)
{
    _strength = newStrength;
}

float indie::components::Bomb::getTimeBeforeExplode() const
{
    return _timeBeforeExplode;
}

void indie::components::Bomb::setTimeBeforeExplode(const int &newTimeBeforeExplode)
{
    _timeBeforeExplode = newTimeBeforeExplode;
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
    _player = player;
}

indie::components::PlayerType indie::components::Bomb::getPlayerType() const
{
    return _player;
}

indie::components::Bomb &indie::components::Bomb::operator>>(std::ostream &file)
{
    file << R"(        <component type="Bomb">)" << std::endl;
    file << R"(            <argument name="strength" value=")" << _strength << R"("/>)" << std::endl;
    file << R"(            <argument name="timeBeforeExplode" value=")" << _timeBeforeExplode << R"("/>)" << std::endl;
    file << R"(            <argument name="bombType" value=")" << _bombType << R"("/>)" << std::endl;
    file << R"(            <argument name="player" value=")" << _player << R"("/>)" << std::endl;
    file << R"(            <argument name="texturePath" value=")" << _texturePath << R"("/>)" << std::endl;
    file << R"(            <argument name="textureMesh" value=")" << _meshPath << R"("/>)" << std::endl;
    file << R"(            <argument name="position" value=")" << _vectPos << R"("/>)" << std::endl;
    file << "        </component>" << std::endl;
    return *this;
}
