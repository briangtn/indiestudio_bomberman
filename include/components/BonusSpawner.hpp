/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** BonusSpawner.hpp
*/

/* Created the 05/06/2019 at 21:51 by jfrabel */

#ifndef INDIESTUDIO_BONUSSPAWNER_HPP
#define INDIESTUDIO_BONUSSPAWNER_HPP

#include "Component.hpp"
#include "BonusEffector.hpp"

namespace indie {

    namespace components {

        class BonusSpawner : public jf::components::Component {
        public:
            enum BonusSpawnerType {
                BONUS_SPAWNER_T_RANDOM,
                BONUS_SPAWNER_T_SPECIFIC,
            };

        public:
            BonusSpawner(jf::entities::Entity &entity, BonusSpawnerType spawnerType = BONUS_SPAWNER_T_RANDOM, BonusType bonusType = BONUS_T_WALL_PASS);
            ~BonusSpawner() override;

        public:
            BonusSpawnerType getSpawnerType() const;
            void setSpawnerType(BonusSpawnerType spawnerType);

            BonusType getBonusType() const;
            void setBonusType(BonusType bonusType);

        private:
            BonusSpawnerType _spawnerType;
            BonusType _bonusType;
        };
    }
}

#endif //INDIESTUDIO_BONUSSPAWNER_HPP
