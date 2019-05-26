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

        private:
            std::string _xMovementAxis;
            std::string _yMovementAxis;
            std::string _zMovementAxis;

            bool _lockMovementX;
            bool _lockMovementY;
            bool _lockMovementZ;

            bool _movementRelativeToCamera;

            float _movementSpeed;
        };
    }
}

#endif //INDIESTUDIO_PLAYERCONTROLLER_HPP
