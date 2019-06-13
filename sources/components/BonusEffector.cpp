/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** BonusEffector.cpp
*/

/* Created the 05/06/2019 at 21:29 by jfrabel */

#include "Events.hpp"
#include "components/BonusEffector.hpp"

indie::components::BonusEffector::BonusEffector(jf::entities::Entity &entity, BonusType type)
    : Component(entity), _type(type)
{
    EMIT_CREATE(BonusEffector);
}

indie::components::BonusEffector::~BonusEffector()
{
    EMIT_DELETE(BonusEffector);
}

indie::components::BonusType indie::components::BonusEffector::getType() const
{
    return _type;
}

void indie::components::BonusEffector::setType(indie::components::BonusType type)
{
    _type = type;
}
