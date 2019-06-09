/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Hoverer.hpp
*/

/* Created the 24/05/2019 at 14:28 by jfrabel */

#ifndef INDIESTUDIO_HOVERER_HPP
#define INDIESTUDIO_HOVERER_HPP

#include "Component.hpp"
#include "maths/Vectors.hpp"

namespace indie {

    namespace components {

        class Hoverer : public jf::components::Component {
        public:
            Hoverer(jf::entities::Entity &entity);
            Hoverer(jf::entities::Entity &entity, const indie::maths::Vector3D &speed, const indie::maths::Vector3D &amplitude);
            ~Hoverer() override;

        public:
            void setSpeed(const indie::maths::Vector3D &speed);
            indie::maths::Vector3D getSpeed() const;

            void setAmplitude(const indie::maths::Vector3D &amplitude);
            const indie::maths::Vector3D &getAmplitude() const;

            void setAdvancement(const indie::maths::Vector3D &advancement);
            const indie::maths::Vector3D &getAdvancement() const;

            std::ostream &operator<<(std::ostream &file);

        private:
            indie::maths::Vector3D _speed;
            indie::maths::Vector3D _amplitude;
            indie::maths::Vector3D _advancement;
        };
    }
}
#endif //INDIESTUDIO_HOVERER_HPP
