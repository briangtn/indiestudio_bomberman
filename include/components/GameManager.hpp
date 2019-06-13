/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** GameManager.hpp
*/

/* Created the 13/06/2019 at 19:49 by jfrabel */

#ifndef INDIESTUDIO_GAMEMANAGER_HPP
#define INDIESTUDIO_GAMEMANAGER_HPP

#include "Component.hpp"

namespace indie {

    namespace components {

        class GameManager : public jf::components::Component {
        public:
            GameManager(jf::entities::Entity &entity);
            ~GameManager() override;

        private:

        };
    }
}

#endif //INDIESTUDIO_GAMEMANAGER_HPP
