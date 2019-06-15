/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** BonusEffector.hpp
*/

/* Created the 05/06/2019 at 21:29 by jfrabel */

#ifndef INDIESTUDIO_BONUSEFFECTOR_HPP
#define INDIESTUDIO_BONUSEFFECTOR_HPP

#include "Component.hpp"
#include <map>

namespace indie {

    namespace components {

        enum BonusType {
            BONUS_T_BOMB_UP,
            BONUS_T_SPEED_UP,
            BONUS_T_FIRE_UP,
            BONUS_T_WALL_PASS,
            BONUS_T_NB
        };

        class BonusEffector : public jf::components::Component {
        public:
            explicit BonusEffector(jf::entities::Entity &entity, BonusType type);
            ~BonusEffector() override;

            BonusEffector &operator>>(std::ostream &file);
        public:
            BonusType getType() const;
            void setType(BonusType type);

        public:
            static const std::map<BonusType, std::string> bonusTypes;

        private:
            BonusType _type;
        };
    }
}

#endif //INDIESTUDIO_BONUSEFFECTOR_HPP
