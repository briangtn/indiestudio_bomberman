/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** InvalidXmlScene.cpp
*/

/* Created the 16/06/2019 at 18:48 by jfrabel */

#include "scenes/SceneManager.hpp"
#include "components/GUI/Button.hpp"
#include "components/GUI/Image.hpp"
#include "components/Transform.hpp"
#include "components/GUI/Text.hpp"
#include "components/GUI/Font.hpp"
#include "ECSWrapper.hpp"
#include "scenes/InvalidXmlScene.hpp"

void indie::scenes::InvalidXmlScene::onStart()
{
    ECSWrapper ecs;

    auto backgroundEntity = ecs.entityManager.createEntity("background");
    backgroundEntity->assignComponent<indie::components::Image>("default_menu_background");
    auto backgroundTransform = backgroundEntity->assignComponent<indie::components::Transform>();
    backgroundTransform->setPosition({0, 0, -1});

    auto textEntity = ecs.entityManager.createEntity("infoText");
    auto textComponent = textEntity->assignComponent<indie::components::Text>("Invalid XML data");
    auto transform = textEntity->assignComponent<indie::components::Transform>();
    transform->setScale({1280, 720, 0});
    textComponent->setColor(irr::video::SColor(255, 255, 0, 0));
    textComponent->setVerticalAlignement(components::Text::MIDDLE);
    textComponent->setHorizontalAlignement(components::Text::CENTER);
    textEntity->assignComponent<indie::components::Font>("default_font");

    auto backToMenuButton = ecs.entityManager.createEntity("backToMenuButton");
    auto backToMenuButtonComponent = backToMenuButton->assignComponent<indie::components::Button>("", 99, "button_back_to_menu");
    auto backToMenuButtonTransform = backToMenuButton->assignComponent<indie::components::Transform>();
    backToMenuButtonTransform->setPosition({0, 645, 0});
    backToMenuButtonTransform->setScale({367,75,0});

    backToMenuButton->getComponent<indie::components::Button>()->setOnClicked([](indie::components::Button *button) {
        indie::scenes::SceneManager::safeChangeScene("mainMenu");
    });
    backToMenuButtonComponent->setOnHovered([](indie::components::Button *button, bool isHovered) {
        if (isHovered) {
            button->setTexturePath("button_back_to_menu_hovered");
        } else {
            button->setTexturePath("button_back_to_menu");
        }
    });
}

void indie::scenes::InvalidXmlScene::onStop()
{

}

indie::scenes::SaveState indie::scenes::InvalidXmlScene::save(bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}

indie::scenes::SaveState
indie::scenes::InvalidXmlScene::save(const std::string &saveName, bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}
