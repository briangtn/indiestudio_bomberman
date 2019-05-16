/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Camera.hpp
*/

#ifndef JFENTITYCOMPONENTSYSTEM_CAMERA_HPP
#define JFENTITYCOMPONENTSYSTEM_CAMERA_HPP

#include <irrlicht.h>
#include "Component.hpp"
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
            explicit Camera(entities::Entity &entity, float FOV = 45);
            ~Camera() override;

            void updateCamera();

            irr::scene::ICameraSceneNode *getCameraNode();

            void setFOV(float FOV);
            float getFOV() const;

        protected:
            irr::scene::ICameraSceneNode *_cameraNode;
            jf::internal::ID _eventCloseID;
            float _FOV;
        };
    };
};


#endif //JFENTITYCOMPONENTSYSTEM_CAMERA_HPP
