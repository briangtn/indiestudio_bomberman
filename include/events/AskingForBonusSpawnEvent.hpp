/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** AskingForBonusSpawnEvent.hpp
*/

/* Created the 05/06/2019 at 22:33 by jfrabel */

#ifndef INDIESTUDIO_ASKINGFORBONUSSPAWNEVENT_HPP
#define INDIESTUDIO_ASKINGFORBONUSSPAWNEVENT_HPP

#include "maths/Vectors.hpp"
#include "components/BonusSpawner.hpp"

namespace indie {

    namespace events {

        struct AskingForBonusSpawnEvent {
            maths::Vector3D eventPosition;
            components::BonusSpawner::BonusSpawnerType spawnType;
            components::BonusType optionalBonusType;
        };
    }
}
#endif //INDIESTUDIO_ASKINGFORBONUSSPAWNEVENT_HPP
