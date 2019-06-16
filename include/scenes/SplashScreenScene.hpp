/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** SplashScreenScene.hpp
*/

/* Created the 16/06/2019 at 22:02 by jfrabel */

#ifndef INDIESTUDIO_SPLASHSCREENSCENE_HPP
#define INDIESTUDIO_SPLASHSCREENSCENE_HPP

#include "IScene.hpp"

namespace indie {

    namespace scenes {

        class SplashScreenScene : public IScene {
        public:
            void onStart() override;
            void onStop() override;
            SaveState save(bool override, bool saveShouldBeKeeped) override;
            SaveState save(const std::string &saveName, bool override, bool saveShouldBeKeeped) override;
        };
    }
}

#endif //INDIESTUDIO_SPLASHSCREENSCENE_HPP
