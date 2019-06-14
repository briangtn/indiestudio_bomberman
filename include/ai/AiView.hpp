/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** AiView.hpp
*/

/* Created the 11/06/2019 at 11:51 by jfrabel */

#ifndef INDIESTUDIO_AIVIEW_HPP
#define INDIESTUDIO_AIVIEW_HPP

#include <vector>
#include <stdint.h>

namespace indie {

    namespace ai {

        class AIView {
        public:
            enum AICellType : uint16_t {
                AI_CELL_TYPE_AIR                = 0b0000000000,
                AI_CELL_TYPE_UNBREAKABLE_WALL   = 0b0000000001,
                AI_CELL_TYPE_BREAKABLE_WALL     = 0b0000000010,
                AI_CELL_TYPE_PLAYER             = 0b0000000100,
                AI_CELL_TYPE_BOMB               = 0b0000001000,
                AI_CELL_TYPE_POWER_UP_FIRE_UP   = 0b0000010000,
                AI_CELL_TYPE_POWER_UP_BOMB_UP   = 0b0000100000,
                AI_CELL_TYPE_POWER_UP_SPEED_UP  = 0b0001000000,
                AI_CELL_TYPE_POWER_UP_WALL_PASS = 0b0010000000,
                AI_CELL_BLAST                   = 0b0100000000,
                AI_CELL_TYPE_UNKNOWN            = 0b1000000000,
                AI_CELL_COLLIDE                 = AI_CELL_TYPE_UNBREAKABLE_WALL | AI_CELL_TYPE_BREAKABLE_WALL | AI_CELL_TYPE_BOMB,
            };

            using AICellViewGrid = std::vector<std::vector<unsigned int>>;
            using AICellCollisionGrid = std::vector<std::vector<bool>>;

        public:
            static const AICellCollisionGrid &getCollisionGrid();
            static const AICellViewGrid &getViewGrid();
            static void recomputeViewGrid(int width, int height);

        private:
            static void recomputePlayers(int width, int height);
            static void recomputeUnbreakableWalls(int width, int height);
            static void recomputeBreakableWalls(int width, int height);
            static void recomputeBombs(int width, int height);
            static void recomputePowerUps(int width, int height);

        private:
            static AICellViewGrid _viewGrid;
            static AICellCollisionGrid _collisionGrid;
        };
    }
}


#endif //INDIESTUDIO_AIVIEW_HPP
