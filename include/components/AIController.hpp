/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** AIController
*/

#ifndef AICONTROLLER_HPP_
#define AICONTROLLER_HPP_

#include "Component.hpp"
#include "maths/Vectors.hpp"

namespace indie {

    namespace components {

        class AIController : public jf::components::Component {
            public:
                AIController(jf::entities::Entity &entity);
                ~AIController();
                        
            public:
                typedef enum {
                    SEARCH,
                    FOCUS,
                    POWERUP,
                    SURVIVE,
                    TAUNT,
                    UNKNOWN
                } state;

                void setTargetVector(indie::maths::Vector3D assign);
                void setIsTaunting(bool assign);
                void setIsPlacingBombs(bool assign);
                void setState(state);

                bool getIsTaunting() const;
                bool getIsPlacingBombs() const;
                indie::maths::Vector3D getTarget() const;
                state getState() const;

            private:
                indie::maths::Vector3D _target;
                bool _isTaunting;
                bool _isPlacingBombs;
                state _state;
        };
    }
}

#else

namespace indie {

    namespace components {
        class AIController;
    }
}

#endif /* !AICONTROLLER_HPP_ */