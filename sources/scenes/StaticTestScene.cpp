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
#include "components/Hoverer.hpp"
#include "components/PlayerController.hpp"

void indie::scenes::StaticTestScene::onStart()
{
    ECSWrapper ecs;
    auto cameraEntity = ecs.entityManager.createEntity("camera");
    auto cameraTr = cameraEntity->assignComponent<indie::components::Transform>();
    cameraTr->setPosition({20, 10, 0});
    cameraTr->setRotation({25, -90, 0});
    cameraEntity->assignComponent<indie::components::Camera>();
    auto cameraControler = cameraEntity->assignComponent<indie::components::PlayerController, std::string, std::string, std::string>("xAxis", "yAxis", "zAxis");
    cameraControler->setAlwaysLookForward(false);
    cameraControler->setXRotationAxis("xRotAxis");
    cameraControler->setYRotationAxis("yRotAxis");
    cameraControler->setRotationSpeed(100);

    auto plEntity = ecs.entityManager.createEntity("pointLight");
    auto plTr = plEntity->assignComponent<indie::components::Transform>();
    plTr->setPosition({-1, 1, -1});
    plEntity->assignComponent<indie::components::PointLight>();

    auto cubeEntity = ecs.entityManager.createEntity("item");
    auto tr2 = cubeEntity->assignComponent<indie::components::Transform>();
    tr2->setPosition({5, 1, 0});
    cubeEntity->assignComponent<indie::components::Rotator, indie::maths::Vector3D>({0, 90, 0});
    cubeEntity->assignComponent<indie::components::Hoverer, indie::maths::Vector3D, indie::maths::Vector3D>({0, 1, 0}, {0, 1, 0});
    cubeEntity->assignComponent<indie::components::Mesh, std::string>("../test_assets/cube.obj");
    auto mat = cubeEntity->assignComponent<indie::components::Material, std::string>("../test_assets/cube_texture.png");
    mat->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
    mat->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    auto planeEntity = ecs.entityManager.createEntity("plane");
    auto planeTr = planeEntity->assignComponent<indie::components::Transform>();
    planeTr->setPosition({0, -1, 0});
    planeTr->setScale({100, 1, 100});
    planeEntity->assignComponent<indie::components::Mesh, std::string>("../test_assets/cube.obj");

    auto playerEntity = ecs.entityManager.createEntity("player");
    auto playerTr = playerEntity->assignComponent<indie::components::Transform>();
    auto playerMesh = playerEntity->assignComponent<indie::components::Mesh, std::string>("../test_assets/White/white.b3d");
    auto playerMat = playerEntity->assignComponent<indie::components::Material, std::string>("../test_assets/White/white.png");
    playerMat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    auto playerAnimator = playerEntity->assignComponent<indie::components::Animator, std::map<std::string, components::Animator::Animation>>({
        {"default", {.start = 0, .end = 0, .speed = 0, .loop = true, .transition = ""}},
        {"idle", {.start = 2, .end = 60, .speed = 20, .loop = true, .transition = ""}},
        {"walk", {.start = 62, .end = 121, .speed = 60, .loop = true, .transition = ""}},
        {"dab", {.start = 123, .end = 145, .speed = 40, .loop = false, .transition = "idle"}},
        {"place bomb", {.start = 184, .end = 243, .speed = 60, .loop = false, .transition = "idle"}},
        {"die", {.start = 245, .end = 304, .speed = 80, .loop = false, .transition = "dead"}},
        {"dead", {.start = 305, .end = 305, .speed = 0, .loop = true, .transition = ""}},
    });
    ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_W>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("default");
        }
    });
    ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_X>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("idle");
        }
    });
    ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_C>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("walk");
        }
    });
    ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_V>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("dab");
        }
    });
    ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_B>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("place bomb");
        }
    });
    ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_N>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("die");
        }
    });
    //auto playerControler = playerEntity->assignComponent<indie::components::PlayerController, std::string, std::string, std::string, bool, bool, bool>("xAxis", "yAxis", "zAxis", false, true, false);
    //playerControler->setAlwaysLookForward(true);
    //playerControler->setXRotationAxis("xRotAxis");
    //playerControler->setYRotationAxis("yRotAxis");
    //playerControler->setRotationSpeed(100);

    auto particleSystemEntity = ecs.entityManager.createEntity("particleSystem");
    particleSystemEntity->assignComponent<indie::components::Transform, indie::maths::Vector3D>({0, 1, 0});
    auto sys = particleSystemEntity->assignComponent<indie::components::Particle, std::string>("p1");
    sys->setTexture(0, "../test_assets/particle_default.png");
    sys->setAngle(0);
    sys->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 255, 0, 0), irr::video::SColor(0, 0, 0, 255)));
    sys->setEmiterSize(irr::core::aabbox3df(-100, 0, -100, 100, 1, 100));
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
