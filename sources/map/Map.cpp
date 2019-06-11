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

void indie::Map::drawElement(const std::string &objPath, const std::string &texturePath, const indie::maths::Vector3D position, uint64_t hitboxLayer, const indie::maths::Vector3D scale)
{
    ECSWrapper ecs;

    auto cubeEntity = ecs.entityManager.createEntity("cube");
    cubeEntity->setShouldBeKeeped(true);
    auto tr = cubeEntity->assignComponent<indie::components::Transform>();
    tr->setPosition(position);
    tr->setScale(scale);
    cubeEntity->assignComponent<indie::components::Mesh, std::string>(objPath);
    auto mat = cubeEntity->assignComponent<indie::components::Material, std::string>(texturePath);
    mat->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
    mat->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    if (hitboxLayer != 0)
        cubeEntity->assignComponent<indie::components::BoxCollider, maths::Vector3D, maths::Vector3D>({0.5, 0.5, 0.5}, {0, 0, 0}, hitboxLayer);
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
    ECSWrapper ecs;
    for (int i = 10; i > (static_cast<float>(height) * -10.0f) - 10.0f; i -= 10) {
        drawElement("../test_assets/cube.obj", "../test_assets/unbreakable_texture.png", {-10, 0, static_cast<float>(i)}, 0);
        drawElement("../test_assets/cube.obj", "../test_assets/unbreakable_texture.png", {width * 10.0f, 0, static_cast<float>(i)}, 0);
    }
    auto wallLeft = ecs.entityManager.createEntity("wallLeft");
    auto trWL = wallLeft->assignComponent<indie::components::Transform>();
    trWL->setPosition({-10.0f, 0.0f, height * -4.5f});
    trWL->setScale({10.0f, 10.0f, height * 15.0f});
    wallLeft->assignComponent<components::BoxCollider, maths::Vector3D, maths::Vector3D, uint64_t>({0.5f, 0.5f, 0.5f}, {0, 0, 0}, UNBREAKABLE_BLOCK_LAYER);
    auto wallRight = ecs.entityManager.createEntity("wallRight");
    auto trWR = wallRight->assignComponent<indie::components::Transform>();
    trWR->setPosition({width * 10.0f, 0.0f, height * -4.5f});
    trWR->setScale({10.0f, 10.0f, height * 15.0f});
    wallRight->assignComponent<components::BoxCollider, maths::Vector3D, maths::Vector3D, uint64_t>({0.5f, 0.5f, 0.5f}, {0, 0, 0}, UNBREAKABLE_BLOCK_LAYER);
    for (int j = 0; j < width * 10; j += 10) {
        drawElement("../test_assets/cube.obj", "../test_assets/unbreakable_texture.png", {static_cast<float>(j), 0, 10.0f}, 0);
        drawElement("../test_assets/cube.obj", "../test_assets/unbreakable_texture.png", {static_cast<float>(j), 0, height * -10.0f}, 0);
    }
    auto wallUp = ecs.entityManager.createEntity("wallUp");
    auto trWU = wallUp->assignComponent<indie::components::Transform>();
    trWU->setPosition({width * 4.5f, 0.0f, 10.0f});
    trWU->setScale({width * 15.0f, 10.0f, 10.0f});
    wallUp->assignComponent<components::BoxCollider, maths::Vector3D, maths::Vector3D, uint64_t>({0.5f, 0.5f, 0.5f}, {0, 0, 0}, UNBREAKABLE_BLOCK_LAYER);
    auto wallDown = ecs.entityManager.createEntity("wallDown");
    auto trWD = wallDown->assignComponent<indie::components::Transform>();
    trWD->setPosition({width * 4.5f, 0.0f, height * -10.0f});
    trWD->setScale({width * 15.0f, 10.0f, 10.0f});
    wallDown->assignComponent<components::BoxCollider, maths::Vector3D, maths::Vector3D, uint64_t>({0.5f, 0.5f, 0.5f}, {0, 0, 0}, UNBREAKABLE_BLOCK_LAYER);
}

void indie::Map::drawFloor(unsigned int width, unsigned int height)
{
    for (int y = 0; y > height * -10.0f; y -= 10) {
        for (int x = 0; x < width * 10.0f; x+= 10) {
            drawElement("../test_assets/cube.obj", "../test_assets/grass_texture.png", {static_cast<float>(x), -10, static_cast<float>(y)}, 0);
        }
    }
}

int indie::Map::generateMap(unsigned int width, unsigned int height, unsigned int seed, bool clamped)
{
    indie::PpmImage image(width, height);
    Perlin pr(seed);
    double n = 0;
    float drawX = 0;
    float drawY = 0;

    drawFloor(width, height);
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
            if (y % 2 == 0 && x % 2 == 0 && y > 0 && x > 0 && x < width - 1 &&
                y < height - 1 && !isSpawningArea(drawX, drawY, width, height))
                drawElement("../test_assets/cube.obj", "../test_assets/unbreakable_texture.png", {drawX, 0, drawY}, UNBREAKABLE_BLOCK_LAYER);
            else if (n > 122 && !isSpawningArea(drawX, drawY, width, height))
                drawElement("../test_assets/case2.obj", "../test_assets/case_texture.jpg", {drawX, 0, drawY}, BREAKABLE_BLOCK_LAYER);
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
            else if (y % 2 == 0 && x % 2 == 0 && y > 0 && x > 0 && x < width - 1 &&
                    y < height - 1 && !isSpawningArea(drawX, drawY, width, height))
                n = 122;
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