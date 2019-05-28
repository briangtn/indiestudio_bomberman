/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** InputManager.cpp
*/

/* Created by romainfouyer on 5/27/19. */

#include <cmath>
#include "map/Map.hpp"
#include "map/PpmImage.hpp"
#include "map/Perlin.hpp"
#include "components/Transform.hpp"
#include "components/Material.hpp"
#include "ECSWrapper.hpp"
#include "components/Mesh.hpp"
#include <iostream>

std::vector<std::pair<float, float>> indie::Map::getSpawn(unsigned int width, unsigned int height)
{
    return {
            {0, 0}, {10, 0}, {0, -10}, {10, -10},
            {(10 * width) - 10, 0}, {(10 * width) - 20, 0}, {(10 * width) - 10, -10}, {(10 * width) - 20, -10},
            {0, (static_cast<float>(height) * -10.0f) + 10.0f}, {10, (static_cast<float>(height) * -10.0f) + 10.0f},
            {0, (static_cast<float>(height) * -10.0f) + 20.0f}, {10, (static_cast<float>(height) * -10.0f) + 20.0f},
            {(10 * width) - 10, (static_cast<float>(height) * -10.0f) + 10.0f},
            {(10 * width) - 20, (static_cast<float>(height) * -10.0f) + 10.0f},
            {(10 * width) - 10, (static_cast<float>(height) * -10.0f) + 20.0f},
            {(10 * width) - 20, (static_cast<float>(height) * -10.0f) + 20.0f},
    };
}

void indie::Map::drawCube(float drawX, float drawY, const std::string &textureName)
{
    ECSWrapper ecs;

    auto cubeEntity = ecs.entityManager.createEntity("cube");
    auto tr = cubeEntity->assignComponent<indie::components::Transform>();
    tr->setPosition({drawX, drawY, 10});
    tr->setScale({10, 10, 2});
    cubeEntity->assignComponent<indie::components::Mesh, std::string>("../test_assets/cube.obj");
    auto mat = cubeEntity->assignComponent<indie::components::Material, std::string>(textureName);
    mat->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
    mat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

bool indie::Map::isSpawningArea(float drawX, float drawY, unsigned int width, unsigned int height)
{
    for (auto &it : getSpawn(width, height)) {
        if (it.first == drawX && it.second == drawY)
            return true;
    }
    return false;
}

void indie::Map::drawCorner(unsigned int width, unsigned int height)
{
    for (int i = 10; i > (static_cast<float>(height) * -10.0f) - 10.0f; i -= 10) {
        drawCube(-10, static_cast<float>(i), "../test_assets/unbreakable_cube.png");
        drawCube(width * 10, static_cast<float>(i), "../test_assets/unbreakable_cube.png");
    }
    for (int j = 0; j < width * 10; j++) {
        drawCube(static_cast<float>(j), 10.0f, "../test_assets/unbreakable_cube.png");
        drawCube(static_cast<float>(j), static_cast<float>(height) * -10.0f, "../test_assets/unbreakable_cube.png");
    }
}

int indie::Map::generateMap(unsigned int width, unsigned int height, unsigned int seed, bool clamped)
{
    indie::PpmImage image(width, height);
    Perlin pr(seed);
    double n = 0;
    float drawX = 0;
    float drawY = 0;

    drawCorner(width, height);
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            n = 20 * pr.noise(x, y, 0.8);
            n -= floor(n);
            if (clamped) {
                if (255 * n >= 122) n = 255;
                else if (255 * n < 122) n = 0;
            } else
                n = floor(255 * n);
            if (y % 2 == 0 && x % 2 == 0 && y > 0 && x > 0 && x < width - 1 && y < height - 1 && !isSpawningArea(drawX, drawY, width, height))
                drawCube(drawX, drawY, "../test_assets/unbreakable_cube.png");
            else if (n > 122 && !isSpawningArea(drawX, drawY, width, height))
                drawCube(drawX, drawY, "../test_assets/cube_texture.png");
            drawX += 10;
        }
        drawX = 0;
        drawY -= 10;
    }
    return 0;
}

int indie::Map::generateMap(unsigned int width, unsigned int height, unsigned int seed, bool clamped, const std::string &fileName)
{
    indie::PpmImage image(width, height);
    Perlin pr(seed);
    unsigned int co = 0;
    double n = 0;
    float drawX = 0;
    float drawY = 0;

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            n = 20 * pr.noise(x, y, 0.8);
            n -= floor(n);
            if (clamped) {
                if (255 * n >= 122)
                    n = 255;
                else if (255 * n < 122)
                    n = 0;
            } else
                n = floor(255 * n);
            if (isSpawningArea(drawX, drawY, width, height))
                n = 0;
            else if (y % 2 == 0 && x % 2 == 0 && y > 0 && x > 0 && x < width - 1 && y < height - 1 && !isSpawningArea(drawX, drawY, width, height)) {
                std::cout << "[" << drawX << ";" << drawY << "]" << std::endl;
                n = 122;
            }
            image._rgb['r'][co] = n;
            image._rgb['g'][co] = n;
            image._rgb['b'][co] = n;
            co++;
            drawX += 10;
        }
        drawX = 0;
        drawY -= 10;
    }
    image.writeImage(fileName);
    return 0;
}