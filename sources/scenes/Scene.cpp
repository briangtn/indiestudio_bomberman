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
#include "components/DestroyOnTime.hpp"
#include "events/AskingForSaveEvent.hpp"
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
#include "systems/IrrklangAudioSystem.hpp"
#include "input/Controller.hpp"
#include "components/Camera.hpp"
#include "components/Hoverer.hpp"
#include "components/PlayerController.hpp"
#include "components/Rotator.hpp"
#include "scenes/PlayerConfigScene.hpp"
#include "exceptions/ParserExceptions.hpp"
#include "components/LeaderBoard.hpp"
#include "components/AIController.hpp"
#include "components/DynamicCamera.hpp"
#include "components/PlayerAlive.hpp"
#include "components/GUI/Font.hpp"

indie::scenes::Scene::Scene(const std::string &fileName)
    : _fileName(fileName), _listeners()
{
}

void indie::scenes::Scene::onStart()
{
    try {
        Parser::getInstance().loadScene(std::string(SCENES_FOLDER_PATH) + "/" + _fileName);
    } catch (indie::exceptions::ParserDeviceException e){
        Parser::getInstance().loadScene(std::string(SAVES_FOLDER_PATH) + "/" + _fileName);
    }
    ECSWrapper ecs;

    if (_fileName == "mainMenu.xml") {
        auto startButton = ecs.entityManager.getEntitiesByName("startButton")[0]->getComponent<indie::components::Button>();
        auto loadSaveButton = ecs.entityManager.getEntitiesByName("loadSaveButton")[0]->getComponent<indie::components::Button>();
        auto settingsButton = ecs.entityManager.getEntitiesByName("settingsButton")[0]->getComponent<indie::components::Button>();
        auto exitButton = ecs.entityManager.getEntitiesByName("closeButton")[0]->getComponent<indie::components::Button>();

        startButton->setOnClicked([](indie::components::Button *button){
            indie::scenes::PlayerConfigScene::Load();
        });
        startButton->setOnHovered([](indie::components::Button *button, bool isHovered) {
            auto transform = button->getEntity()->getComponent<indie::components::Transform>();
            if (isHovered) {
                button->setTexturePath("button_new_game_hovered");
                transform->setPosition(indie::maths::Vector3D({
                    transform->getPosition().x - 10,
                    transform->getPosition().y,
                    transform->getPosition().z
                }));
            } else {
                button->setTexturePath("button_new_game");
                transform->setPosition(indie::maths::Vector3D({
                    transform->getPosition().x + 10,
                    transform->getPosition().y,
                    transform->getPosition().z
                }));
            }
        });
        settingsButton->setOnClicked([](indie::components::Button *button) {
           indie::scenes::SceneManager::safeChangeScene("settings");
        });
        loadSaveButton->setOnClicked([](indie::components::Button *button) {
            SceneManager::safeChangeScene("loadSave");
        });
        loadSaveButton->setOnHovered([](indie::components::Button *button, bool isHovered) {
            auto transform = button->getEntity()->getComponent<indie::components::Transform>();
            if (isHovered) {
                button->setTexturePath("button_load_game_hovered");
                transform->setPosition(indie::maths::Vector3D({
                    transform->getPosition().x - 10,
                    transform->getPosition().y,
                    transform->getPosition().z
                }));
            } else {
                button->setTexturePath("button_load_game");
                transform->setPosition(indie::maths::Vector3D({
                    transform->getPosition().x + 10,
                    transform->getPosition().y,
                    transform->getPosition().z
                }));
            }
        });
        settingsButton->setOnHovered([](indie::components::Button *button, bool isHovered) {
            auto transform = button->getEntity()->getComponent<indie::components::Transform>();
            if (isHovered) {
                button->setTexturePath("button_settings_hovered");
                transform->setPosition(indie::maths::Vector3D({
                    transform->getPosition().x - 10,
                    transform->getPosition().y,
                    transform->getPosition().z
                }));
            } else {
                button->setTexturePath("button_settings");
                transform->setPosition(indie::maths::Vector3D({
                    transform->getPosition().x + 10,
                    transform->getPosition().y,
                    transform->getPosition().z
                }));
            }
        });
        exitButton->setOnClicked([](indie::components::Button *button){
            ECSWrapper ecs;
            try {
                ecs.systemManager.stopSystem<indie::systems::IrrlichtManagerSystem>();
            } catch (std::exception e) {

            }
        });
        exitButton->setOnHovered([](indie::components::Button *button, bool isHovered) {
            auto transform = button->getEntity()->getComponent<indie::components::Transform>();
            if (isHovered) {
                button->setTexturePath("button_exit_hovered");
                transform->setPosition(indie::maths::Vector3D({
                    transform->getPosition().x - 10,
                    transform->getPosition().y,
                    transform->getPosition().z
                }));
            } else {
                button->setTexturePath("button_exit");
                transform->setPosition(indie::maths::Vector3D({
                    transform->getPosition().x + 10,
                    transform->getPosition().y,
                    transform->getPosition().z
                }));
            }
        });
    }
    if (_fileName == "settings.xml") {
        std::stringstream effectVolumeStringStream;
        std::stringstream musicVolumeStringStream;
        auto backToMenuButton = ecs.entityManager.getEntitiesByName("backToMenuButton")[0]->getComponent<indie::components::Button>();
        auto resourcesPacksButton = ecs.entityManager.getEntitiesByName("resourcesPacksButton")[0]->getComponent<indie::components::Button>();

        musicVolumeStringStream << ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getMusicVolume() * 100 << "%";
        effectVolumeStringStream << ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getEffectVolume() * 100 << "%";
        ecs.entityManager.getEntitiesByName("effectValueText")[0]->getComponent<indie::components::Text>()->setText(effectVolumeStringStream.str());
        ecs.entityManager.getEntitiesByName("musicValueText")[0]->getComponent<indie::components::Text>()->setText(musicVolumeStringStream.str());

        resourcesPacksButton->setOnClicked([](indie::components::Button *button) {
            indie::scenes::SceneManager::safeChangeScene("resourcesPacksScene");
        });
        backToMenuButton->setOnClicked([](indie::components::Button *button) {
            indie::scenes::SceneManager::safeChangeScene("mainMenu");
        });
        backToMenuButton->setOnHovered([](indie::components::Button *button, bool isHovered) {
            if (isHovered) {
                button->setTexturePath("button_back_to_menu_hovered");
            } else {
                button->setTexturePath("button_back_to_menu");
            }
        });

        // Effect Volume Management
        ecs.entityManager.getEntitiesByName("effectVolumeUpButton")[0]->getComponent<indie::components::Button>()->setOnClicked([](indie::components::Button *button) {
            std::stringstream effectVolumeStringStream;
            ECSWrapper ecs;

            if (ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getEffectVolume() + 0.05f < 1.05) {
                ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().setEffectVolume(ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getEffectVolume() + 0.05f);
                effectVolumeStringStream << ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getEffectVolume() * 100 << "%";
                ecs.entityManager.getEntitiesByName("effectValueText")[0]->getComponent<indie::components::Text>()->setText(effectVolumeStringStream.str());
            }
        });

        ecs.entityManager.getEntitiesByName("effectVolumeDownButton")[0]->getComponent<indie::components::Button>()->setOnClicked([](indie::components::Button *button) {
            std::stringstream effectVolumeStringStream;
            ECSWrapper ecs;
            int volume = static_cast<int>(ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getEffectVolume() * 100);

            if (ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getEffectVolume() > 0) {
                volume -= 5;
                ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().setEffectVolume(volume / 100.0f);
                effectVolumeStringStream << volume << "%";
                ecs.entityManager.getEntitiesByName("effectValueText")[0]->getComponent<indie::components::Text>()->setText(effectVolumeStringStream.str());
            }
        });

        // Music Volume Management
        ecs.entityManager.getEntitiesByName("musicVolumeUpButton")[0]->getComponent<indie::components::Button>()->setOnClicked([](indie::components::Button *button) {
            std::stringstream musicVolumeStringStream;
            ECSWrapper ecs;

            if (ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getMusicVolume() + 0.05f < 1.05) {
                ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().setMusicVolume(ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getMusicVolume() + 0.05f);
                musicVolumeStringStream << ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getMusicVolume() * 100 << "%";
                ecs.entityManager.getEntitiesByName("musicValueText")[0]->getComponent<indie::components::Text>()->setText(musicVolumeStringStream.str());
            }
        });

        ecs.entityManager.getEntitiesByName("musicVolumeDownButton")[0]->getComponent<indie::components::Button>()->setOnClicked([](indie::components::Button *button) {
            std::stringstream musicVolumeStringStream;
            ECSWrapper ecs;
            int volume = static_cast<int>(ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getMusicVolume() * 100);

            if (ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().getMusicVolume() > 0) {
                volume -= 5;
                ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().setMusicVolume(volume / 100.0f);
                musicVolumeStringStream << volume << "%";
                ecs.entityManager.getEntitiesByName("musicValueText")[0]->getComponent<indie::components::Text>()->setText(musicVolumeStringStream.str());
            }
        });
    }
    auto id = ecs.eventManager.addListener<Scene, events::AskingForSaveEvent>(this, [](Scene *self, events::AskingForSaveEvent e){
        self->save(true, true);
    });
    _listeners.emplace_back(id);
}

void indie::scenes::Scene::onStop()
{
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

    std::string name = saveName.substr(0, saveName.find(".xml"));
    scenes::IScene *scene = indie::Parser::getInstance().loadSingleScene(name, saveName);
    SceneManager::addSingleScene(name, scene);
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
    if (entity->hasComponent<components::Bomb>()) {
        components::Bomb &component = *(entity->getComponent<components::Bomb>().get());
        component >> file;
    }
    if (entity->hasComponent<components::BonusEffector>()) {
        components::BonusEffector &component = *(entity->getComponent<components::BonusEffector>().get());
        component >> file;
    }
    if (entity->hasComponent<components::BonusSpawner>()) {
        components::BonusSpawner &component = *(entity->getComponent<components::BonusSpawner>().get());
        component >> file;
    }
    if (entity->hasComponent<components::BoxCollider>()) {
        components::BoxCollider &component = *(entity->getComponent<components::BoxCollider>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Button>()) {
        components::Button &component = *(entity->getComponent<components::Button>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Camera>()) {
        components::Camera &component = *(entity->getComponent<components::Camera>().get());
        component >> file;
    }
    if (entity->hasComponent<components::DestroyOnTime>()) {
        components::DestroyOnTime &component = *(entity->getComponent<components::DestroyOnTime>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Font>()) {
        components::Font &component = *(entity->getComponent<components::Font>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Hoverer>()) {
        components::Hoverer &component = *(entity->getComponent<components::Hoverer>().get());
        component >> file;
    }
    if (entity->hasComponent<components::Image>()) {
        components::Image &component = *(entity->getComponent<components::Image>().get());
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
    if (entity->hasComponent<components::Text>()) {
        components::Text &component = *(entity->getComponent<components::Text>().get());
        component >> file;
    }
    if (entity->hasComponent<components::LeaderBoard>()) {
        components::LeaderBoard &component = *(entity->getComponent<components::LeaderBoard>().get());
        component >> file;
    }
    if (entity->hasComponent<components::AIController>()) {
        components::AIController &component = *(entity->getComponent<components::AIController>().get());
        component >> file;
    }
    if (entity->hasComponent<components::DynamicCamera>()) {
        components::DynamicCamera &component = *(entity->getComponent<components::DynamicCamera>().get());
        component >> file;
    }
    if (entity->hasComponent<components::PlayerAlive>()) {
        components::PlayerAlive &component = *(entity->getComponent<components::PlayerAlive>().get());
        component >> file;
    }
    if (entity->hasComponent<components::MoveToTarget>()) {
        components::MoveToTarget &component = *(entity->getComponent<components::MoveToTarget>().get());
        component >> file;
    }
    file << "    </entity>" << std::endl;
    return file;
}
