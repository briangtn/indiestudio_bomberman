/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** IrrlichtParticleComponent
*/

/* Created the 10/05/2019 at 18:56 by Charlie Jeanneau */

#ifndef IRRLICHTPARTICLECOMPONENT_HPP_
#define IRRLICHTPARTICLECOMPONENT_HPP_

#include "ECSWrapper.hpp"
#include "Component.hpp"
#include "irrlicht.h"

namespace jf {

    class IrrlichtParticleComponent : public jf::components::Component {
        public:

        IrrlichtParticleComponent(entities::Entity &entity);

        ~IrrlichtParticleComponent() {
            EMIT_DELETE(IrrlichtParticleComponent);
        }   

        protected:
        private:
    };
}

#endif /* !IRRLICHTPARTICLECOMPONENT_HPP_ */