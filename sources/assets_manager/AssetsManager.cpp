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
    :   _currentAssets(),
        _texturePacks()
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
        _texturePacks.emplace(texturePackName, path);
    else
        throw indie::exceptions::AssetsManagerExceptions("Texture pack doesn't exist : " + texturePackName);
    return 0;
}

int indie::AssetsManager::loadTexturePack(const std::string &texturePackName)
{
    if (_texturePacks.find(texturePackName) == _texturePacks.end())
        throw indie::exceptions::AssetsManagerExceptions(texturePackName + " texture pack can't be loaded");

    _currentAssets.empty();
    _currentAssets["player_model"] = _texturePacks[texturePackName] + "player_model.b3d";
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

    _currentAssets["bomb_normal_model"] = _texturePacks[texturePackName] + "bomb_normal_model.obj";
    _currentAssets["bomb_normal_texture"] = _texturePacks[texturePackName] + "bomb_normal_texture.png";
    _currentAssets["bomb_normal_particle_texture"] = _texturePacks[texturePackName] + "bomb_normal_particle_texture.png";
    _currentAssets["bomb_normal_sound"] = _texturePacks[texturePackName] + "bomb_normal_sound.ogg";

    _currentAssets["bomb_plasma_model"] = _texturePacks[texturePackName] + "bomb_plasma_model.obj";
    _currentAssets["bomb_plasma_texture"] = _texturePacks[texturePackName] + "bomb_plasma_texture.png";
    _currentAssets["bomb_plasma_particle_texture"] = _texturePacks[texturePackName] + "bomb_plasma_particle_texture.png";
    _currentAssets["bomb_plasma_sound"] = _texturePacks[texturePackName] + "bomb_plasma_sound.ogg";

    _currentAssets["bomb_sexy_model"] = _texturePacks[texturePackName] + "bomb_sexy_model.obj";
    _currentAssets["bomb_sexy_texture"] = _texturePacks[texturePackName] + "bomb_sexy_texture.png";
    _currentAssets["bomb_sexy_particle_texture"] = _texturePacks[texturePackName] + "bomb_sexy_particle_texture.png";
    _currentAssets["bomb_sexy_sound"] = _texturePacks[texturePackName] + "bomb_sexy_sound.ogg";

    _currentAssets["bomb_water_model"] = _texturePacks[texturePackName] + "bomb_water_model.obj";
    _currentAssets["bomb_water_texture"] = _texturePacks[texturePackName] + "bomb_water_texture.png";
    _currentAssets["bomb_water_particle_texture"] = _texturePacks[texturePackName] + "bomb_water_particle_texture.png";
    _currentAssets["bomb_water_sound"] = _texturePacks[texturePackName] + "bomb_water_sound.ogg";

    _currentAssets["bomb_fire_model"] = _texturePacks[texturePackName] + "bomb_fire_model.obj";
    _currentAssets["bomb_fire_texture"] = _texturePacks[texturePackName] + "bomb_fire_texture.png";
    _currentAssets["bomb_fire_particle_texture"] = _texturePacks[texturePackName] + "bomb_fire_particle_texture.png";
    _currentAssets["bomb_fire_sound"] = _texturePacks[texturePackName] + "bomb_fire_sound.ogg";

    _currentAssets["default_menu_background"] = _texturePacks[texturePackName] + "default_menu_background.png";

    _currentAssets["default_font"] = _texturePacks[texturePackName] + "default_font.png";
    _currentAssets["default_button_texture"] = _texturePacks[texturePackName] + "default_button_texture.png";
    _currentAssets["default_particle_texture"] = _texturePacks[texturePackName] + "default_particle_texture.png";
    _currentAssets["ai_icon"] = _texturePacks[texturePackName] + "ai_icon.png";
    _currentAssets["input_config_icon"] = _texturePacks[texturePackName] + "input_config_icon.png";
    _currentAssets["input_exist_icon"] = _texturePacks[texturePackName] + "input_exist_icon.png";
    _currentAssets["valid_selection_icon"] = _texturePacks[texturePackName] + "valid_selection_icon.png";

    _currentAssets["item_bombup_model"] = _texturePacks[texturePackName] + "item_bombup_model.b3d";
    _currentAssets["item_fireup_model"] = _texturePacks[texturePackName] + "item_fireup_model.b3d";
    _currentAssets["item_speedup_model"] = _texturePacks[texturePackName] + "item_speedup_model.b3d";
    _currentAssets["item_wallpass_model"] = _texturePacks[texturePackName] + "item_wallpass_model.b3d";
    _currentAssets["items_texture"] = _texturePacks[texturePackName] + "items_texture.png";

    return (0);
}

std::string indie::AssetsManager::getAsset(const std::string &asset)
{
    return indie::AssetsManager::getInstance().getAssets().at(asset);
}

std::map<std::string, std::string> indie::AssetsManager::getAssets() const
{
    return _currentAssets;
}

const std::string &indie::AssetsManager::operator[](const std::string &asset)
{
    return _currentAssets[asset];
}