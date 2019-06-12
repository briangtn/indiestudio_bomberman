/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** AStar.hpp
*/

/* Created the 11/06/2019 at 16:15 by jfrabel */

#ifndef INDIESTUDIO_ASTAR_HPP
#define INDIESTUDIO_ASTAR_HPP

#include <stack>
#include <list>
#include "maths/Vectors.hpp"
#include "AiView.hpp"

namespace indie {

    namespace ai {

        class AStar {
        public:
            struct Node {
                struct position {
                    int x;
                    int y;
                } pos;
                unsigned int gCost;
                unsigned int hCost;
                unsigned int fCost() const;
                bool isStart;
                bool isEnd;
                bool walkable;
                Node *parent;

                bool operator<(const Node &rhs) const;
                bool operator>(const Node &rhs) const;
                bool operator<=(const Node &rhs) const;
                bool operator>=(const Node &rhs) const;
                bool operator==(const Node &rhs) const;
                bool operator!=(const Node &rhs) const;

                maths::Vector3D toWorldPos() const;
            };

        struct NodeCompare : public std::unary_function<Node, bool> {
            explicit NodeCompare(const Node &cmp) : compared(cmp) {}
            bool operator()(const Node &arg) {
                return arg == compared;
            }
            const Node &compared;
        };

            using NodeGrid = std::vector<std::vector<Node>>;

        public:
            static NodeGrid computeNodeGrid(const AIView::AICellViewGrid &viewGrid, bool ignoreBreakableWalls = false);
            static std::stack<Node> findPath(const AIView::AICellViewGrid &viewGrid, const Node::position &start, const Node::position &end, bool ignoreBreakableWalls = false);
            static std::stack<Node> findPath(NodeGrid &grid, const Node::position &start, const Node::position &end);

        private:
            static std::list<std::reference_wrapper<Node>> getNeighbours(NodeGrid &grid, Node &node);
            static int getDistance(const Node &nodeA, const Node &nodeB);
            static std::stack<Node> traceBackPath(Node &endNode);
        };
    }
}

#endif //INDIESTUDIO_ASTAR_HPP
