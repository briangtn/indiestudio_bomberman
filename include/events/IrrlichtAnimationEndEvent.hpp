/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IrrlichtAnimationEndEvent.hpp
*/

/* Created the 05/06/2019 at 22:33 by jfrabel */

#ifndef INDIESTUDIO_ASKINGFORBONUSSPAWNEVENT_HPP
#define INDIESTUDIO_ASKINGFORBONUSSPAWNEVENT_HPP

#include "maths/Vectors.hpp"
#include "components/BonusSpawner.hpp"

namespace indie {

    namespace events {

        struct IrrlichtAnimationEndEvent {
            jf::internal::ID entityId;
            std::string animationName;
        };
    }
}
#endif //INDIESTUDIO_ASKINGFORBONUSSPAWNEVENT_HPP
