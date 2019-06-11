/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** StaticTestScene.hpp
*/

/* Created the 22/05/2019 at 18:36 by jfrabel */

#ifndef INDIESTUDIO_STATICTESTSCENE_HPP
#define INDIESTUDIO_STATICTESTSCENE_HPP

#include <vector>
#include "IScene.hpp"
#include "Entity.hpp"

namespace indie {

    namespace scenes {

        class StaticTestScene : public IScene {
        public:
            StaticTestScene();
            ~StaticTestScene() = default;
            void onStart() override;
            void onStop() override;

        private:
            std::vector<jf::internal::ID> _listeners;
        };
    }
}

#endif //INDIESTUDIO_STATICTESTSCENE_HPP
