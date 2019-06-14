/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** IScene.hpp
*/

/* Created the 22/05/2019 at 14:49 by jfrabel */

#ifndef INDIESTUDIO_ISCENE_HPP
#define INDIESTUDIO_ISCENE_HPP

#include <string>

namespace indie {
    namespace scenes {

        enum SaveState {
            SUCCESS,
            FAIL
        };

        class IScene {
        public:
            virtual void onStart() = 0;
            virtual void onStop() = 0;
            virtual SaveState save(bool override, bool saveShouldBeKeeped) = 0;
            virtual SaveState save(const std::string &saveName, bool override, bool saveShouldBeKeeped) = 0;
        };
    }
}
#endif //INDIESTUDIO_ISCENE_HPP
