/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PauseSystem.cpp
*/

/* Created the 15/06/2019 at 18:04 by brian */

#include "events/IrrlichtKeyJustChangedEvent.hpp"
#include "components/GUI/Font.hpp"
#include "ECSWrapper.hpp"
#include "input/InputManager.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/IrrklangAudioSystem.hpp"
#include "systems/AISystem.hpp"
#include "systems/BonusSystem.hpp"
#include "systems/DestroyOnTimeSystem.hpp"
#include "systems/LiveSystem.hpp"
#include "systems/TauntSystem.hpp"
#include "systems/BombManagerSystem.hpp"
#include "scenes/SceneManager.hpp"
#include "events/AskingForSaveEvent.hpp"
#include "systems/PauseSystem.hpp"

indie::systems::PauseSystem::PauseSystem()
    : _pauseButtonEventID()
{
    ECSWrapper ecs;

    InputManager::RegisterKey(irr::KEY_ESCAPE);
    _pauseButtonEventID = ecs.eventManager.addListener<void, events::IrrlichtKeyJustChangedEvent>(nullptr, [](void *, events::IrrlichtKeyJustChangedEvent e) {
        ECSWrapper ecs;

        if (e.keyCode == irr::KEY_ESCAPE && e.pressed && ecs.systemManager.getSystem<LiveSystem>().isGameLaunched()) {
            if (ecs.systemManager.getState<systems::PauseSystem>() == jf::systems::RUNNING) {
                ecs.systemManager.stopSystem<systems::PauseSystem>();
            } else if (ecs.systemManager.getState<systems::PauseSystem>() == jf::systems::STOPPED || ecs.systemManager.getState<systems::PauseSystem>() == jf::systems::NOT_STARTED) {
                ecs.systemManager.startSystem<systems::PauseSystem>();
            }
        }
    });
}

indie::systems::PauseSystem::~PauseSystem()
{
    ECSWrapper ecs;

    ecs.eventManager.removeListener(_pauseButtonEventID);
}

void indie::systems::PauseSystem::onAwake()
{

}

void indie::systems::PauseSystem::onStart()
{
    ECSWrapper ecs;

    ecs.systemManager.stopSystem<indie::systems::MovementSystem>();
    ecs.systemManager.stopSystem<indie::systems::BombManagerSystem>();
    ecs.systemManager.stopSystem<indie::systems::BonusSystem>();
    ecs.systemManager.stopSystem<indie::systems::DestroyOnTimeSystem>();
    ecs.systemManager.stopSystem<indie::systems::LiveSystem>();
    ecs.systemManager.stopSystem<indie::systems::TauntSystem>();
    ecs.systemManager.stopSystem<indie::systems::AISystem>();
    ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().pauseSounds(true);

    float gapSize = 10.0f;
    indie::maths::Vector3D buttonSize(500, 50, 0);
    indie::maths::Vector3D startPos((1280 - buttonSize.x) / 2, (720 - (buttonSize.y * 3 + gapSize * 2)) / 2, 0);

    auto backToGameButtonEntity = ecs.entityManager.createEntity("backToGameButton");
    auto backToGameButtonComponent = backToGameButtonEntity->assignComponent<components::Button>("Back to game", 1);
    auto backToGameButtonTransform = backToGameButtonEntity->assignComponent<components::Transform>();
    auto backToGameFont = backToGameButtonEntity->assignComponent<components::Font>("default_font");
    backToGameButtonTransform->setPosition(startPos);
    backToGameButtonTransform->setScale(buttonSize);
    backToGameButtonComponent->setTexturePath("button_default");

    backToGameButtonComponent->setOnClicked([](components::Button *self) {
        ECSWrapper ecs;

        ecs.systemManager.getSystem<PauseSystem>().destroyButtons();
        ecs.systemManager.stopSystem<PauseSystem>();
    });

    auto saveEntity = ecs.entityManager.createEntity("saveButton");
    auto saveComponent = saveEntity->assignComponent<components::Button>("Save and quit", 2);
    auto saveTransform = saveEntity->assignComponent<components::Transform>();
    auto saveFont = saveEntity->assignComponent<components::Font>("default_font");
    saveTransform->setPosition({startPos.x, startPos.y + buttonSize.y + gapSize, 0});
    saveTransform->setScale(buttonSize);
    saveComponent->setTexturePath("button_default");

    saveComponent->setOnClicked([](components::Button *self) {
        ECSWrapper ecs;

        ecs.systemManager.getSystem<PauseSystem>().destroyButtons();
        ecs.eventManager.emit<events::AskingForSaveEvent>({});
        scenes::SceneManager::safeChangeScene("mainMenu");
        ecs.systemManager.getSystem<systems::LiveSystem>().endGame();
        if (ecs.systemManager.getState<systems::PauseSystem>() == jf::systems::RUNNING)
            ecs.systemManager.stopSystem<PauseSystem>();
    });

    auto quitEntity = ecs.entityManager.createEntity("quitButton");
    auto quitComponent = quitEntity->assignComponent<components::Button>("Quit without saving", 3);
    auto quitTransform = quitEntity->assignComponent<components::Transform>();
    auto quitFont = quitEntity->assignComponent<components::Font>("default_font");
    quitTransform->setPosition({startPos.x, startPos.y + buttonSize.y * 2 + gapSize * 2, 0});
    quitTransform->setScale(buttonSize);
    quitComponent->setTexturePath("button_default");

    quitComponent->setOnClicked([](components::Button *self){
        ECSWrapper ecs;

        ecs.systemManager.getSystem<PauseSystem>().destroyButtons();
        scenes::SceneManager::safeChangeScene("mainMenu");
        ecs.systemManager.getSystem<systems::LiveSystem>().endGame();
        ecs.systemManager.stopSystem<PauseSystem>();
    });
}

void indie::systems::PauseSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{

}

void indie::systems::PauseSystem::onStop()
{
    ECSWrapper ecs;
    ecs.systemManager.startSystem<indie::systems::MovementSystem>();
    ecs.systemManager.startSystem<indie::systems::BombManagerSystem>();
    ecs.systemManager.startSystem<indie::systems::BonusSystem>();
    ecs.systemManager.startSystem<indie::systems::DestroyOnTimeSystem>();
    ecs.systemManager.startSystem<indie::systems::LiveSystem>();
    ecs.systemManager.startSystem<indie::systems::TauntSystem>();
    ecs.systemManager.startSystem<indie::systems::AISystem>();
    ecs.systemManager.getSystem<indie::systems::IrrklangAudioSystem>().playSounds(true);

    destroyButtons();
}

void indie::systems::PauseSystem::onTearDown()
{

}

void indie::systems::PauseSystem::destroyButtons()
{
    ECSWrapper ecs;

    try {
        ecs.entityManager.safeDeleteEntity(ecs.entityManager.getEntityByName("backToGameButton")->getID());
        ecs.entityManager.getEntityByName("backToGameButton")->setEnable(false);
    } catch (jf::BadHandlerException &e) {}
    try {
        ecs.entityManager.safeDeleteEntity(ecs.entityManager.getEntityByName("saveButton")->getID());
        ecs.entityManager.getEntityByName("saveButton")->setEnable(false);
    } catch (jf::BadHandlerException &e) {}
    try {
        ecs.entityManager.safeDeleteEntity(ecs.entityManager.getEntityByName("quitButton")->getID());
        ecs.entityManager.getEntityByName("quitButton")->setEnable(false);
    } catch (jf::BadHandlerException &e) {}
}
