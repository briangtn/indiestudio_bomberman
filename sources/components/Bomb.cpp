/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Bombe
*/

#include "components/Bomb.hpp"

const std::map<int, std::pair<std::string, std::string>> indie::components::Bomb::_pathTextureBomb =
{
    {0, { "./Assets/Bombs/Mesh/NormalBomb.dae.obj", "./Assets/Bombs/Texture/TextureNormalBomb.png"} },
    {1, {"./Assets/Bombs/Mesh/FireBomb.dae.obj", "./Assets/Bombs/Texture/TextureFireBomb.png"} },
    {2, {"./Assets/Bombs/Mesh/WaterBomb.dae.obj", "./Assets/Bombs/Texture/TextureWaterBomb.png"} },
    {3, {"./Assets/Bombs/Mesh/PlasmaBomb.dae.obj", "./Assets/Bombs/Texture/TexturePlasmaBomb.png"} },
    {4, {"./Assets/Bombs/Mesh/SexyBomb.dae.obj", "./Assets/Bombs/Texture/TextureSexyBomb.png"} }
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