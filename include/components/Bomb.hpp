/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include <iostream>
#include <irrlicht.h>
#include "Component.hpp"
#include "ComponentCreatedEvent.hpp"
#include "ECSWrapper.hpp"
#include "systems/IrrlichtManagerSystem.hpp"

namespace indie {
    namespace components {

            /* enum for each type of bomb */

            enum BombType {
                NORMAL,
                FIRE,
                WATER,
                ELECTRIC,
                LOVE
            };

            /* enum for each type of player */

            enum PlayerType {
                P1 = 1,
                P2 = 2,
                P3 = 3,
                P4 = 4
            };

        class Bomb : public jf::components::Component {
        public:

            /* Bombe Constructor */

            Bomb(jf::entities::Entity &entity, const int &strength,\
            const float &timeBeforeExplose, BombType bomb, PlayerType player);

            /* Bombe Destructor */

            ~Bomb();

            /* Set & Get Strength */

            int getStrength() const;
            void setStength(const int &newStrength);

            /* Set & Get TimeBeforeExplose */

            float getTimeBeforeExplose() const;
            void setTimeBeforeExplose(const float &newTimeBeforeExplose);

            /* Set & Get BombType */

            BombType getBombType() const;
            void setBombType(BombType newBombType);

            /* Set & Get TexturePath */

            std::string getTexturePath() const;
            void setTexturePath(const std::string &newTexturePath);

            /* Set & Get TextureMesh */

            std::string getTextureMesh() const;
            void setTextureMesh(const std::string &newMeshPath);

            /* Set & Get InitialPosition Bomb */

            void setInitialPosition(const indie::maths::Vector3D &vectPos);
            indie::maths::Vector3D getInitialPosition() const;

            /* Set & Get PlayerType */

            void setPlayerType(const PlayerType &player);
            PlayerType getPlayerType() const;

        protected:
        private:
            int _strength;
            float _timeBeforeExplose;
            int _bombID;
            BombType _bombType;
            PlayerType _Player;
            std::string _meshPath;
            std::string _texturePath;
            static const std::map<int, std::pair<std::string, std::string>> _pathTextureBomb;
            indie::maths::Vector3D _vectPos;
        };
    }
}

#endif /* !BOMB_HPP_ */
