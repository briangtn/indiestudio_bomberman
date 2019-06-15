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

#define RESOURCES_PACK_PATH "./resources/resources_packs/"

namespace indie {

    class AssetsManager {
    public:

        static AssetsManager &getInstance();

    private:

        AssetsManager();
        AssetsManager(const AssetsManager &other) = delete;
        AssetsManager(AssetsManager &&other) = delete;

    public:
        int addResourcesPack(const std::string &texturePackName, const std::string &path);
        int loadResourcesPack(const std::string &texturePackName);

        void fetchResourcesPacks();

        std::map<std::string, std::string> getResourcesPacks() const;
        std::map<std::string, std::string> getAssets() const;
        static std::string getAsset(const std::string &asset);

    private:
        std::map<std::string, std::string> _resourcesPacks;
        std::map<std::string, std::string> _currentAssets;

    public:
        const std::string &operator[](const std::string &asset);
    };

}


#endif //INDIESTUDIO_ASSETSMANAGER_HPP
