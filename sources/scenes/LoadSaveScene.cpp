/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** LoadSaveScene.cpp
*/

/* Created the 15/06/2019 at 00:26 by brian */

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "scenes/LoadSaveScene.hpp"
#include "components/GUI/Image.hpp"
#include "ECSWrapper.hpp"
#include "components/Transform.hpp"
#include "components/GUI/Button.hpp"
#include "scenes/PlayerConfigScene.hpp"

int indie::scenes::LoadSaveScene::page = 0;

void indie::scenes::LoadSaveScene::onStart()
{
    ECSWrapper ecs;
    std::vector<std::string> saves;

    auto backgroundEntity = ecs.entityManager.createEntity("background");
    backgroundEntity->assignComponent<indie::components::Image>("default_menu_background");
    auto backgroundTransform = backgroundEntity->assignComponent<indie::components::Transform>();
    backgroundTransform->setPosition({0, 0, -1});

    boost::filesystem::path dir("resources/saves");
    boost::filesystem::recursive_directory_iterator end;

    for (boost::filesystem::recursive_directory_iterator elem(dir); elem != end; ++elem) {
        boost::filesystem::path file = elem->path();
        std::string name = file.string();

        while (name.find("/") != std::string::npos) {
            name = name.substr(name.find("/") + 1);
        }
        saves.push_back(name);
    }
    page = 0;

    createButtons(page, saves);

    auto leftPageEntity = ecs.entityManager.createEntity("leftPageButton");
    auto leftPageButton = leftPageEntity->assignComponent<components::Button>("<", 1);
    auto leftPageTransform = leftPageEntity->assignComponent<components::Transform>();
    leftPageTransform->setScale({50, 50, 0});
    leftPageTransform->setPosition({1130, 620, 0});

    leftPageButton->setOnClicked([saves](components::Button *btn){
        if (page <= 0)
            return;
        destroyButtons();
        page--;
        createButtons(page, saves);
    });

    auto rightPageEntity = ecs.entityManager.createEntity("rightPageButton");
    auto rightPageButton = rightPageEntity->assignComponent<components::Button>(">", 2);
    auto rightPageTransform = rightPageEntity->assignComponent<components::Transform>();
    rightPageTransform->setScale({50, 50, 0});
    rightPageTransform->setPosition({1190, 620, 0});

    rightPageButton->setOnClicked([saves](components::Button *btn){
        if ((page + 1)* 10 > saves.size())
            return;
        destroyButtons();
        page++;
        createButtons(page, saves);
    });
}

void indie::scenes::LoadSaveScene::createButtons(unsigned int page, std::vector<std::string> saves)
{
    ECSWrapper ecs;

    for (int i = page * 10; i < (page * 10) + 10 && i < saves.size(); i++) {
        auto buttonEntity = ecs.entityManager.createEntity("button" + std::to_string(i % 10));
        auto buttonComponent = buttonEntity->assignComponent<components::Button>(saves[i], 100 + (i % 10));
        auto transformComponent = buttonEntity->assignComponent<components::Transform>();
        transformComponent->setScale({1200, 50, 0});
        transformComponent->setPosition({40, 10.0f + ((i % 10) * 60.0f), 0});

        std::string name = saves[i];
        buttonComponent->setOnClicked([name](components::Button *btn) {
            indie::scenes::PlayerConfigScene::Load(name.substr(0, name.find(".")), true);
        });
    }
}

void indie::scenes::LoadSaveScene::destroyButtons()
{
    ECSWrapper ecs;

    for (int i = 0; i < 10; i++) {
        auto buttonEntity = ecs.entityManager.getEntityByName("button" + std::to_string(i));
        if (!buttonEntity.isValid())
            return;
        ecs.entityManager.safeDeleteEntity(buttonEntity->getID());
    }
}

void indie::scenes::LoadSaveScene::onStop()
{

}

indie::scenes::SaveState indie::scenes::LoadSaveScene::save(bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}

indie::scenes::SaveState
indie::scenes::LoadSaveScene::save(const std::string &saveName, bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}
