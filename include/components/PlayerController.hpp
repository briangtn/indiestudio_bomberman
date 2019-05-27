/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PlayerController.hpp
*/

/* Created the 26/05/2019 at 11:34 by jfrabel */

#ifndef INDIESTUDIO_PLAYERCONTROLLER_HPP
#define INDIESTUDIO_PLAYERCONTROLLER_HPP

#include "Component.hpp"

namespace indie {

    namespace components {

        class PlayerController : public jf::components::Component {
        public:
            PlayerController(jf::entities::Entity &entity);
            PlayerController(jf::entities::Entity &entity, const std::string &xAxis, const std::string &yAxis, const std::string &zAxis);
            PlayerController(jf::entities::Entity &entity, const std::string &xAxis, const std::string &yAxis, const std::string &zAxis, bool lockX, bool lockY, bool lockZ);
            ~PlayerController() override;

        public:
            const std::string &getXMovementAxis() const;
            void setXMovementAxis(const std::string &xMovementAxis);
            const std::string &getYMovementAxis() const;
            void setYMovementAxis(const std::string &yMovementAxis);
            const std::string &getZMovementAxis() const;
            void setZMovementAxis(const std::string &zMovementAxis);

            bool isLockMovementX() const;
            void setLockMovementX(bool lockMovementX);
            bool isLockMovementY() const;
            void setLockMovementY(bool lockMovementY);
            bool isLockMovementZ() const;
            void setLockMovementZ(bool lockMovementZ);

            bool isMovementRelativeToCamera() const;
            void setMovementRelativeToCamera(bool movementRelativeToCamera);

            float getMovementSpeed() const;
            void setMovementSpeed(float movementSpeed);

            const std::string &getXRotationAxis() const;
            void setXRotationAxis(const std::string &xRotationAxis);
            const std::string &getYRotationAxis() const;
            void setYRotationAxis(const std::string &yRotationAxis);
            const std::string &getZRotationAxis() const;
            void setZRotationAxis(const std::string &zRotationAxis);

            bool isLockRotationX() const;
            void setLockRotationX(bool lockRotationX);
            bool isLockRotationY() const;
            void setLockRotationY(bool lockRotationY);
            bool isLockRotationZ() const;
            void setLockRotationZ(bool lockRotationZ);

            bool isAlwaysLookForward() const;
            void setAlwaysLookForward(bool alwaysLookForward);

            float getRotationSpeed() const;
            void setRotationSpeed(float rotationSpeed);

        private:
            std::string _xMovementAxis;
            std::string _yMovementAxis;
            std::string _zMovementAxis;

            bool _lockMovementX;
            bool _lockMovementY;
            bool _lockMovementZ;

            bool _movementRelativeToCamera;

            float _movementSpeed;

            std::string _xRotationAxis;
            std::string _yRotationAxis;
            std::string _zRotationAxis;

            bool _lockRotationX;
            bool _lockRotationY;
            bool _lockRotationZ;

            bool _alwaysLookForward;

            float _rotationSpeed;
        };
    }
}

#endif //INDIESTUDIO_PLAYERCONTROLLER_HPP
