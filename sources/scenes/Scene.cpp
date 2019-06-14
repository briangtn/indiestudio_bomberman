/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Scene.cpp
*/

/* Created the 27/05/2019 at 15:27 by jbulteau */

#include <iostream>
#include <regex>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <boost/filesystem/operations.hpp>
#include "scenes/Scene.hpp"
#include "parser/Parser.hpp"
#include "ECSWrapper.hpp"
#include "parser/Parser.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "components/Transform.hpp"
#include "components/Animator.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "map/Map.hpp"
#include "ai/AiView.hpp"
#include "components/BonusSpawner.hpp"
#include "events/AskingForBonusSpawnEvent.hpp"
#include "ai/AStar.hpp"
#include "scenes/SceneManager.hpp"
#include "events/IrrlichtJoystickInputEvent.hpp"
#include "input/Controller.hpp"
#include "components/Camera.hpp"
#include "components/Hoverer.hpp"
#include "components/PlayerController.hpp"
#include "components/Rotator.hpp"
#include "components/LeaderBoard.hpp"

indie::scenes::Scene::Scene(const std::string &fileName)
    : _fileName(fileName), _listeners()
{
}

void indie::scenes::Scene::onStart()
{
    Parser::getInstance().loadScene(std::string(SCENES_FOLDER_PATH) + "/" + _fileName);
    ECSWrapper ecs;

    if (_fileName == "mainMenu.xml") {
        ecs.entityManager.getEntitiesByName("startButton")[0]->getComponent<indie::components::Button>()->setOnClicked([](indie::components::Button *button){
            indie::scenes::SceneManager::safeChangeScene("playerConfig");
        });
        ecs.entityManager.getEntitiesByName("closeButton")[0]->getComponent<indie::components::Button>()->setOnClicked([](indie::components::Button *button){
            ECSWrapper ecs;
            try {
                ecs.systemManager.stopSystem<indie::systems::IrrlichtManagerSystem>();
            } catch (std::exception e) {

            }
        });
    }
}

void indie::scenes::Scene::onStop()
{

    if (_fileName != "mainMenu.xml") {
        save(false, false);
    }
    ECSWrapper ecs;
    for (auto &id : _listeners)
        ecs.eventManager.removeListener(id);
    _listeners.clear();
}

indie::scenes::SaveState indie::scenes::Scene::save(bool override, bool saveShouldBeKeeped)
{
    std::time_t time = std::time(nullptr);
    std::stringstream date;
    std::string fileName = "save " + _fileName.substr(0, _fileName.length() - 4);

    date << std::put_time(std::localtime(&time), " %Y-%m-%d %H-%M-%S.xml");
    fileName += date.str();
    return save(fileName, override, saveShouldBeKeeped);
}

indie::scenes::SaveState indie::scenes::Scene::save(const std::string &saveName, bool override, bool saveShouldBeKeeped)
{
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

std::ostream &indie::operator<<(std::ostream &file, jf::entities::EntityHandler entity)
{
    file << "    <entity name=\"" << entity->getName() << "\" shouldBeKeeped=\"" << std::boolalpha
         << entity->shouldBeKeeped() << "\">" << std::endl;
    if (entity->hasComponent<components::Animator>()) {
        components::Animator &component = *(entity->getComponent<components::Animator>().get());
        component >> file;
    }
    if (entity->hasComponent<components::BoxCollider>()) {
        components::BoxCollider &component = *(entity->getComponent<components::BoxCollider>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Camera>()) {
        components::Camera &component = *(entity->getComponent<components::Camera>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Hoverer>()) {
        components::Hoverer &component = *(entity->getComponent<components::Hoverer>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Material>()) {
        components::Material &component = *(entity->getComponent<components::Material>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Mesh>()) {
        components::Mesh &component = *(entity->getComponent<components::Mesh>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Particle>()) {
        components::Particle &component =  *(entity->getComponent<components::Particle>().get());
        component >> file;
    }
    if (entity->hasComponent<components::PlayerController>()) {
        components::PlayerController &component = *(entity->getComponent<components::PlayerController>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Rotator>()) {
        components::Rotator &component = *(entity->getComponent<components::Rotator>().get());
        component >> file;
    }
    if (entity->hasComponent<components::SoundComponent>()) {
        components::SoundComponent &component = *(entity->getComponent<components::SoundComponent>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Transform>()) {
        components::Transform &component = *(entity->getComponent<components::Transform>().get());
        component >> file;
    }
    if (entity->hasComponent<components::LeaderBoard>()) {
        components::LeaderBoard &component = *(entity->getComponent<components::LeaderBoard>().get());
        component >> file;
    }
    file << "    </entity>" << std::endl;
    return file;
}
