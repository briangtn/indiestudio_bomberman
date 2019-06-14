/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** AStar.cpp
*/

/* Created the 11/06/2019 at 16:15 by jfrabel */

#include <functional>
#include <algorithm>
#include <limits.h>
#include <list>
#include "ai/AStar.hpp"

unsigned int indie::ai::AStar::Node::fCost() const
{
    return gCost + hCost;
}

bool indie::ai::AStar::Node::operator<(const indie::ai::AStar::Node &rhs) const
{
    if (fCost() == rhs.fCost())
        return hCost < rhs.hCost;
    return fCost() < rhs.fCost();
}

bool indie::ai::AStar::Node::operator>(const indie::ai::AStar::Node &rhs) const
{
    return rhs < *this;
}

bool indie::ai::AStar::Node::operator<=(const indie::ai::AStar::Node &rhs) const
{
    return !(rhs < *this);
}

bool indie::ai::AStar::Node::operator>=(const indie::ai::AStar::Node &rhs) const
{
    return !(*this < rhs);
}

bool indie::ai::AStar::Node::operator==(const indie::ai::AStar::Node &rhs) const
{
    return pos.x == rhs.pos.x &&
           pos.y == rhs.pos.y &&
           gCost == rhs.gCost &&
           hCost == rhs.hCost &&
           isStart == rhs.isStart &&
           isEnd == rhs.isEnd &&
           walkable == rhs.walkable &&
           parent == rhs.parent;
}

bool indie::ai::AStar::Node::operator!=(const indie::ai::AStar::Node &rhs) const
{
    return !(rhs == *this);
}

indie::maths::Vector3D indie::ai::AStar::Node::toWorldPos() const
{
    return indie::maths::Vector3D(pos.x * 10.0f, 0, -pos.y * 10.0f);
}

bool indie::ai::AStar::Node::hasCrate() const
{
    return walkCost == 2u;
}

indie::ai::AStar::NodeGrid indie::ai::AStar::computeNodeGrid(const indie::ai::AIView::AICellViewGrid &viewGrid, bool ignoreBreakableWalls)
{
    NodeGrid grid;
    grid.resize(viewGrid.size());
    for (int i = 0; i < viewGrid.size(); ++i) {
        grid[i].resize(viewGrid[i].size());
        for (int j = 0; j < viewGrid[i].size(); ++j) {
            grid[i][j] = Node({
                {j, i},
                UINT_MAX,
                UINT_MAX,
                false,
                false,
                !((viewGrid[i][j] & AIView::AI_CELL_COLLIDE) && (!(viewGrid[i][j] & AIView::AI_CELL_TYPE_BREAKABLE_WALL) || !ignoreBreakableWalls)),
                nullptr,
                viewGrid[i][j] & AIView::AI_CELL_TYPE_BREAKABLE_WALL ? 2u : 1u
            });
        }
    }
    return grid;
}

std::stack<indie::ai::AStar::Node> indie::ai::AStar::findPath(
    const indie::ai::AIView::AICellViewGrid &viewGrid,
    const indie::ai::AStar::Node::position &start,
    const indie::ai::AStar::Node::position &end,
    bool ignoreBreakableWalls)
{
    auto grid = computeNodeGrid(viewGrid, ignoreBreakableWalls);
    return findPath(grid, start, end);
}


std::stack<indie::ai::AStar::Node>
indie::ai::AStar::findPath(
    indie::ai::AStar::NodeGrid &grid,
    const indie::ai::AStar::Node::position &start,
    const indie::ai::AStar::Node::position &end)
{
    if (start.y < 0 || start.y >= grid.size() || start.x < 0 || start.x >= grid[start.y].size()) {
        std::cerr << "[AStar][Warning]Start position not in grid" << std::endl;
        return std::stack<indie::ai::AStar::Node>();
    }
    if (end.y < 0 || end.y >= grid.size() || end.x < 0 || end.x >= grid[start.y].size()) {
        std::cerr << "[AStar][Warning]End position not in grid" << std::endl;
        return std::stack<indie::ai::AStar::Node>();
    }
    Node &startNode = grid[start.y][start.x];
    Node &endNode = grid[end.y][end.x];
    Node *currentNode = &startNode;
    std::list<Node *> _openSet;
    std::list<Node *> _closeSet;

    startNode.isStart = true;
    startNode.gCost = 0;
    endNode.isEnd = true;
    _openSet.push_front(&startNode);
    while (!_openSet.empty()) {
        _openSet.sort([](const Node *nodeA, const Node *nodeB) {
            return *nodeA < *nodeB;
        });
        currentNode = _openSet.front();
        _openSet.remove(currentNode);
        _closeSet.push_front(currentNode);

        if (currentNode->isEnd) {
            return traceBackPath(endNode);
        }

        for (auto &neighbour : getNeighbours(grid, *currentNode)) {
            if (!neighbour.get().walkable || std::find(_closeSet.begin(), _closeSet.end(), &neighbour.get()) != _closeSet.end())
                continue;
            int movementCostFromStart = currentNode->gCost + getDistance(*currentNode, neighbour.get());
            if (movementCostFromStart < neighbour.get().gCost || std::find(_openSet.begin(), _openSet.end(), &neighbour.get()) == _openSet.end()) {
                neighbour.get().gCost = movementCostFromStart;
                neighbour.get().hCost = getDistance(neighbour.get(), endNode);
                neighbour.get().parent = currentNode;
                if (std::find(_openSet.begin(), _openSet.end(), &neighbour.get()) == _openSet.end()) {
                    _openSet.push_front(&neighbour.get());
                }
            }
        }
    }
    return std::stack<indie::ai::AStar::Node>();
}

std::list<std::reference_wrapper<indie::ai::AStar::Node>> indie::ai::AStar::getNeighbours(NodeGrid &grid, Node &node)
{
    std::list<std::reference_wrapper<indie::ai::AStar::Node>> neighbours;
    auto pos = node.pos;
    if (pos.y - 1 >= 0) {
        neighbours.push_front(grid[pos.y - 1][pos.x]);
    }
    if (pos.y + 1 < grid.size()) {
        neighbours.push_front(grid[pos.y + 1][pos.x]);
    }
    if (pos.x - 1 >= 0) {
        neighbours.push_front(grid[pos.y][pos.x - 1]);
    }
    if (pos.x + 1 < grid[pos.y].size()) {
        neighbours.push_front(grid[pos.y][pos.x + 1]);
    }
    return neighbours;
}

int indie::ai::AStar::getDistance(const indie::ai::AStar::Node &nodeA, const indie::ai::AStar::Node &nodeB)
{
    return nodeA.walkCost * nodeB.walkCost * std::abs(nodeA.pos.x - nodeB.pos.x) + nodeA.walkCost * nodeB.walkCost * std::abs(nodeA.pos.y - nodeB.pos.y);
}

std::stack<indie::ai::AStar::Node> indie::ai::AStar::traceBackPath(indie::ai::AStar::Node &endNode)
{
    std::stack<Node> path;
    Node &currentNode = endNode;
    while (currentNode.parent) {
        path.push(currentNode);
        currentNode = *currentNode.parent;
    }
    return path;
}

indie::ai::AStar::Node::position indie::ai::get2DPositionFromWorldPos(const indie::maths::Vector3D &worldPos)
{
    return {static_cast<int>(std::round(worldPos.x / 10.0f)), -static_cast<int>(std::round(worldPos.z / 10.0f))};
}
