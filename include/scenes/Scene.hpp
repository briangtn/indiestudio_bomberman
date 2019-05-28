/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Scene.hpp
*/

/* Created the 27/05/2019 at 15:27 by jbulteau */

#ifndef INDIESTUDIO_SCENE_HPP
#define INDIESTUDIO_SCENE_HPP

#include <string>
#include <vector>
#include "IScene.hpp"
#include "ID.hpp"

namespace indie {

    namespace scenes {

        class Scene : public IScene {
        public:
            Scene(const std::string &fileName);
            ~Scene() = default;

        public:
            void onStart() override;
            void onStop() override;

        private:
            const std::string &_fileName;

            std::vector<jf::internal::ID> _listeners;
        };
    }
}

#endif //INDIESTUDIO_SCENE_HPP
