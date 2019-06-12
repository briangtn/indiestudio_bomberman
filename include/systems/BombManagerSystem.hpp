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
#include "components/PlayerController.hpp"
#include <unistd.h>

namespace indie {
    namespace systems {
        class BombManagerSystem : public jf::systems::ISystem {
            public:

                /* Constructor & Destructor BombManagerSystem */

                BombManagerSystem();
                ~BombManagerSystem();
            
            public:

                /* Override Function ISystem */

                void onAwake() override;
                void onStart() override;
                void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
                void onStop() override;
                void onTearDown() override;

            public:

                /* Funciton For Create A Bomb */

                void createBomb(jf::components::ComponentHandler<components::Bomb> bomb,
                jf::components::ComponentHandler<components::Transform> tr);

                /* Display Particle And Play Sound For Each Bomb */

                void displayParticle(indie::components::BombType typeBomb, const int &strength, jf::components::ComponentHandler<indie::components::Bomb> bomb);
                void playSoundExplosion(indie::components::BombType typeBomb, bool &pass);

                /* Set & Get bombPlace */

                void setNumberBombPlace(const int &newNumberBombPlace, const components::PlayerType &newPlayerType);
                unsigned int getNumberBombPlacer(const components::PlayerType &playerType) const;

                /* Remove & Add Bomb In NumberBombPlace */

                void addBombPlace(components::PlayerType playerType);
                void removeBombPlace(components::PlayerType playerType);

                /* Shake Bomb Function */

                void shakeBomb(jf::components::ComponentHandler<indie::components::Bomb> bomb);

            protected:
            private:
            std::map<components::PlayerType, unsigned int> _numberBombPlace;
        };
    }
}

#endif /* !BOMBMANAGERSYSTEM_HPP_ */