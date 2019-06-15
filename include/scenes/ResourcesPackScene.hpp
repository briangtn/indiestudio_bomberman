/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** EndScene.hpp
*/

//
// Created by romainfouyer on 6/15/19.
//

#ifndef INDIESTUDIO_RESOURCESPACKSCENE_HPP
#define INDIESTUDIO_RESOURCESPACKSCENE_HPP

#include "IScene.hpp"
#include <vector>

namespace indie {

    namespace scenes {

        class ResourcesPacksScene : public IScene {
        public:
            void onStart() override;
            void onStop() override;

            static void createButtons(unsigned int page, std::vector<std::string> saves);
            static void destroyButtons();

            SaveState save(bool override, bool saveShouldBeKeeped) override;
            SaveState save(const std::string &saveName, bool override, bool saveShouldBeKeeped) override;

        private:
            static int _page;
        };

    }

}


#endif //INDIESTUDIO_RESOURCESPACKSCENE_HPP
