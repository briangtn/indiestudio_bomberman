/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** ControllerConfigScene.cpp
*/

/* Created the 13/06/2019 at 00:29 by brian */

#include <algorithm>
#include "scenes/ControllerConfigScene.hpp"
#include "scenes/SceneManager.hpp"
#include "ECSWrapper.hpp"
#include "events/IrrlichtKeyJustChangedEvent.hpp"
#include "events/IrrlichtKeyInputEvent.hpp"
#include "events/IrrlichtJoystickInputEvent.hpp"
#include "scenes/PlayerConfigScene.hpp"
#include "components/GUI/Image.hpp"
#include "components/Transform.hpp"
#include "components/GUI/Text.hpp"
#include "components/GUI/Font.hpp"

int indie::scenes::ControllerConfigScene::id = -1;
indie::Controller indie::scenes::ControllerConfigScene::controller("");
indie::scenes::ControllerConfigScene::Step indie::scenes::ControllerConfigScene::step = UP;
std::vector<jf::internal::ID> indie::scenes::ControllerConfigScene::listeners;
std::vector<irr::u16> indie::scenes::ControllerConfigScene::keysPressed;
std::vector<irr::u16> indie::scenes::ControllerConfigScene::joysticksActivated;

void indie::scenes::ControllerConfigScene::onStart()
{
    ECSWrapper ecs;

    auto backgroundEntity = ecs.entityManager.createEntity("background");
    backgroundEntity->assignComponent<indie::components::Image>("../background.png");
    auto backgroundTransform = backgroundEntity->assignComponent<indie::components::Transform>();
    backgroundTransform->setPosition({0, 0, -1});

    auto textEntity = ecs.entityManager.createEntity("infoText");
    auto textComponent = textEntity->assignComponent<indie::components::Text>("...");
    auto transform = textEntity->assignComponent<indie::components::Transform>();
    transform->setScale({1280, 720, 0});
    textComponent->setColor(irr::video::SColor(255, 255, 0, 0));
    textComponent->setVerticalAlignement(components::Text::MIDDLE);
    textComponent->setHorizontalAlignement(components::Text::CENTER);
    textEntity->assignComponent<indie::components::Font>("../bigfont.png");

    up();
}

void indie::scenes::ControllerConfigScene::onStop()
{
    keysPressed.empty();
    joysticksActivated.empty();
    removeListeners();
}

void indie::scenes::ControllerConfigScene::up()
{
    ECSWrapper ecs;
    step = UP;

    setInfoText("Waiting for pressing up key or moving up/down axis");
    auto eventId = ecs.eventManager.addListener<void, events::IrrlichtKeyInputEvent>(nullptr, [&](void *a, events::IrrlichtKeyInputEvent e){
        if (e.wasReleased && step == UP)
            down(e.keyCode);
    });
    listeners.push_back(eventId);
    eventId = ecs.eventManager.addListener<void, events::IrrlichtJoystickEvent>(nullptr, [](void *a, events::IrrlichtJoystickEvent e){
        if (step != UP)
            return;
        for (unsigned char i = 0; i < e.data.NUMBER_OF_BUTTONS; i++) {
            irr::u16 toSearch = (e.data.Joystick << 8) + i;
            auto finded = std::find(keysPressed.begin(), keysPressed.end(), toSearch);
            if (e.data.IsButtonPressed(i) && finded == keysPressed.end()) {
                keysPressed.push_back((e.data.Joystick << 8) + i);
            } else if (!e.data.IsButtonPressed(i) && finded != keysPressed.end()) {
                keysPressed.erase(finded);
                down(e.data.Joystick, i);
                return;
            }
        }
        for (unsigned short i = 0; i < e.data.NUMBER_OF_AXES; i++) {
            irr::u16 toSearch = (e.data.Joystick << 8) + i;
            auto finded = std::find(joysticksActivated.begin(), joysticksActivated.end(), toSearch);
            if ((e.data.Axis[i] >= 30000 || e.data.Axis[i] <= -30000) && finded == joysticksActivated.end()) {
                joysticksActivated.push_back(toSearch);
                return;
            } else if ((e.data.Axis[i] <= 20000 && e.data.Axis[i] >= -20000) && finded != joysticksActivated.end()) {
                joysticksActivated.erase(finded);
                controller.addAxis<JoystickAxis>("zAxis", {e.data.Joystick, i, true});
                left();
            }
        }
    });
    listeners.push_back(eventId);
}

void indie::scenes::ControllerConfigScene::down(irr::EKEY_CODE firstKeyCode)
{
    ECSWrapper ecs;
    step = DOWN;

    setInfoText("Waiting for pressing down keyboard key");
    auto eventId = ecs.eventManager.addListener<void, events::IrrlichtKeyInputEvent>(nullptr, [firstKeyCode](void *a, events::IrrlichtKeyInputEvent e){
        if (step != DOWN)
            return;
        if (!e.wasReleased)
            return;
        controller.addAxis<KeyAxis>("zAxis", {firstKeyCode, e.keyCode});
        left();
    });
    listeners.push_back(eventId);
}

void indie::scenes::ControllerConfigScene::down(irr::u8 id, irr::u8 keyCode)
{
    ECSWrapper ecs;
    step = DOWN;

    setInfoText("Waiting for pressing down controller key");
    auto eventId = ecs.eventManager.addListener<void, events::IrrlichtJoystickEvent>(nullptr, [id, keyCode](void *a, events::IrrlichtJoystickEvent e){
        if (step != DOWN)
            return;
        if (e.data.Joystick != id)
            return;
        for (unsigned char i = 0; i < e.data.NUMBER_OF_BUTTONS; i++) {
            irr::u16 toSearch = (e.data.Joystick << 8) + i;
            auto finded = std::find(keysPressed.begin(), keysPressed.end(), toSearch);
            if (e.data.IsButtonPressed(i) && finded == keysPressed.end()) {
                keysPressed.push_back((e.data.Joystick << 8) + i);
            } else if (!e.data.IsButtonPressed(i) && finded != keysPressed.end()) {
                keysPressed.erase(finded);
                controller.addAxis<ControllerKeyAxis>("zAxis", {id, keyCode, i});
                left();
                return;
            }
        }
    });
    listeners.push_back(eventId);
}


void indie::scenes::ControllerConfigScene::left()
{
    ECSWrapper ecs;
    step = LEFT;

    setInfoText("Waiting for pressing left key or moving left/right axis");
    auto eventId = ecs.eventManager.addListener<void, events::IrrlichtKeyInputEvent>(nullptr, [&](void *a, events::IrrlichtKeyInputEvent e){
        if (step != LEFT)
            return;
        if (e.wasReleased)
            right(e.keyCode);
    });
    listeners.push_back(eventId);
    eventId = ecs.eventManager.addListener<void, events::IrrlichtJoystickEvent>(nullptr, [](void *a, events::IrrlichtJoystickEvent e){
        if (step != LEFT)
            return;
        for (int i = 0; i < e.data.NUMBER_OF_BUTTONS; i++) {
            irr::u16 toSearch = (e.data.Joystick << 8) + i;
            auto finded = std::find(keysPressed.begin(), keysPressed.end(), toSearch);
            if (e.data.IsButtonPressed(i) && finded == keysPressed.end()) {
                keysPressed.push_back((e.data.Joystick << 8) + i);
            } else if (!e.data.IsButtonPressed(i) && finded != keysPressed.end()) {
                keysPressed.erase(finded);
                right(e.data.Joystick, i);
                return;
            }
        }
        for (unsigned short i = 0; i < e.data.NUMBER_OF_AXES; i++) {
            irr::u16 toSearch = (e.data.Joystick << 8) + i;
            auto finded = std::find(joysticksActivated.begin(), joysticksActivated.end(), toSearch);
            if ((e.data.Axis[i] >= 30000 || e.data.Axis[i] <= -30000) && finded == joysticksActivated.end()) {
                joysticksActivated.push_back(toSearch);
                return;
            } else if ((e.data.Axis[i] <= 20000 && e.data.Axis[i] >= -20000) && finded != joysticksActivated.end()) {
                joysticksActivated.erase(finded);
                controller.addAxis<JoystickAxis>("xAxis", {e.data.Joystick, i});
                taunt();
            }
        }
    });
    listeners.push_back(eventId);
}

void indie::scenes::ControllerConfigScene::right(irr::EKEY_CODE firstKeyCode)
{
    ECSWrapper ecs;
    step = RIGHT;

    setInfoText("Waiting for pressing right keyboard key");
    auto eventId = ecs.eventManager.addListener<void, events::IrrlichtKeyInputEvent>(nullptr, [firstKeyCode](void *a, events::IrrlichtKeyInputEvent e){
        if (step != RIGHT)
            return;
        if (!e.wasReleased)
            return;
        controller.addAxis<KeyAxis>("xAxis", {e.keyCode, firstKeyCode});
        taunt();
    });
    listeners.push_back(eventId);
}

void indie::scenes::ControllerConfigScene::right(irr::u8 id, irr::u8 keyCode)
{
    ECSWrapper ecs;
    step = RIGHT;

    setInfoText("Waiting for pressing right controller key");
    auto eventId = ecs.eventManager.addListener<void, events::IrrlichtJoystickEvent>(nullptr, [id, keyCode](void *a, events::IrrlichtJoystickEvent e){
        if (step != RIGHT)
            return;
        if (e.data.Joystick != id)
            return;
        for (unsigned char i = 0; i < e.data.NUMBER_OF_BUTTONS; i++) {
            irr::u16 toSearch = (e.data.Joystick << 8) + i;
            auto finded = std::find(keysPressed.begin(), keysPressed.end(), toSearch);
            if (e.data.IsButtonPressed(i) && finded == keysPressed.end()) {
                keysPressed.push_back((e.data.Joystick << 8) + i);
            } else if (!e.data.IsButtonPressed(i) && finded != keysPressed.end()) {
                keysPressed.erase(finded);
                controller.addAxis<ControllerKeyAxis>("xAxis", {id, i, keyCode});
                taunt();
                return;
            }
        }
    });
    listeners.push_back(eventId);
}

void indie::scenes::ControllerConfigScene::taunt()
{
    ECSWrapper ecs;
    step = TAUNT;

    setInfoText("Waiting for pressing taunt key");
    auto eventId = ecs.eventManager.addListener<void, events::IrrlichtKeyInputEvent>(nullptr, [&](void *a, events::IrrlichtKeyInputEvent e){
        if (step != TAUNT)
            return;
        if (!e.wasReleased)
            return;
        controller.addKey("taunt", e.keyCode);
        bomb();
    });
    listeners.push_back(eventId);
    eventId = ecs.eventManager.addListener<void, events::IrrlichtJoystickEvent>(nullptr, [](void *a, events::IrrlichtJoystickEvent e){
        if (step != TAUNT)
            return;
        for (int i = 0; i < e.data.NUMBER_OF_BUTTONS; i++) {
            irr::u16 toSearch = (e.data.Joystick << 8) + i;
            auto finded = std::find(keysPressed.begin(), keysPressed.end(), toSearch);
            if (e.data.IsButtonPressed(i) && finded == keysPressed.end()) {
                keysPressed.push_back((e.data.Joystick << 8) + i);
            } else if (!e.data.IsButtonPressed(i) && finded != keysPressed.end()) {
                keysPressed.erase(finded);
                controller.addKey("taunt", e.data.Joystick, i);
                bomb();
                return;
            }
        }
    });
    listeners.push_back(eventId);
}

void indie::scenes::ControllerConfigScene::bomb()
{
    ECSWrapper ecs;
    step = BOMB;

    setInfoText("Waiting for pressing bomb key");
    auto eventId = ecs.eventManager.addListener<void, events::IrrlichtKeyInputEvent>(nullptr, [&](void *a, events::IrrlichtKeyInputEvent e){
        if (step != BOMB)
            return;
        if (!e.wasReleased)
            return;
        controller.addKey("bomb", e.keyCode);
        end();
    });
    listeners.push_back(eventId);
    eventId = ecs.eventManager.addListener<void, events::IrrlichtJoystickEvent>(nullptr, [](void *a, events::IrrlichtJoystickEvent e){
        if (step != BOMB)
            return;
        for (int i = 0; i < e.data.NUMBER_OF_BUTTONS; i++) {
            irr::u16 toSearch = (e.data.Joystick << 8) + i;
            auto finded = std::find(keysPressed.begin(), keysPressed.end(), toSearch);
            if (e.data.IsButtonPressed(i) && finded == keysPressed.end()) {
                keysPressed.push_back((e.data.Joystick << 8) + i);
            } else if (!e.data.IsButtonPressed(i) && finded != keysPressed.end()) {
                keysPressed.erase(finded);
                controller.addKey("bomb", e.data.Joystick, i);
                end();
                return;
            }
        }
    });
    listeners.push_back(eventId);
}

void indie::scenes::ControllerConfigScene::end()
{
    step = END;
    removeListeners();
    SceneManager::safeChangeScene("playerConfig");
}

void indie::scenes::ControllerConfigScene::removeListeners()
{
    ECSWrapper ecs;

    for (auto listener : listeners) {
        ecs.eventManager.removeListener(listener);
    }
}

void indie::scenes::ControllerConfigScene::setInfoText(const std::string &text)
{
    ECSWrapper ecs;

    ecs.entityManager.getEntityByName("infoText")->getComponent<components::Text>()->setText(text);
}

indie::scenes::SaveState indie::scenes::ControllerConfigScene::save(bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}

indie::scenes::SaveState indie::scenes::ControllerConfigScene::save(const std::string &saveName, bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}
