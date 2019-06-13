/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Rotator.hpp
*/

/* Created the 24/05/2019 at 13:58 by jfrabel */

#ifndef INDIESTUDIO_ROTATOR_HPP
#define INDIESTUDIO_ROTATOR_HPP

#include "Component.hpp"
#include "maths/Vectors.hpp"

namespace indie {

    namespace components {

        class Rotator : public jf::components::Component {
        public:
            Rotator(jf::entities::Entity &entity);
            Rotator(jf::entities::Entity &entity, float speedX, float speedY, float speedZ);
            Rotator(jf::entities::Entity &entity, const indie::maths::Vector3D &speed);
            ~Rotator() override;

            Rotator &operator>>(std::ostream &file);

        public:
            void setSpeed(const indie::maths::Vector3D &speed);
            const indie::maths::Vector3D &getSpeed() const;

            void setSpeedX(float speedX);
            float getSpeedX() const;

            void setSpeedY(float speedY);
            float getSpeedY() const;

            void setSpeedZ(float speedZ);
            float getSpeedZ() const;

        private:
            indie::maths::Vector3D _speed;
        };
    }
}

#endif //INDIESTUDIO_ROTATOR_HPP
