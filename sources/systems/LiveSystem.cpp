/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** LiveSystem.cpp
*/

/* Created the 13/06/2019 at 10:07 by jfrabel */

#include "systems/LiveSystem.hpp"
#include "ECSWrapper.hpp"
#include "components/PlayerAlive.hpp"
#include "components/PlayerController.hpp"
#include "components/AIController.hpp"
#include "components/LeaderBoard.hpp"

indie::systems::LiveSystem::LiveSystem()
    : _elapsedTime(0)
{

}

indie::systems::LiveSystem::~LiveSystem()
{

}

void indie::systems::LiveSystem::onAwake()
{

}

void indie::systems::LiveSystem::onStart()
{

}

void indie::systems::LiveSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    float elapsedTimeAsSeconds = elapsedTime.count() / 1000000000.0f;
    _elapsedTime += elapsedTimeAsSeconds;
    if (_elapsedTime >= updateDelta) {
        ECSWrapper ecs;
        auto entityWithLives = ecs.entityManager.getEntitiesWith<indie::components::PlayerAlive>();
        for (auto &entity : entityWithLives) {
            auto playerAliveComponent = entity->getComponent<components::PlayerAlive>();
            if (playerAliveComponent->getLives() <= 0 && !playerAliveComponent->isMarkedAsDead()) {
                entity->removeComponent<components::PlayerController>();
                entity->removeComponent<components::AIController>();
                entity->removeComponent<components::MoveToTarget>();
                entity->removeComponent<components::BoxCollider>();
                auto animator = entity->getComponent<components::Animator>();
                animator->setCurrentAnimation("die");
                playerAliveComponent->setMarkedAsDead(true);

                int playerNumber = std::atoi(entity->getName().substr(6).c_str());

                auto leaderBoardEntity = ecs.entityManager.getEntityByName("leaderBoard");
                if (leaderBoardEntity.isValid()) {
                    auto leaderBoardComponent = leaderBoardEntity->getComponent<components::LeaderBoard>();
                    if (leaderBoardComponent.isValid()) {
                        leaderBoardComponent->addPlayerToLeaderBoard(leaderBoardComponent->getPlayerLeaderboard().size() + 1, playerNumber);
                    } else
                        std::cerr << "[ERROR][LiveSystem] startNewGame was not called!" << std::endl;
                } else
                    std::cerr << "[ERROR][LiveSystem] startNewGame was not called!" << std::endl;
            }
        }
        _elapsedTime -= updateDelta;
    }
}

void indie::systems::LiveSystem::onStop()
{

}

void indie::systems::LiveSystem::onTearDown()
{

}

void indie::systems::LiveSystem::startNewGame()
{
    ECSWrapper ecs;
    auto entity = ecs.entityManager.createEntity("leaderBoard");
    entity->assignComponent<components::LeaderBoard>();
}

indie::components::LeaderBoard::PlayerLeaderBoard indie::systems::LiveSystem::endGame()
{
    ECSWrapper ecs;
    components::LeaderBoard::PlayerLeaderBoard values;
    auto leaderBoardEntity = ecs.entityManager.getEntityByName("leaderBoard");
    if (leaderBoardEntity.isValid()) {
        auto leaderBoardComponent = leaderBoardEntity->getComponent<components::LeaderBoard>();
        if (leaderBoardComponent.isValid()) {
            values = leaderBoardComponent->getPlayerLeaderboard();
            int nbPlayers = values.size();
            for (auto &value : values) {
                value.first = nbPlayers - value.first + 1;
            }
            return values;
        }
    }
    std::cerr << "[ERROR][LiveSystem] startNewGame was not called!" << std::endl;
    return values;
}
