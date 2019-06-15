/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** EndScene.cpp
*/

/* Created the 14/06/2019 at 16:39 by jbulteau */

#include <algorithm>
#include "scenes/EndScene.hpp"
#include "ECSWrapper.hpp"
#include "components/Camera.hpp"
#include "components/GUI/Button.hpp"
#include "components/GUI/Text.hpp"
#include "components/GUI/Font.hpp"
#include "components/GUI/Image.hpp"
#include "scenes/SceneManager.hpp"
#include "systems/LiveSystem.hpp"
#include "components/Mesh.hpp"
#include "components/Rotator.hpp"

void indie::scenes::EndScene::onStart()
{
    ECSWrapper ecs;

    auto particleSystemEntity = ecs.entityManager.createEntity("particleSystem");
    particleSystemEntity->assignComponent<indie::components::Transform, indie::maths::Vector3D>({-10, -15, 5});
    auto sys = particleSystemEntity->assignComponent<indie::components::Particle, std::string>("p1");
    sys->setTexture(0, "default_particle_texture");
    sys->setAngle(0);
    sys->setDarkBrightColor(std::make_pair(irr::video::SColor(0, 145, 145, 0), irr::video::SColor(0, 255, 255, 0)));
    sys->setEmitterSize(irr::core::aabbox3df(-7, 0, -7, 7, 10, 7));
    sys->setEmitRate(std::make_pair(40, 80));
    sys->setFadeColor(irr::video::SColor(0, 0, 0, 0));
    sys->setFadeTime(1000);
    sys->setMinMaxAge(std::make_pair(1600, 3000));
    sys->setMinMaxSize(std::make_pair(irr::core::dimension2d<irr::f32>(0.3, 0.3), irr::core::dimension2d<irr::f32>(0.6, 0.6)));
    sys->setInitialDirection(irr::core::vector3df(0.0f, 0.01f, 0.0f));
    sys->initParticle();

    auto cameraEntity = ecs.entityManager.createEntity("camera");
    cameraEntity->assignComponent<indie::components::Camera>();
    auto cameraTransform = cameraEntity->assignComponent<indie::components::Transform, maths::Vector3D>({0, 0, -20});

    auto soundEntity = ecs.entityManager.createEntity("endSceneMusic");
    auto sound = soundEntity->assignComponent<indie::components::SoundComponent>("music_result", components::SoundComponent::MUSIC);
    sound->setIsLooped(true);
    sound->setIsPaused(false);

    auto backgroundEntity = ecs.entityManager.createEntity("background");
    backgroundEntity->assignComponent<indie::components::Image>("default_menu_background");
    auto backgroundTransform = backgroundEntity->assignComponent<indie::components::Transform>();
    backgroundTransform->setPosition({0, 0, -1});

    std::vector<std::pair<int, int>> results;
    try {
        results = ecs.systemManager.getSystem<systems::LiveSystem>().endGame(); //TODO change the ways players are got
    } catch (jf::SystemNotFoundException &e) {
        std::cerr << "[ERROR][EndScene] LiveSystem does not exist ! Score will not be retrieved." << std::endl;
    }
    int nbPlayers = results.size();
    if (nbPlayers > 10)
        nbPlayers = 10;
    int divisor = nbPlayers + 1;

    std::sort(results.begin(), results.end(), [](auto &a, auto &b) {
        return a.second < b.second;
    });

    auto mainTextEntity = ecs.entityManager.createEntity("text");
    auto textComponent = mainTextEntity->assignComponent<indie::components::Text>("WINNER");
    auto transform = mainTextEntity->assignComponent<indie::components::Transform, maths::Vector3D, maths::Vector3D, maths::Vector3D>(
            {100.0f / 2.0f, -280.0f, 0},
            {0, 0, 0},
            {1280.0f / 2.0f, 720.0f, 0}
    );
    textComponent->setColor(irr::video::SColor(255, 0, 0, 0));
    textComponent->setVerticalAlignement(components::Text::MIDDLE);
    textComponent->setHorizontalAlignement(components::Text::CENTER);
    mainTextEntity->assignComponent<indie::components::Font>("default_font");

    auto winnerEntity = ecs.entityManager.createEntity("Winner");
    winnerEntity->assignComponent<components::Transform, maths::Vector3D, maths::Vector3D, maths::Vector3D>(
            {-10, -9, 5},
            {0, 180, 0},
            {10, 10, 10}
    );
    winnerEntity->assignComponent<components::Mesh, std::string>("player_model");
    auto winnerMaterial = winnerEntity->assignComponent<components::Material, std::string>(getMaterial(getWinner(results)));
    winnerMaterial->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    winnerEntity->assignComponent<components::Rotator, float, float, float>(0, 60, 0);
    winnerEntity->assignComponent<components::Animator, std::map<std::string, components::Animator::Animation>>({
        {"taunt", components::Animator::Animation(123, 145, 40, true, "")}
    });

    for (int i = 0; i < nbPlayers; ++i) {
        int playerRanking = results[i].second;
        int playerNumber = results[i].first;
        auto textEntity = ecs.entityManager.createEntity("Player" + std::to_string(playerNumber) + "Score");
        auto textComponent = textEntity->assignComponent<indie::components::Text>(std::to_string(playerRanking) + "\t:\tPlayer " + std::to_string(playerNumber));
        auto transform = textEntity->assignComponent<indie::components::Transform, maths::Vector3D, maths::Vector3D, maths::Vector3D>(
                {1280.0f / 2.0f, i * (720.0f / divisor), 0},
                {0, 0, 0},
                {1280.0f / 2.0f, 720.0f / divisor, 0}
        );
        textComponent->setColor(irr::video::SColor(255, 0, 0, 0));
        textComponent->setVerticalAlignement(components::Text::MIDDLE);
        textComponent->setHorizontalAlignement(components::Text::CENTER);
        textEntity->assignComponent<indie::components::Font>("default_font");
    }

    constexpr float buttonMargin = 15.0f;

    auto buttonRestartEntity = ecs.entityManager.createEntity("buttonRestart");
    auto buttonRestartComponent = buttonRestartEntity->assignComponent<indie::components::Button>("Restart", 5);
    buttonRestartEntity->assignComponent<indie::components::Font>("default_font");
    auto buttonRestartTransform = buttonRestartEntity->assignComponent<indie::components::Transform>();
    buttonRestartTransform->setPosition({2 * (1280.0f / 4.0f) + buttonMargin, nbPlayers * (720.0f / divisor) + buttonMargin, 100});
    buttonRestartTransform->setScale({1280.0f / 4.0f - buttonMargin * 2, 720.0f / divisor - buttonMargin * 2, 0});

    buttonRestartComponent->setOnClicked([](components::Button *btn){
        indie::scenes::SceneManager::safeChangeScene("newGameScene");
    });

    auto buttonMenuEntity = ecs.entityManager.createEntity("buttonMenu");
    auto buttonMenuComponent = buttonMenuEntity->assignComponent<indie::components::Button>("Menu", 6);
    buttonMenuEntity->assignComponent<indie::components::Font>("default_font");
    auto buttonMenuTransform = buttonMenuEntity->assignComponent<indie::components::Transform>();
    buttonMenuTransform->setPosition({3 * (1280.0f / 4.0f) + buttonMargin, nbPlayers * (720.0f / divisor) + buttonMargin, 100});
    buttonMenuTransform->setScale({1280.0f / 4.0f - buttonMargin * 2, 720.0f / divisor - buttonMargin * 2, 0});

    buttonMenuComponent->setOnClicked([](components::Button *btn){
        indie::scenes::SceneManager::safeChangeScene("mainMenu");
    });
}

void indie::scenes::EndScene::onStop()
{

}

indie::scenes::SaveState indie::scenes::EndScene::save(bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}

indie::scenes::SaveState indie::scenes::EndScene::save(const std::string &saveName, bool override, bool saveShouldBeKeeped)
{
    return SUCCESS;
}

int indie::scenes::EndScene::getWinner(std::vector<std::pair<int, int>> &results) const
{
    for (auto &it : results) {
        if (it.second == 1) {
            return it.first;
        }
    }
    return 0;
}

const std::string &indie::scenes::EndScene::getMaterial(int winnerId) const
{
    static const std::map<int, std::string> materialPath = {
            {1, "player_texture_black"},
            {2, "player_texture_blue"},
            {3, "player_texture_white"},
            {4, "player_texture_yellow"}
    };
    return materialPath.at(winnerId);
}
