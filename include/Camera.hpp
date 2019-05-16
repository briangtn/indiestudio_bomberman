/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Camera.hpp
*/

#ifndef JFENTITYCOMPONENTSYSTEM_CAMERA_HPP
#define JFENTITYCOMPONENTSYSTEM_CAMERA_HPP

#include "Component.hpp"
#include <irrlicht/ICameraSceneNode.h>
#include "Vectors.hpp"
#include "Transform.hpp"

/*!
 * @namespace jf
 * @brief The jfecs library namespace
 */
namespace jf {
    namespace components {
        class Camera : public Component {
        public:
            explicit Camera(entities::Entity &entity, float FOV = 90);

            void update();

            void setFOV(float FOV);
            float getFOV() const;

            ~Camera() override;
        protected:
            irr::scene::ICameraSceneNode *_sceneNode;
            jf::internal::ID _eventCloseID;
            float _FOV;
        };
    };
};


#endif //JFENTITYCOMPONENTSYSTEM_CAMERA_HPP
