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
#include "components/BoxCollider.hpp"
#include "events/AskingForBonusSpawnEvent.hpp"
#include "scenes/StaticTestScene.hpp"
#include "components/Material.hpp"
#include "components/Camera.hpp"
#include "exceptions/IrrlichtManagerExceptions.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "events/IrrlichtMouseInputEvent.hpp"
#include "ECSWrapper.hpp"
#include "components/ComponentParticle.hpp"
#include "Exceptions.hpp"
#include "map/Map.hpp"
#include "components/Rotator.hpp"
#include "components/Hoverer.hpp"
#include "components/PlayerController.hpp"
#include "assets_manager/AssetsManager.hpp"
#include "parser/Parser.hpp"

void indie::scenes::StaticTestScene::onStart()
{
    ECSWrapper ecs;
    auto cameraEntity = ecs.entityManager.createEntity("camera");
    auto cameraTr = cameraEntity->assignComponent<indie::components::Transform>();
    cameraTr->setPosition({50, 130, -105});
    cameraTr->setRotation({75, 0, 0});
    cameraEntity->assignComponent<indie::components::Camera>();

    indie::AssetsManager::getInstance().addTexturePack("Minecraft", "../test_assets/lol");

    auto playerEntity = ecs.entityManager.createEntity("player");
    auto playerTr = playerEntity->assignComponent<indie::components::Transform>();
    playerTr->setScale({8, 8, 8});
    playerEntity->assignComponent<indie::components::BoxCollider, maths::Vector3D, maths::Vector3D, uint64_t>({0.25f, 0.5f, 0.25f}, {0, 0.5f, 0}, P1_LAYER);
    auto playerMesh = playerEntity->assignComponent<indie::components::Mesh, std::string>("../test_assets/Players/player.b3d");
    auto playerMat = playerEntity->assignComponent<indie::components::Material, std::string>("../test_assets/Players/player1.png");
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
    auto id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_W>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("default");
        }
    });
    _listeners.emplace_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_X>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("idle");
        }
    });
    _listeners.emplace_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_C>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("walk");
        }
    });
    _listeners.emplace_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_V>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("taunt");
        }
    });
    _listeners.emplace_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_B>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("place bomb");
        }
    });
    _listeners.emplace_back(id);
    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_N>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.entityManager.getEntitiesByName("player")[0]->getComponent<components::Animator>()->setCurrentAnimation("die");
        }
    });
    _listeners.emplace_back(id);

    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_J>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            ecs.eventManager.emit(events::AskingForBonusSpawnEvent({{10, 1, 0}, components::BonusSpawner::BONUS_SPAWNER_T_RANDOM, components::BONUS_T_NB}));
        }
    });
    _listeners.emplace_back(id);

    indie::Map::generateMap(15, 13, 420, false);

    id = ecs.eventManager.addListener<void, events::IrrlichtSpecifiedKeyInputEvent<irr::KEY_KEY_M>>(nullptr, [](void *n, auto e) {
        ECSWrapper ecs;
        if (e.wasPressed) {
            indie::systems::IrrlichtManagerSystem::drawGizmos(!indie::systems::IrrlichtManagerSystem::getDrawGizmos());
        }
    });
    _listeners.emplace_back(id);

    auto particleSystemEntity = ecs.entityManager.createEntity("particleSystem");
    particleSystemEntity->assignComponent<indie::components::Transform, indie::maths::Vector3D>({0, 1, 0});
    auto sys = particleSystemEntity->assignComponent<indie::components::Particle, std::string>("p1");
    sys->setTexture(0, "../test_assets/particle_default.png");
    sys->setAngle(0);
    sys->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 255, 0, 0), irr::video::SColor(0, 0, 0, 255)));
    sys->setEmitterSize(irr::core::aabbox3df(-100, 0, -100, 100, 1, 100));
    sys->setEmitRate(std::make_pair(40, 80));
    sys->setFadeColor(irr::video::SColor(0, 0, 255, 0));
    sys->setFadeTime(1000);
    sys->setMinMaxAge(std::make_pair(800, 2000));
    sys->setMinMaxSize(std::make_pair(irr::core::dimension2d<irr::f32>(1, 1), irr::core::dimension2d<irr::f32>(2, 2)));
    sys->setInitialDirection(irr::core::vector3df(0.0f, 0.06f, 0.0f));

    auto textEntity = ecs.entityManager.createEntity("testText");
    textEntity->assignComponent<components::Transform>();
    auto textComp = textEntity->assignComponent<components::Text, std::string>("Salut toi");
    auto fontComp = textEntity->assignComponent<components::Font, std::string>("../bigfont.png");
    textEntity->getComponent<components::Transform>()->setScale(maths::Vector3D(300, 100, 0));
    textEntity->getComponent<components::Transform>()->setPosition(maths::Vector3D(400, 400, 0));
    textComp->setHorizontalAlignement(components::Text::CENTER);
    textComp->setBackgroundColor(irr::video::SColor(255, 255, 0, 0));
    textComp->setColor(irr::video::SColor(255, 0, 0, 255));

}

void indie::scenes::StaticTestScene::onStop()
{
    ECSWrapper ecs;
    for (auto &id : _listeners)
        ecs.eventManager.removeListener(id);
    _listeners.clear();
}

indie::scenes::StaticTestScene::StaticTestScene(): _listeners()
{

}
