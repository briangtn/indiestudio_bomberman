/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** BonusSystem.hpp
*/

/* Created the 05/06/2019 at 21:59 by jfrabel */

#ifndef INDIESTUDIO_BONUSSYSTEM_HPP
#define INDIESTUDIO_BONUSSYSTEM_HPP

#include <map>
#include <random>
#include "maths/Vectors.hpp"
#include "System.hpp"
#include "components/BonusEffector.hpp"
#include "components/BonusSpawner.hpp"

namespace indie {

    namespace systems {

        class BonusSystem : public jf::systems::ISystem {
        public:
            BonusSystem();
            ~BonusSystem() override;

        public:
            void onAwake() override;
            void onStart() override;
            void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
            void onStop() override;
            void onTearDown() override;

        private:
            components::BonusType getRandomType();

            jf::entities::EntityHandler spawnNewPowerUp(components::BonusType bonusType, const maths::Vector3D &pos, const maths::Vector3D &scale);

        private:
            static bool BombUpAffector(jf::entities::EntityHandler affectTo, jf::components::ComponentHandler<components::BonusEffector> &effector);
            static bool FireUpAffector(jf::entities::EntityHandler affectTo, jf::components::ComponentHandler<components::BonusEffector> &effector);
            static bool SpeedUpAffector(jf::entities::EntityHandler affectTo, jf::components::ComponentHandler<components::BonusEffector> &effector);
            static bool WallPassAffector(jf::entities::EntityHandler affectTo, jf::components::ComponentHandler<components::BonusEffector> &effector);

        private:
            using BonusFunction = std::function<bool(jf::entities::EntityHandler affectTo, jf::components::ComponentHandler<components::BonusEffector> &)>;

            static const std::map<components::BonusType, float> _bonusDistributionRate;
            static const std::map<components::BonusType, BonusFunction> _bonusAffectorMap;
            static const std::map<components::BonusType, std::pair<std::string, std::string>> _bonusModelMap;

            static constexpr int _bombTileAdded = 1;
            static constexpr float _speedAdded = 10.0f;
            static constexpr float _maxSpeed = 60.0f;
            static constexpr int _maxBombAdded = 1;

        private:
            jf::internal::ID _bonusSpawnerDestroyedEventListenerID;
            std::default_random_engine _re;
            std::uniform_real_distribution<float> _distribution;
        };
    }
}

#endif //INDIESTUDIO_BONUSSYSTEM_HPP
