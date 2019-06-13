/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PlayerConfigScene.hpp
*/

/* Created the 12/06/2019 at 13:59 by brian */

#ifndef INDIESTUDIO_PLAYERCONFIGSCENE_HPP
#define INDIESTUDIO_PLAYERCONFIGSCENE_HPP

#include <vector>
#include "IScene.hpp"
#include "input/Controller.hpp"

namespace indie {
    namespace scenes {
        enum PlayerControllerType : int {
            INPUT_EXIST = 0,
            INPUT_CONFIG = 1,
            AI = 2
        };

        struct PlayerSettings {
            PlayerControllerType controllerType = AI;
            Controller controller = Controller("");
            bool isValid = false;
            jf::internal::ID eventKeyboardId;
            jf::internal::ID eventJoystickId;
        };

        class PlayerConfigScene : public IScene {
        public:
            static std::vector<PlayerSettings> playersSettings;
            static std::map<PlayerControllerType, std::string> controllerTypeImages;
            static std::map<std::string, Controller> controllers;

            static void InitControllers();
            static void UpdateConfigController();
        private:
            static void from(PlayerControllerType controllerType, int id);
            static void to(PlayerControllerType controllerType, int id);
            static void setValid(bool valid, int id);
            static void onWaitForInput(int id);

        public:
            void onStart() override;
            void onStop() override;

            void createConfigBlock(int id);
        };
    }
}

#endif //INDIESTUDIO_PLAYERCONFIGSCENE_HPP
