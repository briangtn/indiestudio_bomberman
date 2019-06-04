/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** StaticTestScene.cpp
*/

/* Created the 22/05/2019 at 18:36 by jfrabel */

#include "components/BoxCollider.hpp"
#include "components/GUI/Button.hpp"
#include "components/GUI/Font.hpp"
#include "events/IrrlichtGUIEvent.hpp"
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
    //auto cameraControler = cameraEntity->assignComponent<indie::components::PlayerController, std::string, std::string, std::string>("xAxis", "yAxis", "zAxis");
    //cameraControler->setAlwaysLookForward(false);
    //cameraControler->setXRotationAxis("xRotAxis");
    //cameraControler->setYRotationAxis("yRotAxis");
    //cameraControler->setRotationSpeed(100);

    auto plEntity = ecs.entityManager.createEntity("pointLight");
    auto plTr = plEntity->assignComponent<indie::components::Transform>();
    plTr->setPosition({-1, 1, -1});
    plEntity->assignComponent<indie::components::PointLight>();

    auto cubeEntity = ecs.entityManager.createEntity("item");
    auto tr2 = cubeEntity->assignComponent<indie::components::Transform>();
    cubeEntity->assignComponent<indie::components::BoxCollider, maths::Vector3D>({0.5f, 0.5f, 0.5f});
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
    playerEntity->assignComponent<indie::components::BoxCollider, maths::Vector3D, maths::Vector3D>({0.25f, 0.5f, 0.25f}, {0, 0.5f, 0});
    auto playerMesh = playerEntity->assignComponent<indie::components::Mesh, std::string>("../test_assets/White/white.b3d");
    auto playerMat = playerEntity->assignComponent<indie::components::Material, std::string>("../test_assets/White/white.png");
    playerMat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    auto playerAnimator = playerEntity->assignComponent<indie::components::Animator, std::map<std::string, components::Animator::Animation>>({
        {"default", components::Animator::Animation(0, 0, 0, true, "")},
        {"idle", components::Animator::Animation(2, 60, 20, true, "")},
        {"walk", components::Animator::Animation(62, 121, 60, true, "")},
        {"taunt", components::Animator::Animation(123, 145, 40, false, "idle")},
        {"place bomb", components::Animator::Animation(184, 243, 100, false, "idle")},
        {"die", components::Animator::Animation(245, 304, 100, false, "dead")},
        {"dead", components::Animator::Animation(305, 305, 0, true, "")},
    });
    auto playerControler = playerEntity->assignComponent<indie::components::PlayerController, indie::components::PlayerController::PlayerControllerSettings>({"xAxis", "zAxis", "taunt", "bomb"});
    playerControler->setMovementSpeed(5.0f);
    auto id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_W>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("default");
        }
    });
    _listeners.push_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_X>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("idle");
        }
    });
    _listeners.push_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_C>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("walk");
        }
    });
    _listeners.push_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_V>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("taunt");
        }
    });
    _listeners.push_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_B>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("place bomb");
        }
    });
    _listeners.push_back(id);
    id =  ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_N>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("die");
        }
    });
    _listeners.push_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_M>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            indie::systems::IrrlichtManagerSystem::drawGizmos(!indie::systems::IrrlichtManagerSystem::getDrawGizmos());
        }
    });

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

    auto btnEntity = ecs.entityManager.createEntity("testBtn");
    btnEntity->assignComponent<components::Transform>();
    auto btnCmp = btnEntity->assignComponent<components::Button, std::string, int>("La bite sur ton front", 1);
    btnEntity->assignComponent<components::Font, std::string>("../bigfont.png");
    btnEntity->getComponent<components::Transform>()->setScale(maths::Vector3D(300, 100, 0));
    btnCmp->setTexturePath("../4.png");
    btnCmp->setOnClicked([]() {
        std::cout << "I'm clicked" << std::endl;
    });
}

void indie::scenes::StaticTestScene::onStop()
{
    ECSWrapper ecs;
    for (auto &id : _listeners)
        ecs.eventManager.removeListener(id);
    _listeners.clear();
}
