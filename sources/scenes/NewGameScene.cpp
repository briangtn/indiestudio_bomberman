/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** NewGameScene.cpp
*/

/* Created the 13/06/2019 at 16:34 by jfrabel */

#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <random>
#include <boost/filesystem/operations.hpp>
#include "ECSWrapper.hpp"
#include "scenes/NewGameScene.hpp"
#include "parser/Parser.hpp"
#include "map/Map.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/LiveSystem.hpp"
#include "scenes/PlayerConfigScene.hpp"
#include "components/Transform.hpp"
#include "components/Material.hpp"
#include "components/Mesh.hpp"
#include "components/AIController.hpp"
#include "components/PlayerController.hpp"
#include "components/Camera.hpp"
#include "components/DynamicCamera.hpp"
#include "systems/IrrklangAudioSystem.hpp"
#include "components/PlayerAlive.hpp"

indie::scenes::NewGameScene::NewGameScene()
    : _saveOnExit(true), _saveName("default.xml")
{

}

void indie::scenes::NewGameScene::onStart()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    auto seed = dist(rd);
    std::cout << "Seed: " << seed << std::endl;
    indie::Map::generateMap(mapWidth, mapHeight, -2097377204, false);
    ECSWrapper ecs;
    ecs.systemManager.getSystem<systems::MovementSystem>().setMapSize(
        {static_cast<float>(mapWidth), static_cast<float>(mapHeight)});

    for (int i = 0; i < 4; i++) {
        if (PlayerConfigScene::playersSettings[i].controllerType == NONE)
            continue;
        jf::entities::EntityHandler p;
        switch (i) {
            case 0:
                p = spawnBlack();
                break;
            case 1:
                p = spawnBlue();
                break;
            case 2:
                p = spawnWhite();
                break;
            case 3:
                p = spawnYellow();
                break;
        }
        assignSpecificComponents(p, PlayerConfigScene::playersSettings[i].controllerType);
    }
    spawnCamera();
    auto entity = ecs.entityManager.createEntity("sound");
    auto component = entity->assignComponent<components::SoundComponent>("music_battle", components::SoundComponent::MUSIC);
    component->setSound(ecs.systemManager.getSystem<systems::IrrklangAudioSystem>().add2DSound(component->getSourceFile(), true, false));
    ecs.systemManager.getSystem<systems::LiveSystem>().startNewGame();
}

void indie::scenes::NewGameScene::onStop()
{
    if (_saveOnExit)
        save(_saveName, true, true);
}

indie::scenes::SaveState indie::scenes::NewGameScene::save(bool override, bool saveShouldBeKeeped)
{
    std::time_t time = std::time(nullptr);
    std::stringstream date;
    std::string fileName = "save " + _saveName.substr(0, _saveName.length() - 4);

    date << std::put_time(std::localtime(&time), " %Y-%m-%d %H-%M-%S.xml");
    fileName += date.str();
    return save(fileName, override, saveShouldBeKeeped);
}

indie::scenes::SaveState indie::scenes::NewGameScene::save(const std::string &saveName, bool override, bool saveShouldBeKeeped)
{
    if (!_saveOnExit)
        return SUCCESS;
    ECSWrapper ecs;
    std::string path(std::string(SAVES_FOLDER_PATH) + "/" + saveName);

    if (boost::filesystem::exists(path)) {
        if (override) {
            boost::filesystem::remove(path);
        } else {
            return FAIL;
        }
    }
    std::ofstream file(path);
    file << "<?xml version=\"1.0\"?>" << std::endl << "<scene>" << std::endl;
    ecs.entityManager.applyToEach(
        [&](jf::entities::EntityHandler entity) {
            if (!(!saveShouldBeKeeped && entity->shouldBeKeeped())) {
                file << entity;
            }
        });
    file << "</scene>" << std::endl;
    return SUCCESS;
}

jf::entities::EntityHandler indie::scenes::NewGameScene::spawnBlack()
{
    ECSWrapper ecs;
    auto entity = ecs.entityManager.createEntity("player1");
    entity->assignComponent<components::Transform, maths::Vector3D, maths::Vector3D, maths::Vector3D>({0, -5, 0}, {0, 180, 0}, {8, 8, 8});
    auto mat = entity->assignComponent<components::Material, std::string>("player_texture_black");
    mat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    entity->assignComponent<components::Mesh, std::string>("player_model");
    entity->assignComponent<indie::components::Animator, std::map<std::string, components::Animator::Animation>>({
        {"default", components::Animator::Animation(0, 0, 0, true, "")},
        {"idle", components::Animator::Animation(2, 60, 20, true, "")},
        {"walk", components::Animator::Animation(62, 121, 60, true, "")},
        {"taunt", components::Animator::Animation(123, 145, 40, false, "idle")},
        {"place_bomb", components::Animator::Animation(184, 243, 120, false, "idle")},
        {"die", components::Animator::Animation(245, 304, 100, false, "dead")},
        {"dead", components::Animator::Animation(305, 305, 0, true, "")},
        {"dabLoop", components::Animator::Animation(123, 145, 40, true, "")},
    });
    entity->assignComponent<components::BoxCollider, maths::Vector3D, maths::Vector3D, uint64_t>({0.25f, 0.5f, 0.25f}, {0, 0.5f, 0}, P1_LAYER);
    entity->assignComponent<components::PlayerAlive, int>(nbStartingLives);
    return entity;
}

jf::entities::EntityHandler indie::scenes::NewGameScene::spawnBlue()
{
    ECSWrapper ecs;
    auto entity = ecs.entityManager.createEntity("player2");
    entity->assignComponent<components::Transform, maths::Vector3D, maths::Vector3D, maths::Vector3D>({10.0f * (mapWidth - 1), -5, 0}, {0, 180, 0}, {8, 8, 8});
    auto mat = entity->assignComponent<components::Material, std::string>("player_texture_blue");
    mat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    entity->assignComponent<components::Mesh, std::string>("player_model");
    entity->assignComponent<indie::components::Animator, std::map<std::string, components::Animator::Animation>>({
        {"default", components::Animator::Animation(0, 0, 0, true, "")},
        {"idle", components::Animator::Animation(2, 60, 20, true, "")},
        {"walk", components::Animator::Animation(62, 121, 60, true, "")},
        {"taunt", components::Animator::Animation(123, 145, 40, false, "idle")},
        {"place_bomb", components::Animator::Animation(184, 243, 120, false, "idle")},
        {"die", components::Animator::Animation(245, 304, 100, false, "dead")},
        {"dead", components::Animator::Animation(305, 305, 0, true, "")},
        {"dabLoop", components::Animator::Animation(123, 145, 40, true, "")},
        {"taunt", components::Animator::Animation(123, 145, 40, false, "idle")},
    });
    entity->assignComponent<components::BoxCollider, maths::Vector3D, maths::Vector3D, uint64_t>({0.25f, 0.5f, 0.25f}, {0, 0.5f, 0}, P2_LAYER);
    entity->assignComponent<components::PlayerAlive, int>(nbStartingLives);
    return entity;
}

jf::entities::EntityHandler indie::scenes::NewGameScene::spawnWhite()
{
    ECSWrapper ecs;
    auto entity = ecs.entityManager.createEntity("player3");
    entity->assignComponent<components::Transform, maths::Vector3D, maths::Vector3D, maths::Vector3D>({0, -5, -10.0f * (mapHeight - 1)}, {0, 180, 0}, {8, 8, 8});
    auto mat = entity->assignComponent<components::Material, std::string>("player_texture_white");
    mat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    entity->assignComponent<components::Mesh, std::string>("player_model");
    entity->assignComponent<indie::components::Animator, std::map<std::string, components::Animator::Animation>>({
        {"default", components::Animator::Animation(0, 0, 0, true, "")},
        {"idle", components::Animator::Animation(2, 60, 20, true, "")},
        {"walk", components::Animator::Animation(62, 121, 60, true, "")},
        {"place_bomb", components::Animator::Animation(184, 243, 120, false, "idle")},
        {"die", components::Animator::Animation(245, 304, 100, false, "dead")},
        {"dead", components::Animator::Animation(305, 305, 0, true, "")},
        {"dabLoop", components::Animator::Animation(123, 145, 40, true, "")},
        {"taunt", components::Animator::Animation(123, 145, 40, false, "idle")},
    });
    entity->assignComponent<components::BoxCollider, maths::Vector3D, maths::Vector3D, uint64_t>({0.25f, 0.5f, 0.25f}, {0, 0.5f, 0}, P3_LAYER);
    entity->assignComponent<components::PlayerAlive, int>(nbStartingLives);
    return entity;
}

jf::entities::EntityHandler indie::scenes::NewGameScene::spawnYellow()
{
    ECSWrapper ecs;
    auto entity = ecs.entityManager.createEntity("player4");
    entity->assignComponent<components::Transform, maths::Vector3D, maths::Vector3D, maths::Vector3D>({10.0f * (mapWidth - 1), -5, -10.0f * (mapHeight - 1)}, {0, 180, 0}, {8, 8, 8});
    auto mat = entity->assignComponent<components::Material, std::string>("player_texture_yellow");
    mat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    entity->assignComponent<components::Mesh, std::string>("player_model");
    entity->assignComponent<indie::components::Animator, std::map<std::string, components::Animator::Animation>>({
        {"default", components::Animator::Animation(0, 0, 0, true, "")},
        {"idle", components::Animator::Animation(2, 60, 20, true, "")},
        {"walk", components::Animator::Animation(62, 121, 60, true, "")},
        {"place_bomb", components::Animator::Animation(184, 243, 120, false, "idle")},
        {"die", components::Animator::Animation(245, 304, 100, false, "dead")},
        {"dead", components::Animator::Animation(305, 305, 0, true, "")},
        {"dabLoop", components::Animator::Animation(123, 145, 40, true, "")},
        {"taunt", components::Animator::Animation(123, 145, 40, false, "idle")},
    });
    entity->assignComponent<components::BoxCollider, maths::Vector3D, maths::Vector3D, uint64_t>({0.25f, 0.5f, 0.25f}, {0, 0.5f, 0}, P4_LAYER);
    entity->assignComponent<components::PlayerAlive, int>(nbStartingLives);
    return entity;
}

void indie::scenes::NewGameScene::assignSpecificComponents(jf::entities::EntityHandler entity,
                                                           indie::scenes::PlayerControllerType type)
{

    std::map<std::string, components::PlayerType> map = {
        {"player1", components::P1},
        {"player2", components::P2},
        {"player3", components::P3},
        {"player4", components::P4},
    };
    if (type == AI) {
        auto ai = entity->assignComponent<components::AIController>();
        ai->setPlayerType(map[entity->getName()]);
        auto mtt = entity->assignComponent<components::MoveToTarget>();
    } else {
        auto pc = entity->assignComponent<components::PlayerController, components::PlayerController::PlayerControllerSettings>({
            entity->getName() + "xAxis",
            entity->getName() + "zAxis",
            entity->getName() + "taunt",
            entity->getName() + "bomb",
        });
        pc->setPlayerType(map[entity->getName()]);
    }
}

jf::entities::EntityHandler indie::scenes::NewGameScene::spawnCamera()
{
    ECSWrapper ecs;
    auto entity = ecs.entityManager.createEntity("camera");
    entity->assignComponent<components::Transform, maths::Vector3D, maths::Vector3D>({70, 150, -140}, {70, 0, 0});
    entity->assignComponent<components::Camera>();
    //entity->assignComponent<components::DynamicCamera>();
    return entity;
}
