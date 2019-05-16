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
#include "ParticleException.hpp"
#include "IrrlichtManagerSystem.hpp"
#include <iostream>

namespace jf {
    namespace components {
        class Particle : public jf::components::Component {
            public:
                Particle(jf::entities::Entity &entity, std::string name);

                void createBoxEmitter(jf::entities::Entity &entity, irr::core::aabbox3d<irr::f32> emiterSize,\
irr::core::vector3df initialDirection, std::pair<int, int> emitRate, std::pair<irr::video::SColor,\
irr::video::SColor> darkBrightColor, std::pair<int, int> minMaxAge, int angle,\
std::pair<irr::core::dimension2df, irr::core::dimension2df> minMaxsize);
                const irr::scene::IParticleEmitter *getEmitter() const;

                void createFadeOutParticle(irr::video::SColor color, int time);

                ~Particle() {
                    EMIT_DELETE(Particle);
                    _affector->drop();
                    _emitter->drop();
                    _particle->drop();
                }

                std::string getName() const;
                void setName(std::string newName);

                std::string getTexturePath() const;
                void setTexture(int layer, std::string textureName);

                void Activate();

                void Deactivate();

                bool getParticleVisible() const;

                irr::core::vector3df getPosition() const;
                void setPosition(irr::core::vector3df newPos);

                irr::core::vector3df getScale() const;
                void setScale(irr::core::vector3df newScale);

                irr::core::vector3df getRotation() const;
                void setRotation(irr::core::vector3df newRotation);

            protected:
            private:

                bool _boxEmiterCreate;
                bool _affectorCreate;
                bool _isVisible;

                irr::scene::IParticleSystemSceneNode *_particle;
                irr::scene::IParticleEmitter *_emitter;
                irr::scene::IParticleAffector *_affector;

                std::string _texturePath;
        };
    }
}

#else

namespace jf {
    namespace components {
        class Particle;
    }
}

#endif /* !COMPONENTPARTICLE_HPP_ */
