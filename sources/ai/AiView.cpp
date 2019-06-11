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

indie::ai::AIView::AICellViewGrid indie::ai::AIView::_viewGrid;

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
    ECSWrapper ecs;
    auto players = ecs.entityManager.getEntitiesWith<indie::components::PlayerController, indie::components::Transform>();
    for (auto &player : players) {
        auto tr = player->getComponent<components::Transform>();
        int x = static_cast<int>(tr->getPosition().x / 10.0f);
        int z = static_cast<int>(tr->getPosition().z / 10.0f);
        if (x >= 0 && x < width && z >= 0 && z < height) {
            _viewGrid[z][x] = AI_CELL_TYPE_PLAYER;
        }
    }
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
    //todo power ups
}
