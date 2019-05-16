/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ComponentParticle
*/

#ifndef COMPONENTPARTICLE_HPP_
#define COMPONENTPARTICLE_HPP_

#include "Component.hpp"
#include "ComponentCreatedEvent.hpp"
#include "irrlicht.h"
#include "ECSWrapper.hpp"
#include "IrrlichtManagerSystem.hpp"
#include <iostream>

namespace jf {
    class Particle : public jf::components::Component {
        public:
            Particle(jf::entities::Entity &entity, std::string name);

            void createBoxEmitter(jf::entities::Entity &entity, irr::core::aabbox3d<irr::f32> emiterSize,\
irr::core::vector3df initialDirection, std::pair<int, int> emitRate, std::pair<irr::video::SColor,\
irr::video::SColor> darkBrightColor, std::pair<int, int> minMaxAge, int angle,\
std::pair<irr::core::dimension2df, irr::core::dimension2df> minMaxsize);

            void createFadeOutParticle(irr::video::SColor color, int time);

            ~Particle() {
                EMIT_DELETE(Particle);
            }

            std::string getName() const;
            void setName(std::string newName);

            std::string getTexturePath() const;
            void setTexture(int layer, std::string textureName);

            void Activate();

            void Deactivate();

            bool getParticleVisible() const;

        protected:
        private:

            bool _boxEmiterCreate;
            bool _affectorCreate;
            bool _isVisible;

            std::string _particleName;
            irr::scene::IParticleSystemSceneNode *_particle;
            irr::scene::IParticleEmitter *_emitter;
            irr::scene::IParticleAffector *_affector;

            irr::core::vector3df _position;
            irr::core::vector3df _scale;
            std::string _texturePath;
    };
}

#endif /* !COMPONENTPARTICLE_HPP_ */
