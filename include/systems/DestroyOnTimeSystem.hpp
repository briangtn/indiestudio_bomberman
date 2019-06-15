/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** DestroyOnTimeSystem
*/

#ifndef DESTROYONTIMESYSTEM_HPP_
#define DESTROYONTIMESYSTEM_HPP_

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

namespace indie {
    namespace systems {
        class DestroyOnTimeSystem : public jf::systems::ISystem {
            public:
                DestroyOnTimeSystem();
                ~DestroyOnTimeSystem();

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

#endif /* !DESTROYONTIMESYSTEM_HPP_ */
