/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** StaticTestScene.cpp
*/

/* Created the 22/05/2019 at 18:36 by jfrabel */

#include "scenes/StaticTestScene.hpp"
#include "components/Material.hpp"
#include "components/Camera.hpp"
#include "exceptions/IrrlichtManagerExceptions.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "events/IrrlichtMouseInputEvent.hpp"
#include "ECSWrapper.hpp"
#include "components/ComponentParticle.hpp"
#include "Exceptions.hpp"
#include "components/Rotator.hpp"

void indie::scenes::StaticTestScene::onStart()
{
    ECSWrapper ecs;
    auto cameraEntity = ecs.entityManager.createEntity("camera");
    auto cameraTr = cameraEntity->assignComponent<indie::components::Transform>();
    cameraTr->setPosition({0, 0, -20});
    cameraEntity->assignComponent<indie::components::Camera>();

    auto id = ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_Q>>(nullptr, [](void *null, auto e) {
        ECSWrapper ecs;
        auto tr = ecs.entityManager.getEntityByName("camera")->getComponent<indie::components::Transform>();
        auto oldPos = tr->getPosition();
        auto oldRot = tr->getRotation();
        if (e.shiftActivated) {
            oldRot.y -= 1;
        } else {
            oldPos.x -= 1;
        }
        tr->setPosition(oldPos);
        tr->setRotation(oldRot);
    });
    _listeners.push_back(id);
    id = ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_D>>(nullptr, [](void *null, auto e) {
        ECSWrapper ecs;
        auto tr = ecs.entityManager.getEntityByName("camera")->getComponent<indie::components::Transform>();
        auto oldPos = tr->getPosition();
        auto oldRot = tr->getRotation();
        if (e.shiftActivated) {
            oldRot.y += 1;
        } else {
            oldPos.x += 1;
        }
        tr->setPosition(oldPos);
        tr->setRotation(oldRot);
    });
    _listeners.push_back(id);
    id = ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_Z>>(nullptr, [](void *null, auto e) {
        ECSWrapper ecs;
        auto tr = ecs.entityManager.getEntityByName("camera")->getComponent<indie::components::Transform>();
        auto oldPos = tr->getPosition();
        if (e.shiftActivated) {
            oldPos.y += 1;
        } else {
            oldPos.z += 1;
        }
        tr->setPosition(oldPos);
    });
    _listeners.push_back(id);
    id = ecs.eventManager.addListener<void, indie::events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_S>>(nullptr, [](void *null, auto e) {
        ECSWrapper ecs;
        auto tr = ecs.entityManager.getEntityByName("camera")->getComponent<indie::components::Transform>();
        auto oldPos = tr->getPosition();
        if (e.shiftActivated) {
            oldPos.y -= 1;
        } else {
            oldPos.z -= 1;
        }
        tr->setPosition(oldPos);
    });
    _listeners.push_back(id);

    auto plEntity = ecs.entityManager.createEntity("pointLight");
    auto plTr = plEntity->assignComponent<indie::components::Transform>();
    plTr->setPosition({-1, -1, -1});
    plEntity->assignComponent<indie::components::PointLight>();

    auto cubeEntity = ecs.entityManager.createEntity("cube");
    auto tr2 = cubeEntity->assignComponent<indie::components::Transform>();
    cubeEntity->assignComponent<indie::components::Rotator, indie::maths::Vector3D>({0, 90, 0});
    cubeEntity->assignComponent<indie::components::Mesh, std::string>("../test_assets/cube.obj");
    auto mat = cubeEntity->assignComponent<indie::components::Material, std::string>("../test_assets/cube_texture.png");
    mat->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
    mat->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    auto cubeEntity2 = ecs.entityManager.createEntity("cube");
    auto tr = cubeEntity2->assignComponent<indie::components::Transform>();
    tr->setPosition({10, 10, 10});
    tr->setScale({10, 10, 2});
    tr->setRotation({0, 0, 45});
    cubeEntity2->assignComponent<indie::components::Mesh, std::string>("../test_assets/cube.obj");
    auto mat2 = cubeEntity2->assignComponent<indie::components::Material, std::string>("../test_assets/cube_texture.png");
    mat2->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    mat2->setMaterialFlag(irr::video::EMF_WIREFRAME, true);

    auto particleSystemEntity = ecs.entityManager.createEntity("particleSystem");
    particleSystemEntity->assignComponent<indie::components::Transform, indie::maths::Vector3D>({0, 1, 0});
    auto sys = particleSystemEntity->assignComponent<indie::components::Particle, std::string>("p1");
    sys->setTexture(0, "../test_assets/particle_default.png");
    sys->setAngle(0);
    sys->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 255, 0, 0), irr::video::SColor(0, 0, 0, 255)));
    sys->setEmiterSize(irr::core::aabbox3df(-7, 0, -7, 7, 1, 7));
    sys->setEmitRate(std::make_pair(40, 80));
    sys->setFadeColor(irr::video::SColor(0, 0, 255, 0));
    sys->setFadeTime(1000);
    sys->setMinMaxAge(std::make_pair(800, 2000));
    sys->setMinMaxSize(std::make_pair(irr::core::dimension2d<irr::f32>(1, 1), irr::core::dimension2d<irr::f32>(2, 2)));
    sys->setInitialDirection(irr::core::vector3df(0.0f, 0.06f, 0.0f));
}

void indie::scenes::StaticTestScene::onStop()
{
    ECSWrapper ecs;
    for (auto &id : _listeners)
        ecs.eventManager.removeListener(id);
    _listeners.clear();
}
