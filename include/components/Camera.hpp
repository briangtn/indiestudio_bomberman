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
#include "maths/Vectors.hpp"
#include "Transform.hpp"

namespace indie {
    namespace components {
        class Camera : public jf::components::Component {
        public:
            explicit Camera(jf::entities::Entity &entity, float FOV = 45);
            ~Camera() override;

            void updateCamera();

            irr::scene::ICameraSceneNode *getCameraNode();

            void setFOV(float FOV);
            float getFOV() const;

            std::ostream &operator<<(std::ostream &file);

        protected:
            irr::scene::ICameraSceneNode *_cameraNode;
            jf::internal::ID _eventCloseID;
            float _FOV;
        };
    };
};


#endif //JFENTITYCOMPONENTSYSTEM_CAMERA_HPP
