/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PlayerConfigScene.cpp
*/

/* Created the 12/06/2019 at 13:59 by brian */

#include <regex>
#include "scenes/PlayerConfigScene.hpp"
#include "ECSWrapper.hpp"
#include "components/GUI/Image.hpp"
#include "components/Transform.hpp"
#include "components/Camera.hpp"
#include "components/GUI/Button.hpp"
#include "events/IrrlichtJoystickInputEvent.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "scenes/SceneManager.hpp"
#include "scenes/ControllerConfigScene.hpp"
#include "systems/IrrklangAudioSystem.hpp"

std::vector<indie::scenes::PlayerSettings> indie::scenes::PlayerConfigScene::playersSettings = {
    {INPUT_EXIST, Controller("")},
    {AI, Controller(""), true},
    {AI, Controller(""), true},
    {AI, Controller(""), true},
};

std::map<indie::scenes::PlayerControllerType, std::string> indie::scenes::PlayerConfigScene::controllerTypeImages = {
    {indie::scenes::INPUT_EXIST, "input_exist_icon"},
    {indie::scenes::INPUT_CONFIG, "input_config_icon"},
    {indie::scenes::AI, "ai_icon"},
    {indie::scenes::NONE, "none_icon"}
};

std::map<std::string, indie::Controller> indie::scenes::PlayerConfigScene::controllers;

void indie::scenes::PlayerConfigScene::InitControllers()
{
    Controller controller = Controller("");

    controller.addAxis<KeyAxis>("xAxis", {irr::KEY_KEY_D, irr::KEY_KEY_Q});
    controller.addAxis<KeyAxis>("zAxis", {irr::KEY_KEY_Z, irr::KEY_KEY_S});
    controller.addKey("taunt", irr::KEY_KEY_U);
    controller.addKey("bomb", irr::KEY_KEY_B);

    controllers.emplace("IndieDefaultKeyboard", controller);

    controller = Controller("");
    controller.addAxis<JoystickAxis>("xAxis", {0, 0});
    controller.addAxis<JoystickAxis>("zAxis", {0, 1, true});
    controller.addKey("taunt", 0, 1);
    controller.addKey("bomb", 0, 2);

    controllers.emplace(".*Xbox One Controller.*", controller);

    controller = Controller("");
    controller.addAxis<JoystickAxis>("xAxis", {0, 0});
    controller.addAxis<JoystickAxis>("zAxis", {0, 1, true});
    controller.addKey("taunt", 0, 0);
    controller.addKey("bomb", 0, 2);

    controllers.emplace(".*Sony.*Controller.*", controller);
}

void indie::scenes::PlayerConfigScene::onStart()
{
    ECSWrapper ecs;

    auto cameraEntity = ecs.entityManager.createEntity("camera");
    cameraEntity->assignComponent<indie::components::Camera>();
    auto cameraTransform = cameraEntity->assignComponent<indie::components::Transform>();

    auto soundEntity = ecs.entityManager.createEntity("playerSelectMusic");
    auto sound = soundEntity->assignComponent<indie::components::SoundComponent>("music_player_select", components::SoundComponent::MUSIC);
    sound->setIsLooped(true);
    sound->setIsPaused(false);

    auto buttonStartEntity = ecs.entityManager.createEntity("buttonStart");
    auto buttonStartComponent = buttonStartEntity->assignComponent<indie::components::Button>("", 3);
    auto buttonStartTransform = buttonStartEntity->assignComponent<indie::components::Transform>();
    buttonStartTransform->setPosition({(1280 - 200) / 2, (720 - 200) / 2, 100});
    buttonStartTransform->setScale({200, 200, 0});
    buttonStartComponent->setTexturePath("play_button");
    buttonStartComponent->setUseAlpha(true);
    buttonStartComponent->setDrawBorder(false);
    buttonStartComponent->setVisible(false);

    buttonStartComponent->setOnClicked([](components::Button *btn){
        for (auto setting : playersSettings) {
            if (!setting.isValid)
                return;
        }
        int i = 1;
        for (auto setting : playersSettings) {
            std::string iStr = std::to_string(i);

            if (setting.controllerType != AI)
                setting.controller.generateKeysAndAxes("player" + iStr);
            i++;
        }
        indie::scenes::SceneManager::safeChangeScene("newGameScene");
    });

    auto buttonReloadEntity = ecs.entityManager.createEntity("buttonReload");
    auto buttonReloadComponent = buttonReloadEntity->assignComponent<indie::components::Button>("", 4);
    auto buttonReloadTransform = buttonReloadEntity->assignComponent<indie::components::Transform>();
    buttonReloadTransform->setPosition({(1280 - 128), 0, 100});
    buttonReloadTransform->setScale({128, 128, 0});
    buttonReloadComponent->setTexturePath("reload_button");
    buttonReloadComponent->setUseAlpha(true);
    buttonReloadComponent->setDrawBorder(false);

    buttonReloadComponent->setOnClicked([](components::Button *button) {
        ECSWrapper ecs;

        ecs.systemManager.getSystem<systems::IrrlichtManagerSystem>().reloadJoysticks();
    });

    for (unsigned int i = 1; i <= 4; i++)
        createConfigBlock(i);

    auto backgroundEntity = ecs.entityManager.createEntity("background");
    backgroundEntity->assignComponent<indie::components::Image>("default_menu_background");
    auto backgroundTransform = backgroundEntity->assignComponent<indie::components::Transform>();
    backgroundTransform->setPosition({0, 0, -1});
    UpdateConfigController();
}

void indie::scenes::PlayerConfigScene::onStop()
{
    ECSWrapper ecs;

    for (auto &setting : playersSettings) {
        removeListeners(setting);
    }
}

void indie::scenes::PlayerConfigScene::createConfigBlock(int id)
{
    ECSWrapper ecs;
    unsigned int x = (id - 1) % 2;
    unsigned int y = (id / 2) - x;
    const indie::maths::Vector2D buttonSize = {30, 200};
    const indie::maths::Vector2D imageSize = {200, 200};
    const indie::maths::Vector2D screenSize = {1280, 720};
    const unsigned int gapSize = 10;
    const indie::maths::Vector2D blockSize = {buttonSize.x * 2 + gapSize * 2 + imageSize.x, 200};
    const indie::maths::Vector2D basePos = {(screenSize.x / 4) * ((x * 2) + 1) - (blockSize.x / 2),
                                            (screenSize.y / 4) * ((y * 2) + 1) - (blockSize.y / 2),};
    std::string idString = std::to_string(id);

    auto validImageEntity = ecs.entityManager.createEntity("validImage" + idString);
    auto validImageComponent = validImageEntity->assignComponent<indie::components::Image>("valid_selection_icon");
    auto validImageTransform = validImageEntity->assignComponent<indie::components::Transform>();
    validImageTransform->setPosition({basePos.x + buttonSize.x + gapSize, basePos.y, 1});
    validImageComponent->setUseAlpha(true);
    validImageComponent->setVisible(playersSettings[id - 1].isValid);

    auto imageEntity = ecs.entityManager.createEntity("image" + idString);
    auto imageComponent = imageEntity->assignComponent<indie::components::Image>(controllerTypeImages[playersSettings[id - 1].controllerType]);
    auto imageTransform = imageEntity->assignComponent<indie::components::Transform>();
    imageTransform->setPosition({basePos.x + buttonSize.x + gapSize, basePos.y, 0});
    imageComponent->setUseAlpha(true);

    auto leftButton = ecs.entityManager.createEntity("leftButton" + idString);
    auto leftButtonComponent = leftButton->assignComponent<indie::components::Button>("", 10 + id);
    auto leftButtonTransform = leftButton->assignComponent<indie::components::Transform>();
    leftButtonTransform->setPosition({basePos.x, basePos.y, 0});
    leftButtonTransform->setScale({buttonSize.x, buttonSize.y, 0});

    auto rightButton = ecs.entityManager.createEntity("rightButton" + idString);
    auto rightButtonComponent = rightButton->assignComponent<indie::components::Button>("", 20 + id);
    auto rightButtonTransform = rightButton->assignComponent<indie::components::Transform>();
    rightButtonTransform->setPosition({basePos.x + gapSize * 2 + buttonSize.x + imageSize.x, basePos.y, 0});
    rightButtonTransform->setScale({buttonSize.x, buttonSize.y, 0});

    auto detectControllerButton = ecs.entityManager.createEntity("detectControllerButton" + idString);
    auto detectControllerButtonComponent = detectControllerButton->assignComponent<indie::components::Button>("Detect controller", 30 + id);
    auto detectControllerButtonTransform = detectControllerButton->assignComponent<indie::components::Transform>();
    detectControllerButtonTransform->setPosition({basePos.x, basePos.y + blockSize.y, 0});
    detectControllerButtonTransform->setScale({blockSize.x, 50, 0});

    auto configControllerButton = ecs.entityManager.createEntity("configControllerButton" + idString);
    auto configControllerButtonComponent = configControllerButton->assignComponent<indie::components::Button>("Config controller", 40 + id);
    auto configControllerButtonTransform = configControllerButton->assignComponent<indie::components::Transform>();
    configControllerButtonTransform->setPosition({basePos.x, basePos.y + blockSize.y, 0});
    configControllerButtonTransform->setScale({blockSize.x, 50, 0});

    if (playersSettings[id - 1].controllerType != INPUT_EXIST)
        detectControllerButtonComponent->setVisible(false);
    if (playersSettings[id - 1].controllerType != INPUT_CONFIG)
        configControllerButtonComponent->setVisible(false);

    leftButtonComponent->setOnClicked([id](components::Button *btn){
        bool valid = playersSettings[id - 1].isValid;
        switch (playersSettings[id - 1].controllerType) {
            case INPUT_EXIST:
                from(INPUT_EXIST, id);
                to(NONE, id);
                break;
            case INPUT_CONFIG:
                from(INPUT_CONFIG, id);
                to(INPUT_EXIST, id);
                break;
            case AI:
                from(AI, id);
                to(INPUT_CONFIG, id);
                break;
            case NONE:
                from(NONE, id);
                to(AI, id);
                break;
        }
        if (valid)
            setValid(false, id);
        else
            updatePlayButton();
        removeListeners(playersSettings[id - 1]);
    });

    rightButtonComponent->setOnClicked([id](components::Button *btn){
        bool valid = playersSettings[id - 1].isValid;
        switch (playersSettings[id - 1].controllerType) {
            case INPUT_EXIST:
                from(INPUT_EXIST, id);
                to(INPUT_CONFIG, id);
                break;
            case INPUT_CONFIG:
                from(INPUT_CONFIG, id);
                to(AI, id);
                break;
            case AI:
                from(AI, id);
                to(NONE, id);
                break;
            case NONE:
                from(NONE, id);
                to(INPUT_EXIST, id);
                break;
        }
        if (valid)
            setValid(false, id);
        else
            updatePlayButton();
        removeListeners(playersSettings[id - 1]);
    });

    detectControllerButtonComponent->setOnClicked([id](components::Button *btn) {
        indie::scenes::PlayerConfigScene::onWaitForInput(id);
    });

    configControllerButtonComponent->setOnClicked([id](components::Button *btn) {
        ControllerConfigScene::id = id;
        SceneManager::safeChangeScene("controllerConfig");
    });
}

void indie::scenes::PlayerConfigScene::from(indie::scenes::PlayerControllerType controllerType, int id)
{
    ECSWrapper ecs;
    std::string idString = std::to_string(id);

    if (controllerType == INPUT_EXIST) {
        auto buttonEntity = ecs.entityManager.getEntityByName("detectControllerButton" + idString);
        auto buttonComponent = buttonEntity->getComponent<components::Button>();
        removeListeners(playersSettings[id - 1]);
        buttonComponent->setVisible(false);
    } else if (controllerType == INPUT_CONFIG) {
        auto buttonEntity = ecs.entityManager.getEntityByName("configControllerButton" + idString);
        auto buttonComponent = buttonEntity->getComponent<components::Button>();
        buttonComponent->setVisible(false);
    }
}

void indie::scenes::PlayerConfigScene::to(indie::scenes::PlayerControllerType controllerType, int id)
{
    ECSWrapper ecs;
    std::string idString = std::to_string(id);

    playersSettings[id - 1].controllerType = controllerType;

    auto imageEntity = ecs.entityManager.getEntityByName("image" + idString);
    auto imageComponent = imageEntity->getComponent<components::Image>();
    imageComponent->setPath(controllerTypeImages[controllerType]);
    imageComponent->reload();

    if (controllerType == INPUT_EXIST) {
        auto buttonEntity = ecs.entityManager.getEntityByName("detectControllerButton" + idString);
        auto buttonComponent = buttonEntity->getComponent<components::Button>();
        buttonComponent->setVisible(true);
    } else if (controllerType == INPUT_CONFIG) {
        auto buttonEntity = ecs.entityManager.getEntityByName("configControllerButton" + idString);
        auto buttonComponent = buttonEntity->getComponent<components::Button>();
        buttonComponent->setVisible(true);
    } else if (controllerType == AI) {
        setValid(true, id);
    }
}

void indie::scenes::PlayerConfigScene::setValid(bool valid, int id)
{
    ECSWrapper ecs;
    std::string idString = std::to_string(id);
    auto &settings = playersSettings[id - 1];

    auto imageEntity = ecs.entityManager.getEntityByName("validImage" + idString);
    auto imageComponent = imageEntity->getComponent<components::Image>();

    imageComponent->reload();
    imageComponent->setVisible(valid);
    settings.isValid = valid;
    updatePlayButton();
}

void indie::scenes::PlayerConfigScene::onWaitForInput(int id)
{
    ECSWrapper ecs;

    removeListeners(playersSettings[id - 1]);
    auto eventId = ecs.eventManager.addListener<void, events::IrrlichtKeyInputEvent>(nullptr, [id](void *a, events::IrrlichtKeyInputEvent e){
        auto controller = controllers.find("IndieDefaultKeyboard");
        if (controller == controllers.end()) {
            return;
        }
        indie::scenes::PlayerConfigScene::playersSettings[id - 1].controller = controller->second;
        indie::scenes::PlayerConfigScene::setValid(true, id);
        removeListeners(playersSettings[id - 1]);
    });
    playersSettings[id - 1].eventKeyboardId = eventId;
    eventId = ecs.eventManager.addListener<void, events::IrrlichtJoystickEvent>(nullptr, [id](void *a, events::IrrlichtJoystickEvent e) {
        for (int i = 0; i < e.data.NUMBER_OF_BUTTONS; i++) {
            if (e.data.IsButtonPressed(i)) {
                ECSWrapper ecs;
                auto &system = ecs.systemManager.getSystem<systems::IrrlichtManagerSystem>();
                std::string name = std::string(system.getJoystickInfos()[e.data.Joystick].Name.c_str());

                for (auto &controller : controllers) {
                    std::regex reg(controller.first);
                    if (std::regex_match(name, reg)) {
                        controller.second.setControllerId(e.data.Joystick);
                        indie::scenes::PlayerConfigScene::playersSettings[id - 1].controller = controller.second;
                        setValid(true, id);
                        removeListeners(playersSettings[id - 1]);
                        return;
                    }
                }
            }
        }
    });
    playersSettings[id - 1].eventJoystickId = eventId;
}

void indie::scenes::PlayerConfigScene::UpdateConfigController()
{
    int id = ControllerConfigScene::id;

    if (id <= 0)
        return;
    playersSettings[id - 1].controller = ControllerConfigScene::controller;
    setValid(true, id);

    ControllerConfigScene::id = -1;
    ControllerConfigScene::controller = Controller("");
}

indie::scenes::SaveState indie::scenes::PlayerConfigScene::save(bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}

indie::scenes::SaveState
indie::scenes::PlayerConfigScene::save(const std::string &saveName, bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}

void indie::scenes::PlayerConfigScene::updatePlayButton()
{
    ECSWrapper ecs;

    auto buttonEntity = ecs.entityManager.getEntityByName("buttonStart");
    auto buttonComponent = buttonEntity->getComponent<components::Button>();
    int noneCount = 0;
    for (auto &playerSetting : playersSettings) {
        if (playerSetting.controllerType == NONE)
            noneCount++;
        if ((!playerSetting.isValid && playerSetting.controllerType != NONE) || noneCount > 2) {
            buttonComponent->setVisible(false);
            return;
        }
    }
    buttonComponent->setVisible(true);
}

void indie::scenes::PlayerConfigScene::removeListeners(indie::scenes::PlayerSettings &settings)
{
    ECSWrapper ecs;

    if (settings.eventKeyboardId.isValid())
        ecs.eventManager.removeListener(settings.eventKeyboardId);
    if (settings.eventJoystickId.isValid())
        ecs.eventManager.removeListener(settings.eventJoystickId);
}
