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

namespace indie {
    namespace ststem {
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

            protected:
            private:
        };
    }
}

#endif /* !BOMBMANAGERSYSTEM_HPP_ */
