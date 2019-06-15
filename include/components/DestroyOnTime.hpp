/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** DestroyOnTime
*/

#ifndef DESTROYONTIME_HPP_
#define DESTROYONTIME_HPP_

#include <iostream>
#include <irrlicht.h>
#include "Component.hpp"
#include "ComponentCreatedEvent.hpp"
#include "ECSWrapper.hpp"
#include "systems/IrrlichtManagerSystem.hpp"

namespace indie {
    namespace components {
        class DestroyOnTime : public jf::components::Component {
            public:
                DestroyOnTime(jf::entities::Entity &entity, float time = 5.0f);
                ~DestroyOnTime();

                DestroyOnTime &operator>>(std::ostream &file);

                /* Set and Get TimeBeforeDestroy */

                float getTimeBeforeDestroy() const;
                void setTimeBeforeDestroy(const float &newTimeBeforeDestroy);

            protected:
            private:
                float _timeBeforeDestroy;
        };
    }
}

#endif /* !DESTROYONTIME_HPP_ */
