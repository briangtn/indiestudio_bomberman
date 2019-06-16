/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** InvalidXmlScene.hpp
*/

/* Created the 16/06/2019 at 18:48 by jfrabel */

#ifndef INDIESTUDIO_INVALIDXMLSCENE_HPP
#define INDIESTUDIO_INVALIDXMLSCENE_HPP

#include "Scene.hpp"

namespace indie {

    namespace scenes {

        class InvalidXmlScene : public IScene {
        public:
            void onStart() override;
            void onStop() override;
            SaveState save(bool override, bool saveShouldBeKeeped) override;
            SaveState save(const std::string &saveName, bool override, bool saveShouldBeKeeped) override;
        };
    }
}

#endif //INDIESTUDIO_INVALIDXMLSCENE_HPP
