/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Sound2DComponent.hpp
*/

/* Created the 22/05/2019 at 23:48 by jbulteau */

#ifndef INDIESTUDIO_SOUND2DCOMPONENT_HPP
#define INDIESTUDIO_SOUND2DCOMPONENT_HPP

#include "ASoundComponent.hpp"

namespace indie {

    namespace components {

        class Sound2DComponent : public ASoundComponent {
        public:
            Sound2DComponent(jf::entities::Entity &entity, const std::string &sourceFile, SoundType soundType);

        };
    }
}

#endif //INDIESTUDIO_SOUND2DCOMPONENT_HPP
