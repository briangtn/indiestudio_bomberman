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
#include "Vectors.hpp"

/*!
 * @namespace jf
 * @brief The jfecs library namespace
 */
namespace jf {

    namespace components {

        class Transform : public Component {
        public:
            explicit Transform(jf::entities::Entity &entity);
            ~Transform() override;

        public:
            const maths::Vector3D &getPosition() const;
            void setPosition(const maths::Vector3D &position);
            const maths::Vector3D &getRotation() const;
            void setRotation(const maths::Vector3D &rotation);
            const maths::Vector3D &getScale() const;
            void setScale(const maths::Vector3D &scale);

        private:
            jf::maths::Vector3D _position;
            jf::maths::Vector3D _rotation; /*!< In euler angles */
            jf::maths::Vector3D _scale;
        };
    }
}

#endif //JFENTITYCOMPONENTSYSTEM_TRANSFORM_HPP
