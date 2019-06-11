/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** AiView.cpp
*/

/* Created the 11/06/2019 at 11:51 by jfrabel */

#include "ai/AiView.hpp"
#include "ECSWrapper.hpp"
#include "components/PlayerController.hpp"
#include "components/Transform.hpp"
#include "components/BonusEffector.hpp"

indie::ai::AIView::AICellViewGrid indie::ai::AIView::_viewGrid;
indie::ai::AIView::AICellCollisionGrid indie::ai::AIView::_collisionGrid;

const indie::ai::AIView::AICellCollisionGrid &indie::ai::AIView::getCollisionGrid()
{
    return _collisionGrid;
}

const indie::ai::AIView::AICellViewGrid &indie::ai::AIView::getViewGrid()
{
    return _viewGrid;
}

void indie::ai::AIView::recomputeViewGrid(int width, int height)
{
    _viewGrid.clear();
    _viewGrid.resize(height);
    for (int i = 0; i < height; ++i) {
        _viewGrid[i].resize(width, AI_CELL_TYPE_AIR);
    }
    _collisionGrid.clear();
    _collisionGrid.resize(height);
    for (int i = 0; i < height; ++i) {
        _collisionGrid[i].resize(width, false);
    }
    recomputeUnbreakableWalls(width, height);
    recomputeBreakableWalls(width, height);
    recomputePowerUps(width, height);
    recomputeBombs(width, height);
    recomputePlayers(width, height);
    for (int z = 0; z < height; ++z) {
        for (int x = 0; x < width; ++x) {
            _collisionGrid[z][x] = (_viewGrid[z][x] & 0b1);
        }
    }
}

void indie::ai::AIView::recomputePlayers(int width, int height)
{
    ECSWrapper ecs;
    auto players = ecs.entityManager.getEntitiesWith<indie::components::PlayerController, indie::components::Transform>();
    for (auto &player : players) {
        auto tr = player->getComponent<components::Transform>();
        int x = static_cast<int>(tr->getPosition().x / 10.0f);
        int z = -static_cast<int>(tr->getPosition().z / 10.0f);
        std::cout << "Found player at " << x << " " << z << std::endl;
        if (x >= 0 && x < width && z >= 0 && z < height) {
            _viewGrid[z][x] = AI_CELL_TYPE_PLAYER;
        }
    }
}

void indie::ai::AIView::recomputeUnbreakableWalls(int width, int height)
{
    ECSWrapper ecs;
    auto unbreakableWalls = ecs.entityManager.getEntitiesByName("unbreakable wall");
    for (auto &wall : unbreakableWalls) {
        auto tr = wall->getComponent<components::Transform>();
        if (!tr.isValid())
            continue;
        int x = static_cast<int>(tr->getPosition().x / 10.0f);
        int z = -static_cast<int>(tr->getPosition().z / 10.0f);
        if (x >= 0 && x < width && z >= 0 && z < height) {
            _viewGrid[z][x] = AI_CELL_TYPE_UNBREAKABLE_WALL;
        }
    }
}

void indie::ai::AIView::recomputeBreakableWalls(int width, int height)
{
    ECSWrapper ecs;
    auto breakableWalls = ecs.entityManager.getEntitiesByName("breakable wall");
    for (auto &wall : breakableWalls) {
        auto tr = wall->getComponent<components::Transform>();
        if (!tr.isValid())
            continue;
        int x = static_cast<int>(tr->getPosition().x / 10.0f);
        int z = -static_cast<int>(tr->getPosition().z / 10.0f);
        if (x >= 0 && x < width && z >= 0 && z < height) {
            _viewGrid[z][x] = AI_CELL_TYPE_BREAKABLE_WALL;
        }
    }
}

void indie::ai::AIView::recomputeBombs(int width, int height)
{
    ECSWrapper ecs;
    //TODO
}

void indie::ai::AIView::recomputePowerUps(int width, int height)
{
    ECSWrapper ecs;
    auto powerUps = ecs.entityManager.getEntitiesWith<components::BonusEffector, components::Transform>();
    for (auto &powerUp : powerUps) {
        auto effector = powerUp->getComponent<components::BonusEffector>();
        auto tr = powerUp->getComponent<components::Transform>();
        int x = static_cast<int>(tr->getPosition().x / 10.0f);
        int z = -static_cast<int>(tr->getPosition().z / 10.0f);
        if (x >= 0 && x < width && z >= 0 && z < height) {
            switch (effector->getType()) {
            case components::BONUS_T_BOMB_UP: _viewGrid[z][x] = AI_CELL_TYPE_POWER_UP_BOMB_UP;
                break;
            case components::BONUS_T_SPEED_UP: _viewGrid[z][x] = AI_CELL_TYPE_POWER_UP_SPEED_UP;
                break;
            case components::BONUS_T_FIRE_UP: _viewGrid[z][x] = AI_CELL_TYPE_POWER_UP_FIRE_UP;
                break;
            case components::BONUS_T_WALL_PASS: _viewGrid[z][x] = AI_CELL_TYPE_POWER_UP_WALL_PASS;
                break;
            default: _viewGrid[z][x] = AI_CELL_TYPE_UNKNOWN;
                break;
            }
        }
    }
}