/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Bombe
*/

#include "components/Bomb.hpp"

const std::map<int, std::string> indie::components::Bomb::_pathTextureBomb =
{
    {0, "Assets/Bombs/model_ob001_bomb.fbx"},
    {1, "Assets/Bombd/model_ob007_golembomb.fbx"},
    {2, "Assets/Bombs/model_ob006_magnetbomb.fbx"},
    {3, "Assets/Bombs/model_ob010_plasmabomb.fbx"},
    {4, "Assets/Bombs/model_ob009_sexybomb.fbx"},
    {5, "Assets/Bombd/model_ob101_misobomb.fbx"}
};

indie::components::Bomb::Bomb(jf::entities::Entity &entity, const int &strength,\
const float &timeBeforeExplose, indie::components::BombType bomb)
    :   Component(entity),
        _strength(strength),
        _timeBeforeExplose(timeBeforeExplose),
        _bombID(bomb),        
        _bombType(bomb)
{
    for (auto &it : _pathTextureBomb)
        if (it.first == _bombID)
            _texturePath = it.second;
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