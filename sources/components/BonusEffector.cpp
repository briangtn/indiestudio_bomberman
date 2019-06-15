/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** BonusEffector.cpp
*/

/* Created the 05/06/2019 at 21:29 by jfrabel */

#include "Events.hpp"
#include "components/BonusEffector.hpp"

const std::map<indie::components::BonusType, std::string> indie::components::BonusEffector::bonusTypes = {
        {indie::components::BONUS_T_BOMB_UP, "BONUS_T_BOMB_UP"},
        {indie::components::BONUS_T_SPEED_UP, "BONUS_T_SPEED_UP"},
        {indie::components::BONUS_T_FIRE_UP, "BONUS_T_FIRE_UP"},
        {indie::components::BONUS_T_WALL_PASS, "BONUS_T_WALL_PASS"},
        {indie::components::BONUS_T_NB, "BONUS_T_NB"}
};

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

indie::components::BonusEffector &indie::components::BonusEffector::operator>>(std::ostream &file)
{
    file << R"(        <component type="BonusEffector">)" << std::endl;
    file << R"(            <argument name="bonusType" value=")" << bonusTypes.at(_type) << R"("/>)" << std::endl;
    file << "        </component>" << std::endl;
    return *this;
}
