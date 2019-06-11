/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ComponentParticle
*/

#ifndef COMPONENTPARTICLE_HPP_
#define COMPONENTPARTICLE_HPP_

#include <iostream>
#include <irrlicht.h>
#include "Component.hpp"
#include "ComponentCreatedEvent.hpp"
#include "ECSWrapper.hpp"
#include "exceptions/ParticleException.hpp"
#include "systems/IrrlichtManagerSystem.hpp"

namespace indie {
    namespace components {
        class Particle : public jf::components::Component {
        public:

            /* Particle Constructor */

            Particle(jf::entities::Entity &entity, const std::string &name);

            /* Particle Destructor */

            ~Particle();            

            /* Init Function */

            void initParticle();
            bool isInit() const;
            void render();
         
            const irr::scene::IParticleEmitter *getEmitter() const;

            /* Get And Set Assets */

            std::string getName() const;
            void setName(const std::string &newName);

            std::string getTexturePath() const;
            void setTexture(int layer, const std::string &textureName);

            /* Handling Display Particle */

            void activate();
            void deactivate();
            bool getIsVisible() const;

            /* Get and Set For Transform */

            irr::core::vector3df getPosition() const;
            void setPosition(const irr::core::vector3df &newPos);

            irr::core::vector3df getScale() const;
            void setScale(const irr::core::vector3df &newScale);

            irr::core::vector3df getRotation() const;
            void setRotation(const irr::core::vector3df &newRotation);

            /* Get and Set For Emitter */

            irr::core::aabbox3d<irr::f32> getEmitterSize() const;
            void setEmitterSize(const irr::core::aabbox3d<irr::f32> &newEmitterSize);

            irr::core::vector3df getInitialDirection() const;
            void setInitialDirection(const irr::core::vector3df &newInitialDirection);

            std::pair<int, int> getEmitRate() const;
            void setEmitRate(const std::pair<int, int> &newEmitRate);

            std::pair<irr::video::SColor, irr::video::SColor> getDarkBrightColor() const;
            void setDarkBrightColor(const std::pair<irr::video::SColor, irr::video::SColor> &newDarkBrightColor);

            std::pair<int, int> getMinMaxAge() const;
            void setMinMaxAge(const std::pair<int, int> &newMinMaxAge);

            int getAngle() const;
            void setAngle(const int &newAngle);

            std::pair<irr::core::dimension2df, irr::core::dimension2df> getMinMaxSize() const;
            void setMinMaxSize(const std::pair<irr::core::dimension2df, irr::core::dimension2df> &newMinMaxSize);

            /* Get and Set For Fade */

            irr::video::SColor getFadeColor() const;
            void setFadeColor(const irr::video::SColor &newFadeColor);

            int getFadeTime() const;
            void setFadeTime(const int &newFadeTime);

        protected:
        private:

            /* Init Function Emitter And Particle */

            void createBoxEmitter();       
            void createFadeOutAffector();

            /* Check Init Emitter And Affector */

            bool isEmitterInit() const;
            bool isAffectorInit() const;
        

            /* Bool is created / Visible */

            bool _boxEmiterCreated;
            bool _affectorCreated;
            bool _isVisible;

            /* Particle Core*/

            irr::scene::IParticleSystemSceneNode *_particle;
            irr::scene::IParticleEmitter *_emitter;
            irr::scene::IParticleAffector *_affector;

            /* BoxEmitter Info */

            irr::core::aabbox3d<irr::f32> _emiterSize;
            irr::core::vector3df _initialDirection;
            std::pair<int, int> _emitRate;
            std::pair<irr::video::SColor, irr::video::SColor> _darkBrightColor;
            std::pair<int, int> _minMaxAge;
            int _angle;
            std::pair<irr::core::dimension2df, irr::core::dimension2df> _minMaxSize;

            bool _emiterSizeInitialize;
            bool _initialDirectionInitialize;
            bool _emitRateInitialize;
            bool _darkBrightColorInitialize;
            bool _minMaxAgeInitialize;
            bool _angleInitialize;
            bool _minMaxSizeInitialize;

            /* FadeOut Info */

            irr::video::SColor _fadeColor;
            int _fadeTime;

            bool _fadeColorInitialize;
            bool _fadeTimeInitialize;

            /* Assets Particle */

            int _layer;
            std::string _texturePath;
            std::string _name;

            jf::internal::ID _irrlichtClosingWindowEventID;
        };
    }
}

#else

namespace indie {
    namespace components {
        class Particle;
    }
}

#endif /* !COMPONENTPARTICLE_HPP_ */
