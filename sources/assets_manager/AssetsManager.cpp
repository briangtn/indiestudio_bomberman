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
    _currentAssets["player_model"] = _texturePacks[texturePackName] + "models/player.b3d";
    _currentAssets["player_texture_black"] = _texturePacks[texturePackName] + "textures/Players/black.png";
    _currentAssets["player_texture_blue"] = _texturePacks[texturePackName] + "textures/Players/blue.png";
    _currentAssets["player_texture_pink"] = _texturePacks[texturePackName] + "textures/Players/pink.png";
    _currentAssets["player_texture_red"] = _texturePacks[texturePackName] + "textures/Players/red.png";
    _currentAssets["player_texture_white"] = _texturePacks[texturePackName] + "textures/Players/white.png";
    _currentAssets["player_texture_yellow"] = _texturePacks[texturePackName] + "textures/Players/yellow.png";

    _currentAssets["unbreakable_wall_model"] = _texturePacks[texturePackName] + "models/unbreakable_wall.obj";
    _currentAssets["unbreakable_wall_texture"] = _texturePacks[texturePackName] + "textures/unbreakable_wall.png";
    _currentAssets["breakable_wall_model"] = _texturePacks[texturePackName] + "models/breakable_wall.obj";
    _currentAssets["breakable_wall_texture"] = _texturePacks[texturePackName] + "textures/breakable_wall.png";
    _currentAssets["floor_model"] = _texturePacks[texturePackName] + "models/floor.obj";
    _currentAssets["floor_texture"] = _texturePacks[texturePackName] + "textures/floor.png";

    _currentAssets["bomb_normal_model"] = _texturePacks[texturePackName] + "models/bombs/bomb_normal.b3d";
    _currentAssets["bomb_normal_texture"] = _texturePacks[texturePackName] + "textures/bombs/bomb_normal.png";
    _currentAssets["bomb_normal_particle_texture"] = _texturePacks[texturePackName] + "textures/bombs/bomb_normal_particle.png";
    _currentAssets["bomb_normal_sound"] = _texturePacks[texturePackName] + "sounds/bomb_normal.ogg";

    _currentAssets["bomb_plasma_model"] = _texturePacks[texturePackName] + "models/bombs/bomb_plasma.b3d";
    _currentAssets["bomb_plasma_texture"] = _texturePacks[texturePackName] + "textures/bombs/bomb_plasma.png";
    _currentAssets["bomb_plasma_particle_texture"] = _texturePacks[texturePackName] + "textures/bombs/bomb_plasma_particle.png";
    _currentAssets["bomb_plasma_sound"] = _texturePacks[texturePackName] + "sounds/bomb_plasma.ogg";

    _currentAssets["bomb_sexy_model"] = _texturePacks[texturePackName] + "models/bombs/bomb_sexy.b3d";
    _currentAssets["bomb_sexy_texture"] = _texturePacks[texturePackName] + "textures/bombs/bomb_sexy.png";
    _currentAssets["bomb_sexy_particle_texture"] = _texturePacks[texturePackName] + "textures/bombs/bomb_sexy_particle.png";
    _currentAssets["bomb_sexy_sound"] = _texturePacks[texturePackName] + "sounds/bomb_sexy.ogg";

    _currentAssets["bomb_water_model"] = _texturePacks[texturePackName] + "models/bombs/bomb_water.b3d";
    _currentAssets["bomb_water_texture"] = _texturePacks[texturePackName] + "textures/bombs/bomb_water.png";
    _currentAssets["bomb_water_particle_texture"] = _texturePacks[texturePackName] + "textures/bombs/bomb_water_particle.png";
    _currentAssets["bomb_water_sound"] = _texturePacks[texturePackName] + "sounds/bomb_water.ogg";

    _currentAssets["bomb_fire_model"] = _texturePacks[texturePackName] + "models/bombs/bomb_fire.b3d";
    _currentAssets["bomb_fire_texture"] = _texturePacks[texturePackName] + "textures/bombs/bomb_fire.png";
    _currentAssets["bomb_fire_particle_texture"] = _texturePacks[texturePackName] + "textures/bombs/bomb_fire_particle.png";
    _currentAssets["bomb_fire_sound"] = _texturePacks[texturePackName] + "sounds/bomb_fire.ogg";

    _currentAssets["default_menu_background"] = _texturePacks[texturePackName] + "textures/GUI/default_menu_background.png";
    _currentAssets["default_font"] = _texturePacks[texturePackName] + "fonts/default_font.png";
    _currentAssets["default_button_texture"] = _texturePacks[texturePackName] + "textures/GUI/default_button.png";
    _currentAssets["default_particle_texture"] = _texturePacks[texturePackName] + "textures/default_particle.png";
    _currentAssets["ai_icon"] = _texturePacks[texturePackName] + "textures/GUI/ai_icon.png";
    _currentAssets["input_config_icon"] = _texturePacks[texturePackName] + "textures/GUI/input_config_icon.png";
    _currentAssets["input_exist_icon"] = _texturePacks[texturePackName] + "textures/GUI/input_exist_icon.png";
    _currentAssets["valid_selection_icon"] = _texturePacks[texturePackName] + "textures/GUI/valid_selection_icon.png";

    _currentAssets["item_bombup_model"] = _texturePacks[texturePackName] + "models/items/item_bombup.b3d";
    _currentAssets["item_fireup_model"] = _texturePacks[texturePackName] + "models/items/item_fireup.b3d";
    _currentAssets["item_speedup_model"] = _texturePacks[texturePackName] + "models/items/item_speedup.b3d";
    _currentAssets["item_wallpass_model"] = _texturePacks[texturePackName] + "models/items/item_wallpass.b3d";
    _currentAssets["items_texture"] = _texturePacks[texturePackName] + "textures/items.png";

    _currentAssets["music_battle"] = _texturePacks[texturePackName] + "sounds/music_battle.ogg";
    _currentAssets["music_player_select"] = _texturePacks[texturePackName] + "sounds/music_player_select.ogg";
    _currentAssets["music_result"] = _texturePacks[texturePackName] + "sounds/music_result.ogg";
    _currentAssets["music_title"] = _texturePacks[texturePackName] + "sounds/music_title.ogg";
    _currentAssets["music_win"] = _texturePacks[texturePackName] + "sounds/music_win.ogg";

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