/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** IrrlichtParticleSystem
*/

/* Created the 10/05/2019 at 18:26 by Charlie Jeanneau */

#ifndef IRRLICHTPARTICLESYSTEM_HPP_
#define IRRLICHTPARTICLESYSTEM_HPP_

#include "System.hpp"
#include <string>
#include "irrlicht.h"

namespace jf {

    class IrrlichtParticleSystem : public jf::systems::ISystem {
        public:

            IrrlichtParticleSystem();

            ~IrrlichtParticleSystem();

            void onAwake() override;

            void onStart() override;

            void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;

            void onStop() override;

            void onTearDown() override;

            void setPosition(int x, int y, int z);

            void setScale(int x, int y, int z);

            void setMaterialFlag(irr::video::E_MATERIAL_FLAG flag, bool activate);

            void setMaterialType(irr::video::E_MATERIAL_FLAG flag);

            void setMaterialTexture(int Number, std::string texture_name);

        protected:
        private:
    };
}

#endif /* !IRRLICHTPARTICLESYSTEM_HPP_ */
