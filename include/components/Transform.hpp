/*
** EPITECH PROJECT, 2018
** JFEntityComponentSystem
** File description:
** Transform2D.hpp
*/

/* Created the 02/05/2019 at 15:25 by jfrabel */

#ifndef JFENTITYCOMPONENTSYSTEM_TRANSFORM_HPP
#define JFENTITYCOMPONENTSYSTEM_TRANSFORM_HPP

#include "Component.hpp"
#include "maths/Vectors.hpp"

namespace indie {

    namespace components {

        class Transform : public jf::components::Component {
        public:
            explicit Transform(jf::entities::Entity &entity, maths::Vector3D position = maths::Vector3D(0, 0, 0),
               maths::Vector3D rotation = maths::Vector3D(0, 0, 0), maths::Vector3D scale = maths::Vector3D(1, 1, 1));
            ~Transform() override;

        public:
            const maths::Vector3D &getPosition() const;
            void setPosition(const maths::Vector3D &position);
            const maths::Vector3D &getRotation() const;
            void setRotation(const maths::Vector3D &rotation);
            const maths::Vector3D &getScale() const;
            void setScale(const maths::Vector3D &scale);

        private:
            maths::Vector3D _position;
            maths::Vector3D _rotation; /*!< In euler angles */
            maths::Vector3D _scale;
        };
    }
}

#endif //JFENTITYCOMPONENTSYSTEM_TRANSFORM_HPP
