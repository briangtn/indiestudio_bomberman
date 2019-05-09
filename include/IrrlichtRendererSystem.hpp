/*
** EPITECH PROJECT, 2018
** jfecs-irrlicht
** File description:
** IrrlichtRendererSystem.hpp
*/

/* Created the 09/05/2019 at 13:55 by jfrabel */

#ifndef JFECS_IRRLICHT_IRRLICHTRENDERERSYSTEM_HPP
#define JFECS_IRRLICHT_IRRLICHTRENDERERSYSTEM_HPP

#include <irrlicht.h>
#include <string>
#include "System.hpp"
#include "Vectors.hpp"

/*!
* @namespace jf
* @brief The jfecs library
*/
namespace jf {

    namespace systems {

        class IrrlichtRendererSystem : public ISystem {
        public:
            IrrlichtRendererSystem();
            ~IrrlichtRendererSystem();

        public:
            void onAwake() override;
            void onStart() override;
            void onUpdate(const std::chrono::nanoseconds &elapsedTime) override;
            void onStop() override;
            void onTearDown() override;

        public:
            bool isFullScreenEnabled() const;
            void setFullScreenEnabled(bool enabled);

            bool isVSyncEnabled() const;
            void setVSyncEnabled(bool enabled);

            const std::string &getWindowCaption() const;
            void setWindowCaption(const std::string &str);

            const jf::maths::Vector2D &getWindowDimension() const;
            void setWindowDimension(const jf::maths::Vector2D &dimensions);

            bool isWindowOpen() const;

        private:
            void openWindow();
            void closeWindow();
            void reloadWindow();

        private:
            irr::IrrlichtDevice *_device;
            irr::video::IVideoDriver *_driver;
            irr::scene::ISceneManager *_sceneManager;
            irr::gui::IGUIEnvironment *_guiEnvironment;

            bool _fullscreenEnabled;
            bool _vsyncEnabled;
            std::string _windowCaption;
            jf::maths::Vector2D _windowDimension;
        };
    }
}

#endif //JFECS_IRRLICHT_IRRLICHTRENDERERSYSTEM_HPP
