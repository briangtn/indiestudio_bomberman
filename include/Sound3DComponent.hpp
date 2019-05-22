/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Sound3DComponent.hpp
*/

/* Created the 22/05/2019 at 23:38 by jbulteau */

#ifndef INDIESTUDIO_SOUND3DCOMPONENT_HPP
#define INDIESTUDIO_SOUND3DCOMPONENT_HPP

#include "ASoundComponent.hpp"
#include "Vectors.hpp"

namespace indie {

    namespace components {

        class Sound3DComponent : public ASoundComponent {
        public:
            Sound3DComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType, jf::maths::Vector3D position);

        public:
            const jf::maths::Vector3D getPosition() const override;
            void setPosition(const jf::maths::Vector3D &position) override;
            const jf::maths::Vector3D getVelocity() const override;
            void setVelocity(const jf::maths::Vector3D &velocity) override;

        private:
            jf::maths::Vector3D _position;
        };
    }
}

#endif //INDIESTUDIO_SOUND3DCOMPONENT_HPP
