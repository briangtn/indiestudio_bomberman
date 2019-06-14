/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** DynamicCamera.hpp
*/

/* Created the 12/06/2019 at 22:30 by jfrabel */

#ifndef INDIESTUDIO_DYNAMICCAMERA_HPP
#define INDIESTUDIO_DYNAMICCAMERA_HPP

#include "Component.hpp"
#include "components/Transform.hpp"

namespace indie {

    namespace components {

        class DynamicCamera : public jf::components::Component {
        public:
            DynamicCamera(jf::entities::Entity &entity);
            ~DynamicCamera() override;

            float getMovementSpeed() const;
            void setMovementSpeed(float movementSpeed);

            int getBlockBorders() const;
            void setBlockBorders(int blockBorders);

            DynamicCamera &operator>>(std::ostream &file);

        private:
            float _movementSpeed;
            int _blockBorders;
        };
    }
}

#endif //INDIESTUDIO_DYNAMICCAMERA_HPP
