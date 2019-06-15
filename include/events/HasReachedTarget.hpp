/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** HasReachedTarget.hpp
*/

/* Created the 14/06/2019 at 22:22 by jfrabel */

#ifndef INDIESTUDIO_HASREACHEDTARGET_HPP
#define INDIESTUDIO_HASREACHEDTARGET_HPP

#include "ComponentHandler.hpp"
#include "components/MoveToTarget.hpp"

namespace indie {

    namespace events {

        struct HasReachedTarget {
            jf::components::ComponentHandler<indie::components::MoveToTarget> mtt;
        };
    }
}

#endif //INDIESTUDIO_HASREACHEDTARGET_HPP
