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

namespace indie {

    namespace ai {

        class AIView {
        public:
            enum AICellType {
                AI_CELL_TYPE_AIR,
                AI_CELL_TYPE_UNBREAKABLE_WALL,
                AI_CELL_TYPE_BREAKABLE_WALL,
                AI_CELL_TYPE_PLAYER,
                AI_CELL_TYPE_POWER_UP_FIRE_UP,
                AI_CELL_TYPE_POWER_UP_BOMB_UP,
                AI_CELL_TYPE_POWER_UP_SPEED_UP,
                AI_CELL_TYPE_POWER_UP_WALL_PASS,
                AI_CELL_TYPE_UNKNOWN,
            };

            using AICellViewGrid = std::vector<std::vector<AICellType>>;

        public:
            static const AICellViewGrid &getViewGrid();
            static void recomputeViewGrid(int width, int height);

        private:
            static AICellViewGrid _viewGrid;
        };
    }
}


#endif //INDIESTUDIO_AIVIEW_HPP
