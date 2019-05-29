/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** BombManagerSystem
*/

#ifndef BOMBMANAGERSYSTEM_HPP_
#define BOMBMANAGERSYSTEM_HPP_

#include <irrlicht.h>
#include <string>
#include "System.hpp"
#include "components/ComponentParticle.hpp"
#include "components/Transform.hpp"
#include "maths/Vectors.hpp"
#include "components/Mesh.hpp"
#include "components/Transform.hpp"
#include "components/Material.hpp"
#include "components/PointLight.hpp"
#include "components/Bomb.hpp"
#include "components/SoundComponent.hpp"
#include "components/DestroyOnTime.hpp"
#include <unistd.h>

namespace indie {
    namespace systems {
        class BombManagerSystem : public jf::systems::ISystem {
            public:
                BombManagerSystem();
                ~BombManagerSystem();
            
            public:
                void onAwake() override;
                void onStart() override;
                void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
                void onStop() override;
                void onTearDown() override;

            public:
                void createBomb(jf::components::ComponentHandler<components::Bomb> bomb,
                jf::components::ComponentHandler<components::Transform> tr);

                void displayParticle(indie::components::BombType typeBomb, const int &strength, indie::maths::Vector3D posLimit);

                void playSoundExplosion(indie::components::BombType typeBomb, bool &pass);

            protected:
            private:
        };
    }
}

#endif /* !BOMBMANAGERSYSTEM_HPP_ */
