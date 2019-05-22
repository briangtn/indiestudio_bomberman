/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** SceneManager.hpp
*/

/* Created the 22/05/2019 at 14:49 by jfrabel */

#ifndef INDIESTUDIO_SCENEMANAGER_HPP
#define INDIESTUDIO_SCENEMANAGER_HPP

#include <map>
#include <vector>
#include <memory>
#include "IScene.hpp"

namespace indie {

    namespace scenes {

        class SceneManager {
        public:
            ~SceneManager();

        public:
            static void addScenes(const std::vector<std::pair<std::string, IScene *>> &scenes);
            static void changeScene(const std::string &sceneName);

        private:
            SceneManager();
            IScene &getSceneByName(const std::string &sceneName);
            void addScene(const std::string &name, IScene *scene);

        private:
            static SceneManager &getInstance();

        private:
            std::string _currentScene;
            std::map<std::string, std::unique_ptr<IScene>> _sceneMap;
        };
    }
}

#endif //INDIESTUDIO_SCENEMANAGER_HPP
