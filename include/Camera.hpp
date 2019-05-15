//
// Created by brian on 5/14/19.
//

#ifndef JFENTITYCOMPONENTSYSTEM_CAMERA_HPP
#define JFENTITYCOMPONENTSYSTEM_CAMERA_HPP

#include <Component.hpp>
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

            ~Camera() override;
        protected:
            irr::scene::ICameraSceneNode *_sceneNode;
        };
    };
};


#endif //JFENTITYCOMPONENTSYSTEM_CAMERA_HPP
