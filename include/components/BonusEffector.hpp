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

namespace indie {

    namespace components {

        enum BonusType {
            BONUS_T_BOMB_UP,
            BONUS_T_SPEED_UP,
            BONUS_T_FIRE_UP,
            BONUS_T_WALL_PASS,
        };

        class BonusEffector : public jf::components::Component {
        public:
            explicit BonusEffector(jf::entities::Entity &entity, BonusType type);
            ~BonusEffector() override;

        public:
            BonusType getType() const;
            void setType(BonusType type);

        private:
            BonusType _type;
        };
    }
}

#endif //INDIESTUDIO_BONUSEFFECTOR_HPP
