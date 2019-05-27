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
                LOVE,
                PIKE
            };

        class Bomb : public jf::components::Component {
        public:

            /* Bombe Constructor */

            Bomb(jf::entities::Entity &entity, const int &strength,\
            const float &timeBeforeExplose, BombType bomb);

            /* Bombe Destructor */

            ~Bomb();

            /* Set & Get Strength */

            int getStrength() const;
            void setStength(const int &newStrength);

            /* Set & Get TimeBeforeExplose */

            float getTimeBeforeExplose() const;
            void setTimeBeforeExplose(const int &newTimeBeforeExplose);

            /* Set & Get BombType */

            BombType getBombType() const;
            void setBombType(BombType newBombType);

            /* Set & Get TexturePath */

            std::string getTexturePath() const;
            void setTexturePath(const std::string &newTexturePath);

        protected:
        private:
            int _strength;
            float _timeBeforeExplose;
            int _bombID;
            BombType _bombType;
            std::string _texturePath;
            static const std::map<int, std::string> _pathTextureBomb;
        };
    }
}

#endif /* !BOMB_HPP_ */
