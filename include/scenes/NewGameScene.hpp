/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** NewGameScene.hpp
*/

/* Created the 13/06/2019 at 16:34 by jfrabel */

#ifndef INDIESTUDIO_NEWGAMESCENE_HPP
#define INDIESTUDIO_NEWGAMESCENE_HPP

#include "IScene.hpp"
#include "PlayerConfigScene.hpp"

namespace indie {

    namespace scenes {

        class NewGameScene : public IScene {
        public:
            NewGameScene();
            void onStart() override;
            void onStop() override;
            SaveState save(bool override, bool saveShouldBeKeeped) override;
            SaveState save(const std::string &saveName, bool override, bool saveShouldBeKeeped) override;

        private:
            jf::entities::EntityHandler spawnCamera();
            jf::entities::EntityHandler spawnBlack();
            jf::entities::EntityHandler spawnBlue();
            jf::entities::EntityHandler spawnWhite();
            jf::entities::EntityHandler spawnYellow();
            void assignSpecificComponents(jf::entities::EntityHandler entity, PlayerControllerType type);

        private:
            static constexpr unsigned int mapWidth = 15;
            static constexpr unsigned int mapHeight = 15;
            static constexpr unsigned int nbStartingLives = 1;

        private:
            bool _saveOnExit;
            std::string _saveName;
            jf::internal::ID _saveEventID;
        };
    }
}

#endif //INDIESTUDIO_NEWGAMESCENE_HPP
