/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** AssetsManager.hpp
*/

//
// Created by romainfouyer on 6/4/19.
//

#ifndef INDIESTUDIO_ASSETSMANAGER_HPP
#define INDIESTUDIO_ASSETSMANAGER_HPP

#include <string>
#include <map>

namespace indie {

    class AssetsManager {
    public:

        static AssetsManager &getInstance();

    private:

        AssetsManager();
        AssetsManager(const AssetsManager &other) = delete;
        AssetsManager(AssetsManager &&other) = delete;

    public:
        int addTexturePack(const std::string &texturePackName, const std::string &path);
        int loadTexturePack(const std::string &texturePackName);

        std::map<std::string, std::string> getAssets() const;
        static const std::string &getAsset(const std::string &asset);

    private:
        std::map<std::string, std::string> _texturePacks;
        std::map<std::string, std::string> _currentAssets;

    public:
        const std::string &operator[](const std::string &asset);
    };

}


#endif //INDIESTUDIO_ASSETSMANAGER_HPP
