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
        _resourcesPacks()
{

}

indie::AssetsManager &indie::AssetsManager::getInstance()
{
    static indie::AssetsManager instance;

    return instance;
}

int indie::AssetsManager::addResourcesPack(const std::string &texturePackName, const std::string &path)
{
    boost::filesystem::path fp(path);

    if (boost::filesystem::is_directory(fp))
        _resourcesPacks.emplace(texturePackName, path);
    else
        throw indie::exceptions::AssetsManagerExceptions("Texture pack doesn't exist : " + texturePackName);
    return 0;
}

void indie::AssetsManager::fetchResourcesPacks()
{
    for (const auto & entry : boost::filesystem::directory_iterator(RESOURCES_PACK_PATH)) {
        std::string nativePath = entry.path().string();
        std::string fullPath = entry.path().string() + "/";
        std::string resourcePackName = nativePath.erase(0, std::string(RESOURCES_PACK_PATH).length());
        addResourcesPack(resourcePackName, fullPath);
    }
}

int indie::AssetsManager::loadResourcesPack(const std::string &texturePackName)
{
    if (_resourcesPacks.find(texturePackName) == _resourcesPacks.end())
        throw indie::exceptions::AssetsManagerExceptions(texturePackName + " texture pack can't be loaded");

    _currentAssets.empty();
    _currentAssets["player_model"] = _resourcesPacks[texturePackName] + "models/player.b3d";
    _currentAssets["player_texture_black"] = _resourcesPacks[texturePackName] + "textures/players/black.png";
    _currentAssets["player_texture_blue"] = _resourcesPacks[texturePackName] + "textures/players/blue.png";
    _currentAssets["player_texture_pink"] = _resourcesPacks[texturePackName] + "textures/players/pink.png";
    _currentAssets["player_texture_red"] = _resourcesPacks[texturePackName] + "textures/players/red.png";
    _currentAssets["player_texture_white"] = _resourcesPacks[texturePackName] + "textures/players/white.png";
    _currentAssets["player_texture_yellow"] = _resourcesPacks[texturePackName] + "textures/players/yellow.png";
    _currentAssets["player_die_sound"] = _resourcesPacks[texturePackName] + "sounds/players/player_die.ogg";

    _currentAssets["unbreakable_wall_model"] = _resourcesPacks[texturePackName] + "models/unbreakable_wall.obj";
    _currentAssets["unbreakable_wall_texture"] = _resourcesPacks[texturePackName] + "textures/unbreakable_wall.png";
    _currentAssets["breakable_wall_model"] = _resourcesPacks[texturePackName] + "models/breakable_wall.obj";
    _currentAssets["breakable_wall_texture"] = _resourcesPacks[texturePackName] + "textures/breakable_wall.png";
    _currentAssets["floor_model"] = _resourcesPacks[texturePackName] + "models/floor.obj";
    _currentAssets["floor_texture"] = _resourcesPacks[texturePackName] + "textures/floor.png";

    _currentAssets["bomb_placed_sound"] = _resourcesPacks[texturePackName] + "sounds/bombs/bomb_placed.ogg";

    _currentAssets["bomb_normal_model"] = _resourcesPacks[texturePackName] + "models/bombs/bomb_normal.b3d";
    _currentAssets["bomb_normal_texture"] = _resourcesPacks[texturePackName] + "textures/bombs/bomb_normal.png";
    _currentAssets["bomb_normal_particle_texture"] = _resourcesPacks[texturePackName] + "textures/bombs/bomb_normal_particle.png";
    _currentAssets["bomb_normal_sound"] = _resourcesPacks[texturePackName] + "sounds/bombs/bomb_normal.ogg";

    _currentAssets["bomb_plasma_model"] = _resourcesPacks[texturePackName] + "models/bombs/bomb_plasma.b3d";
    _currentAssets["bomb_plasma_texture"] = _resourcesPacks[texturePackName] + "textures/bombs/bomb_plasma.png";
    _currentAssets["bomb_plasma_particle_texture"] = _resourcesPacks[texturePackName] + "textures/bombs/bomb_plasma_particle.png";
    _currentAssets["bomb_plasma_sound"] = _resourcesPacks[texturePackName] + "sounds/bombs/bomb_plasma.ogg";

    _currentAssets["bomb_sexy_model"] = _resourcesPacks[texturePackName] + "models/bombs/bomb_sexy.b3d";
    _currentAssets["bomb_sexy_texture"] = _resourcesPacks[texturePackName] + "textures/bombs/bomb_sexy.png";
    _currentAssets["bomb_sexy_particle_texture"] = _resourcesPacks[texturePackName] + "textures/bombs/bomb_sexy_particle.png";
    _currentAssets["bomb_sexy_sound"] = _resourcesPacks[texturePackName] + "sounds/bombs/bomb_sexy.ogg";

    _currentAssets["bomb_water_model"] = _resourcesPacks[texturePackName] + "models/bombs/bomb_water.b3d";
    _currentAssets["bomb_water_texture"] = _resourcesPacks[texturePackName] + "textures/bombs/bomb_water.png";
    _currentAssets["bomb_water_particle_texture"] = _resourcesPacks[texturePackName] + "textures/bombs/bomb_water_particle.png";
    _currentAssets["bomb_water_sound"] = _resourcesPacks[texturePackName] + "sounds/bombs/bomb_water.ogg";

    _currentAssets["bomb_fire_model"] = _resourcesPacks[texturePackName] + "models/bombs/bomb_fire.b3d";
    _currentAssets["bomb_fire_texture"] = _resourcesPacks[texturePackName] + "textures/bombs/bomb_fire.png";
    _currentAssets["bomb_fire_particle_texture"] = _resourcesPacks[texturePackName] + "textures/bombs/bomb_fire_particle.png";
    _currentAssets["bomb_fire_sound"] = _resourcesPacks[texturePackName] + "sounds/bombs/bomb_fire.ogg";

    _currentAssets["bonus_bombup_sound"] = _resourcesPacks[texturePackName] + "sounds/bonus/bonus_bombup.ogg";
    _currentAssets["bonus_fireup_sound"] = _resourcesPacks[texturePackName] + "sounds/bonus/bonus_fireup.ogg";
    _currentAssets["bonus_speedup_sound"] = _resourcesPacks[texturePackName] + "sounds/bonus/bonus_speedup.ogg";
    _currentAssets["bonus_wallpass_sound"] = _resourcesPacks[texturePackName] + "sounds/bonus/bonus_wallpass.ogg";

    _currentAssets["crate_break_sound"] = _resourcesPacks[texturePackName] + "sounds/crates/crate_break.ogg";

    _currentAssets["default_menu_background"] = _resourcesPacks[texturePackName] + "textures/gui/default_menu_background.png";
    _currentAssets["default_font"] = _resourcesPacks[texturePackName] + "fonts/default_font.xml";
    _currentAssets["default_button_texture"] = _resourcesPacks[texturePackName] + "textures/gui/default_button.png";
    _currentAssets["default_particle_texture"] = _resourcesPacks[texturePackName] + "textures/default_particle.png";
    _currentAssets["ai_icon"] = _resourcesPacks[texturePackName] + "textures/gui/ai_icon.png";
    _currentAssets["input_config_icon"] = _resourcesPacks[texturePackName] + "textures/gui/input_config_icon.png";
    _currentAssets["input_exist_icon"] = _resourcesPacks[texturePackName] + "textures/gui/input_exist_icon.png";
    _currentAssets["none_icon"] = _resourcesPacks[texturePackName] + "textures/gui/none_icon.png";
    _currentAssets["valid_selection_icon"] = _resourcesPacks[texturePackName] + "textures/gui/valid_selection_icon.png";
    _currentAssets["button_exit"] = _resourcesPacks[texturePackName] + "textures/gui/button_exit.png";
    _currentAssets["button_exit_hovered"] = _resourcesPacks[texturePackName] + "textures/gui/button_exit_hovered.png";
    _currentAssets["button_new_game"] = _resourcesPacks[texturePackName] + "textures/gui/button_new_game.png";
    _currentAssets["button_new_game_hovered"] = _resourcesPacks[texturePackName] + "textures/gui/button_new_game_hovered.png";
    _currentAssets["button_load_game"] = _resourcesPacks[texturePackName] + "textures/gui/button_load_game.png";
    _currentAssets["button_load_game_hovered"] = _resourcesPacks[texturePackName] + "textures/gui/button_load_game_hovered.png";
    _currentAssets["button_settings"] = _resourcesPacks[texturePackName] + "textures/gui/button_settings.png";
    _currentAssets["button_settings_hovered"] = _resourcesPacks[texturePackName] + "textures/gui/button_settings_hovered.png";
    _currentAssets["play_button"] = _resourcesPacks[texturePackName] + "textures/gui/play_button.png";
    _currentAssets["reload_button"] = _resourcesPacks[texturePackName] + "textures/gui/reload_button.png";
    _currentAssets["button_volume_down"] = _resourcesPacks[texturePackName] + "textures/gui/button_volume_down.png";
    _currentAssets["button_volume_up"] = _resourcesPacks[texturePackName] + "textures/gui/button_volume_up.png";
    _currentAssets["button_back_to_menu"] = _resourcesPacks[texturePackName] + "textures/gui/button_back_to_menu.png";
    _currentAssets["button_back_to_menu_hovered"] = _resourcesPacks[texturePackName] + "textures/gui/button_back_to_menu_hovered.png";
    _currentAssets["button_back"] = _resourcesPacks[texturePackName] + "textures/gui/button_back.png";
    _currentAssets["button_back_hovered"] = _resourcesPacks[texturePackName] + "textures/gui/button_back_hovered.png";
    _currentAssets["button_resources_packs"] = _resourcesPacks[texturePackName] + "textures/gui/button_resources_packs.png";
    _currentAssets["button_default"] = _resourcesPacks[texturePackName] + "textures/gui/button_default.png";
    _currentAssets["button_debug_on"] = _resourcesPacks[texturePackName] + "textures/gui/button_debug_on.png";
    _currentAssets["button_debug_off"] = _resourcesPacks[texturePackName] + "textures/gui/button_debug_off.png";
    _currentAssets["button_fullscreen_on"] = _resourcesPacks[texturePackName] + "textures/gui/button_fullscreen_on.png";
    _currentAssets["button_fullscreen_off"] = _resourcesPacks[texturePackName] + "textures/gui/button_fullscreen_off.png";
    _currentAssets["logo"] = _resourcesPacks[texturePackName] + "textures/gui/logo.png";


    _currentAssets["item_bombup_model"] = _resourcesPacks[texturePackName] + "models/items/item_bombup.b3d";
    _currentAssets["item_fireup_model"] = _resourcesPacks[texturePackName] + "models/items/item_fireup.b3d";
    _currentAssets["item_speedup_model"] = _resourcesPacks[texturePackName] + "models/items/item_speedup.b3d";
    _currentAssets["item_wallpass_model"] = _resourcesPacks[texturePackName] + "models/items/item_wallpass.b3d";
    _currentAssets["items_texture"] = _resourcesPacks[texturePackName] + "textures/items.png";

    _currentAssets["music_battle"] = _resourcesPacks[texturePackName] + "musics/music_battle.ogg";
    _currentAssets["music_player_select"] = _resourcesPacks[texturePackName] + "musics/music_player_select.ogg";
    _currentAssets["music_result"] = _resourcesPacks[texturePackName] + "musics/music_result.ogg";
    _currentAssets["music_title"] = _resourcesPacks[texturePackName] + "musics/music_title.ogg";
    _currentAssets["music_win"] = _resourcesPacks[texturePackName] + "musics/music_win.ogg";

    _currentAssets["splash_screen"] = _resourcesPacks[texturePackName] + "textures/gui/splashscreen.png";

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

std::map<std::string, std::string> indie::AssetsManager::getResourcesPacks() const
{
    return _resourcesPacks;
}