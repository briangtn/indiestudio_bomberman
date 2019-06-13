/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** ControllerConfigScene.hpp
*/

/* Created the 13/06/2019 at 00:29 by brian */

#ifndef INDIESTUDIO_CONTROLLERCONFIGSCENE_HPP
#define INDIESTUDIO_CONTROLLERCONFIGSCENE_HPP

#include <vector>
#include "IScene.hpp"
#include "input/Controller.hpp"

namespace indie {
    namespace scenes {
        class ControllerConfigScene : public IScene {
        public:
            enum Step {
                UP = 0,
                DOWN,
                LEFT,
                RIGHT,
                TAUNT,
                BOMB,
                END
            };

        public:
            static int id;
            static Controller controller;
            static Step step;
            static std::vector<jf::internal::ID> listeners;
            static std::vector<irr::u16> keysPressed;
            static std::vector<irr::u16> joysticksActivated;

        public:
            void onStart() override;
            void onStop() override;

            static void up();
            static void down(irr::EKEY_CODE firstKeyCode);
            static void down(irr::u8 id, irr::u8 keyCode);
            static void left();
            static void right(irr::EKEY_CODE firstKeyCode);
            static void right(irr::u8 id, irr::u8 keyCode);
            static void taunt();
            static void bomb();
            static void end();
            static void removeListeners();
            static void setInfoText(const std::string &text);


        private:
        };
    }
};


#endif //INDIESTUDIO_CONTROLLERCONFIGSCENE_HPP
