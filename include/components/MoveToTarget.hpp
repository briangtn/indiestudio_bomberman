/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** MoveToTarget.hpp
*/

/* Created the 12/06/2019 at 11:32 by jfrabel */

#ifndef INDIESTUDIO_MOVETOTARGET_HPP
#define INDIESTUDIO_MOVETOTARGET_HPP

#include "Component.hpp"
#include "maths/Vectors.hpp"

namespace indie {

    namespace components {

        class MoveToTarget : public jf::components::Component {
        public:
            explicit MoveToTarget(jf::entities::Entity &entity);

            const maths::Vector3D &getTarget() const;
            void setTarget(const maths::Vector3D &target);

            bool isFollowTarget() const;
            void setFollowTarget(bool followTarget);

            float getSpeed() const;
            void setSpeed(float speed);

        private:
            maths::Vector3D _target;
            bool _followTarget;
            float _speed;
        };
    }
}

#endif //INDIESTUDIO_MOVETOTARGET_HPP
