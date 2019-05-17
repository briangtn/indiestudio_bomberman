/*
** EPITECH PROJECT, 2018
** jfecs-irrlicht
** File description:
** IrrlichtManagerSystem.hpp
*/

/* Created the 09/05/2019 at 13:55 by jfrabel */

#ifndef JFECS_IRRLICHT_IRRLICHTRENDERERSYSTEM_HPP
#define JFECS_IRRLICHT_IRRLICHTRENDERERSYSTEM_HPP

#include <irrlicht.h>
#include <string>
#include "System.hpp"
#include "ComponentParticle.hpp"
#include "Transform.hpp"
#include "Vectors.hpp"
#include "Mesh.hpp"
#include "Transform.hpp"

/*!
* @namespace jf
* @brief The jfecs library
*/
namespace jf {

    namespace systems {

        class IrrlichtManagerSystem : public ISystem {
        private:
            class IrrlichtEventReceiver : public irr::IEventReceiver {
            public:
                bool OnEvent(const irr::SEvent &event) override;
            private:
                static void sendGUIEvent(const irr::SEvent &event);
                static void sendMouseInputEvent(const irr::SEvent &event);
                static void sendKeyInputEvent(const irr::SEvent &event);
                static void sendJoystickInputEvent(const irr::SEvent &event);
                static void sendLogTextEvent(const irr::SEvent &event);
                static void sendUserEvent(const irr::SEvent &event);
            };

        public:
            IrrlichtManagerSystem();
            ~IrrlichtManagerSystem();

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

            irr::scene::ISceneManager *getSceneManager();

            bool isWindowOpen() const;

            void activateJoysticks();
            void reloadJoysticks();
            const irr::core::array<irr::SJoystickInfo> &getJoystickInfos();

            irr::scene::ISceneManager *getSceneManager() const;

            irr::video::IVideoDriver *getVideoDriver() const;

        private:
            static void syncModelPos(jf::entities::EntityHandler entity, components::ComponentHandler<components::Transform> tr, components::ComponentHandler<components::Mesh> mesh);

        private:
            void openWindow();
            void closeWindow();
            void reloadWindow();

            void updateCamera(const std::chrono::nanoseconds &elapsedTime);

        private:
            IrrlichtEventReceiver _eventReceiver;

            irr::IrrlichtDevice *_device;
            irr::video::IVideoDriver *_driver;
            irr::scene::ISceneManager *_sceneManager;
            irr::gui::IGUIEnvironment *_guiEnvironment;

            bool _joystickEnabled;
            irr::core::array<irr::SJoystickInfo> _joystickInfos;

            bool _fullscreenEnabled;
            bool _vsyncEnabled;
            std::string _windowCaption;
            jf::maths::Vector2D _windowDimension;

        private:
            static void syncParticle(jf::entities::EntityHandler entity, components::ComponentHandler<components::Transform> transf, components::ComponentHandler<components::Particle> particle);
            
        private:
        };
    }
}

#else

namespace jf {

    namespace systems {
        class IrrlichtManagerSystem;
    }
}

#endif //JFECS_IRRLICHT_IRRLICHTRENDERERSYSTEM_HPP
