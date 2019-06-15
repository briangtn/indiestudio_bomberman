/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** ResourcesPackScene.cpp
*/

//
// Created by romainfouyer on 6/15/19.
//

#include "components/GUI/Image.hpp"
#include "ECSWrapper.hpp"
#include "scenes/ResourcesPackScene.hpp"
#include "scenes/SceneManager.hpp"
#include "assets_manager/AssetsManager.hpp"
#include "components/Transform.hpp"
#include "components/GUI/Font.hpp"
#include "components/GUI/Button.hpp"

int indie::scenes::ResourcesPacksScene::_page = 0;

void indie::scenes::ResourcesPacksScene::onStart()
{
    ECSWrapper ecs;
    indie::AssetsManager &assetsManager = indie::AssetsManager::getInstance();
    std::vector<std::string> resourcesPacks;

    auto backgroundEntity = ecs.entityManager.createEntity("background");
    backgroundEntity->assignComponent<indie::components::Image>("default_menu_background");
    auto backgroundTransform = backgroundEntity->assignComponent<indie::components::Transform>();
    backgroundTransform->setPosition({0, 0, -1});

    auto backToMenuButton = ecs.entityManager.createEntity("backToMenuButton");
    backToMenuButton->assignComponent<indie::components::Button>("", 99, "button_back");
    auto backToMenuButtonTransform = backToMenuButton->assignComponent<indie::components::Transform>();
    backToMenuButtonTransform->setPosition({10, 640, 0});
    backToMenuButtonTransform->setScale({212,75,0});

    backToMenuButton->getComponent<indie::components::Button>()->setOnClicked([](indie::components::Button *button) {
        indie::scenes::SceneManager::safeChangeScene("settings");
    });

    backToMenuButton->getComponent<indie::components::Button>()->setOnHovered([](indie::components::Button *button, bool isHovered) {
        if (isHovered)
            button->setTexturePath("button_back_hovered");
        else
            button->setTexturePath("button_back");
    });

    assetsManager.fetchResourcesPacks();
    for (auto &it : assetsManager.getResourcesPacks())
        resourcesPacks.push_back(it.first);

    _page = 0;

    createButtons(_page, resourcesPacks);

    auto leftPageEntity = ecs.entityManager.createEntity("leftPageButton");
    auto leftPageButton = leftPageEntity->assignComponent<components::Button>("<", 1);
    auto leftPageTransform = leftPageEntity->assignComponent<components::Transform>();
    auto leftPageFont = leftPageEntity->assignComponent<components::Font>("default_font");

    leftPageFont->setPath("default_font");
    leftPageButton->setTexturePath("button_default");
    leftPageTransform->setScale({50, 50, 0});
    leftPageTransform->setPosition({1130, 620, 0});

    leftPageButton->setOnClicked([resourcesPacks](components::Button *btn){
        if (_page <= 0)
            return;
        destroyButtons();
        _page--;
        createButtons(_page, resourcesPacks);
    });

    auto rightPageEntity = ecs.entityManager.createEntity("rightPageButton");
    auto rightPageButton = rightPageEntity->assignComponent<components::Button>(">", 2);
    auto rightPageTransform = rightPageEntity->assignComponent<components::Transform>();
    auto rightPageFont = rightPageEntity->assignComponent<components::Font>("default_font");

    rightPageFont->setPath("default_font");
    rightPageButton->setTexturePath("button_default");
    rightPageTransform->setScale({50, 50, 0});
    rightPageTransform->setPosition({1190, 620, 0});

    rightPageButton->setOnClicked([resourcesPacks](components::Button *btn){
        if ((_page + 1)* 10 > resourcesPacks.size())
            return;
        destroyButtons();
        _page++;
        createButtons(_page, resourcesPacks);
    });
}

void indie::scenes::ResourcesPacksScene::createButtons(unsigned int page, std::vector<std::string> saves)
{
    ECSWrapper ecs;

    for (int i = page * 10; i < (page * 10) + 10 && i < saves.size(); i++) {
        std::string name = saves[i];
        name[0] = toupper(name[0]);
        auto buttonEntity = ecs.entityManager.createEntity("button" + std::to_string(i % 10));
        auto buttonComponent = buttonEntity->assignComponent<components::Button>(name, 100 + (i % 10));
        auto transformComponent = buttonEntity->assignComponent<components::Transform>();
        auto buttonFont = buttonEntity->assignComponent<components::Font>("default_font");

        buttonFont->setPath("default_font");
        buttonComponent->setTexturePath("button_default");
        transformComponent->setScale({1200, 50, 0});
        transformComponent->setPosition({40, 10.0f + ((i % 10) * 60.0f), 0});

        buttonComponent->setOnClicked([name](components::Button *btn) {
            indie::AssetsManager &assetsManager = indie::AssetsManager::getInstance();

            assetsManager.loadResourcesPack(name);
            indie::scenes::SceneManager::safeChangeScene("resourcesPacksScene");
        });
    }
}

void indie::scenes::ResourcesPacksScene::destroyButtons()
{
    ECSWrapper ecs;

    for (int i = 0; i < 10; i++) {
        auto buttonEntity = ecs.entityManager.getEntityByName("button" + std::to_string(i));
        if (!buttonEntity.isValid())
            return;
        ecs.entityManager.safeDeleteEntity(buttonEntity->getID());
    }
}

void indie::scenes::ResourcesPacksScene::onStop()
{

}

indie::scenes::SaveState indie::scenes::ResourcesPacksScene::save(bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}

indie::scenes::SaveState
indie::scenes::ResourcesPacksScene::save(const std::string &saveName, bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}
