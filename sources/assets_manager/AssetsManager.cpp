/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** AssetsManager.cpp
*/

//
// Created by romainfouyer on 6/4/19.
//

#include "assets_manager/AssetsManager.hpp"
#include <iostream>
#include <boost/filesystem.hpp>
#include <exceptions/AssetsManagerExceptions.hpp>

indie::AssetsManager::AssetsManager()
{

}

indie::AssetsManager &indie::AssetsManager::getInstance()
{
    static indie::AssetsManager instance;

    return instance;
}

int indie::AssetsManager::addTexturePack(const std::string &texturePackName, const std::string &path)
{
    boost::filesystem::path fp(path);

    if (boost::filesystem::is_directory(fp))
        _texturePacks[texturePackName] = path;
    else
        throw indie::exceptions::AssetsManagerExceptions("Texture pack doesn't exist : " + texturePackName);
    return 0;
}

int indie::AssetsManager::loadTexturePack(const std::string &texturePackName)
{
    if (_currentAssets.find(texturePackName) == _currentAssets.end())
        throw indie::exceptions::AssetsManagerExceptions(texturePackName + " texture pack can't be loaded");
    _currentAssets["player_model"] = _texturePacks[texturePackName] + "player_model.obj";
    _currentAssets["player_texture"] = _texturePacks[texturePackName] + "player_texture.png";
    _currentAssets["enemy_one_model"] = _texturePacks[texturePackName] + "enemy_one_model.obj";
    _currentAssets["enemy_one_texture"] = _texturePacks[texturePackName] + "enemy_one_texture.png";
    _currentAssets["enemy_two_model"] = _texturePacks[texturePackName] + "enemy_two_model.obj";
    _currentAssets["enemy_two_texture"] = _texturePacks[texturePackName] + "enemy_two_texture.png";
    _currentAssets["enemy_three_model"] = _texturePacks[texturePackName] + "enemy_three_model.obj";
    _currentAssets["enemy_three_texture"] = _texturePacks[texturePackName] + "enemy_three_texture.png";
    _currentAssets["unbreakable_wall_model"] = _texturePacks[texturePackName] + "unbreakable_wall_model.obj";
    _currentAssets["unbreakable_wall_texture"] = _texturePacks[texturePackName] + "unbreakable_wall_texture.png";
    _currentAssets["breakable_wall_model"] = _texturePacks[texturePackName] + "breakable_wall_model.obj";
    _currentAssets["breakable_wall_texture"] = _texturePacks[texturePackName] + "breakable_wall_texture.png";
    _currentAssets["floor_model"] = _texturePacks[texturePackName] + "floor_model.obj";
    _currentAssets["floor_texture"] = _texturePacks[texturePackName] + "floor_texture.png";
    _currentAssets["fire_bomb_model"] = _texturePacks[texturePackName] + "fire_bomb_model.obj";
    _currentAssets["fire_bomb_texture"] = _texturePacks[texturePackName] + "fire_bomb_texture.png";
    _currentAssets["normal_bomb_model"] = _texturePacks[texturePackName] + "normal_bomb_model.obj";
    _currentAssets["normal_bomb_texture"] = _texturePacks[texturePackName] + "normal_bomb_texture.png";
    _currentAssets["love_bomb_model"] = _texturePacks[texturePackName] + "love_bomb_model.obj";
    _currentAssets["love_bomb_texture"] = _texturePacks[texturePackName] + "love_bomb_texture.png";
    _currentAssets["water_bomb_model"] = _texturePacks[texturePackName] + "water_bomb_model.obj";
    _currentAssets["water_bomb_texture"] = _texturePacks[texturePackName] + "water_bomb_texture.png";
    _currentAssets["lightning_bomb_model"] = _texturePacks[texturePackName] + "lightning_bomb_model.obj";
    _currentAssets["lightning_bomb_texture"] = _texturePacks[texturePackName] + "lightning_bomb_texture.png";
}

const std::string &indie::AssetsManager::getAsset(const std::string &asset)
{
    return indie::AssetsManager::getInstance().getAssets()[asset];
}

std::map<std::string, std::string> indie::AssetsManager::getAssets() const
{
    return _currentAssets;
}

const std::string &indie::AssetsManager::operator[](const std::string &asset)
{
    return _currentAssets[asset];
}