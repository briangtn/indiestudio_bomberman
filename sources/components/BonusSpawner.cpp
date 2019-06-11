/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** BonusSpawner.cpp
*/

/* Created the 05/06/2019 at 21:51 by jfrabel */

#include "Events.hpp"
#include "components/BonusSpawner.hpp"

indie::components::BonusSpawner::BonusSpawner(jf::entities::Entity &entity, BonusSpawnerType spawnerType, BonusType bonusType)
    : Component(entity), _spawnerType(spawnerType), _bonusType(bonusType)
{
    EMIT_CREATE(BonusSpawner);
}

indie::components::BonusSpawner::~BonusSpawner()
{
    EMIT_DELETE(BonusSpawner);
}

indie::components::BonusSpawner::BonusSpawnerType indie::components::BonusSpawner::getSpawnerType() const
{
    return _spawnerType;
}

void indie::components::BonusSpawner::setSpawnerType(indie::components::BonusSpawner::BonusSpawnerType spawnerType)
{
    _spawnerType = spawnerType;
}

indie::components::BonusType indie::components::BonusSpawner::getBonusType() const
{
    return _bonusType;
}

void indie::components::BonusSpawner::setBonusType(indie::components::BonusType bonusType)
{
    _bonusType = bonusType;
}
