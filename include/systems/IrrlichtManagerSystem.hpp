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
#include <components/BoxCollider.hpp>

#include "System.hpp"
#include "components/ComponentParticle.hpp"
#include "components/Transform.hpp"
#include "maths/Vectors.hpp"
#include "components/Mesh.hpp"
#include "components/Transform.hpp"
#include "components/Material.hpp"
#include "components/Animator.hpp"
#include "components/PointLight.hpp"

namespace indie {

    namespace systems {

        class IrrlichtManagerSystem : public jf::systems::ISystem {
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

            const indie::maths::Vector2D &getWindowDimension() const;
            void setWindowDimension(const indie::maths::Vector2D &dimensions);

            irr::scene::ISceneManager *getSceneManager();
            irr::video::IVideoDriver *getVideoDriver();
            irr::IrrlichtDevice *getDevice();

            bool isWindowOpen() const;

            void activateJoysticks();
            void reloadJoysticks();
            const irr::core::array<irr::SJoystickInfo> &getJoystickInfos();

        public:
            static void drawGizmos(bool value);
            static bool getDrawGizmos();

        private:
            static void syncModel(
                jf::entities::EntityHandler entity,
                jf::components::ComponentHandler<components::Mesh> mesh);
            static void syncModelMaterial(
                jf::components::ComponentHandler<components::Material> mat,
                jf::components::ComponentHandler<components::Mesh> mesh);
            static void syncModelPos(
                jf::components::ComponentHandler<components::Transform> tr,
                jf::components::ComponentHandler<components::Mesh> mesh);
            static void syncModelAnimation(
                jf::components::ComponentHandler<components::Animator> animator,
                jf::components::ComponentHandler<components::Mesh> mesh);

            static void syncParticlePos(
                jf::entities::EntityHandler entity,
                jf::components::ComponentHandler<components::Transform> tr,
                jf::components::ComponentHandler<components::Particle> particle);

            static void syncPointLights(
                jf::entities::EntityHandler entity,
                jf::components::ComponentHandler<components::PointLight> pl);
            static void syncPointLightsTransform(
                jf::components::ComponentHandler<components::Transform> tr,
                jf::components::ComponentHandler<components::PointLight> pl);
            static void syncPointChanges(jf::components::ComponentHandler<components::PointLight> pl);

            static void drawBoxColliderGizmos(jf::entities::EntityHandler entity, jf::components::ComponentHandler<components::BoxCollider> collider);

        private:
            void openWindow();
            void closeWindow();
            void reloadWindow();

            void updateCamera(const std::chrono::nanoseconds &elapsedTime);

        private:
            static bool _drawGizmos;

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
            indie::maths::Vector2D _windowDimension;
        };
    }
}

#else

namespace indie {

    namespace systems {
        class IrrlichtManagerSystem;
    }
}

#endif //JFECS_IRRLICHT_IRRLICHTRENDERERSYSTEM_HPP
