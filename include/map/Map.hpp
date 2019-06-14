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
#include "maths/Vectors.hpp"

namespace indie {

    class Map {
    public:
        static int generateMap(unsigned int width, unsigned int height, unsigned int seed, bool clamped);
        static int generateMap(unsigned int width, unsigned int height, unsigned int seed, bool clamped, const std::string &fileName);
    private:
        static void drawElement(const std::string &name, const std::string &objPath, const std::string &texturePath, const indie::maths::Vector3D position, uint64_t hitboxLayer = 0, const indie::maths::Vector3D scale = {10, 10, 10});
        static void drawCorner(unsigned int width, unsigned int height);
        static void drawFloor(unsigned int width, unsigned int height);
        static std::vector<std::pair<float, float>> getSpawn(unsigned int width, unsigned int height);
        static bool isSpawningArea(float drawX, float drawY, unsigned int width, unsigned int height);
    };

}


#endif //INDIESTUDIO_MAP_HPP
