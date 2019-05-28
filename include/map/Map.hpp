/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Map.hpp
*/

/* Created by romainfouyer on 5/27/19. */

#ifndef INDIESTUDIO_MAP_HPP
#define INDIESTUDIO_MAP_HPP

#include <string>
#include <vector>

namespace indie {

    class Map {
    public:
        static int generateMap(unsigned int width, unsigned int height, unsigned int seed, bool clamped);
        static int generateMap(unsigned int width, unsigned int height, unsigned int seed, bool clamped, const std::string &fileName);
    private:
        static void drawCorner(unsigned int width, unsigned int height);
        static void drawCube(float drawX, float drawY, const std::string &textureName);
        static std::vector<std::pair<float, float>> getSpawn(unsigned int width, unsigned int height);
        static bool isSpawningArea(float drawX, float drawY, unsigned int width, unsigned int height);
    };

}


#endif //INDIESTUDIO_MAP_HPP
