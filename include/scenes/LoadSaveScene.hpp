/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** LoadSaveScene.hpp
*/

/* Created the 15/06/2019 at 00:26 by brian */

#ifndef INDIESTUDIO_LOADSAVESCENE_HPP
#define INDIESTUDIO_LOADSAVESCENE_HPP

#include "IScene.hpp"

namespace indie {
    namespace scenes {
        class LoadSaveScene : public IScene {
        public:
            void onStart() override;
            void onStop() override;
            static void createButtons(unsigned int page, std::vector<std::string> saves);
            static void destroyButtons();

            SaveState save(bool override, bool saveShouldBeKeeped) override;
            SaveState save(const std::string &saveName, bool override, bool saveShouldBeKeeped) override;

        private:
            static int page;
        };
    }
}

#endif //INDIESTUDIO_LOADSAVESCENE_HPP
