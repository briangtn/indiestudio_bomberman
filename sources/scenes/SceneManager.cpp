/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** SceneManager.cpp
*/

/* Created the 22/05/2019 at 14:49 by jfrabel */

#include "exceptions/SceneManagerException.hpp"
#include "scenes/SceneManager.hpp"
#include "ECSWrapper.hpp"

indie::scenes::SceneManager::SceneManager()
    : _currentScene(""), _sceneMap()
{

}

indie::scenes::SceneManager::~SceneManager()
{
    try {
        IScene &scene = getSceneByName(_currentScene);
        scene.onStop();
    } catch (exceptions::SceneManagerException &e) {}
}

indie::scenes::IScene &indie::scenes::SceneManager::getSceneByName(const std::string &sceneName)
{
    auto it = _sceneMap.find(sceneName);
    if (it == _sceneMap.end()) {
        throw exceptions::SceneManagerException("Scene name " + sceneName + " does not exist.", "getSceneByName");
    }
    return *(it->second);
}

void indie::scenes::SceneManager::addScene(const std::string &name, indie::scenes::IScene *scene)
{
    _sceneMap.emplace(std::make_pair(name, std::unique_ptr<IScene>(scene)));
}

void indie::scenes::SceneManager::addScenes(const std::vector<std::pair<std::string, IScene *>> &scenes)
{
    SceneManager &instance = getInstance();
    for (auto &pair : scenes) {
        instance.addScene(pair.first, pair.second);
    }
}

void indie::scenes::SceneManager::changeScene(const std::string &sceneName)
{
    SceneManager &instance = getInstance();
    IScene &newScene = instance.getSceneByName(sceneName);
    try {
        IScene &currentScene = instance.getSceneByName(instance._currentScene);
        currentScene.onStop();
    } catch (exceptions::SceneManagerException &e) {}
    ECSWrapper ecs;
    ecs.entityManager.deleteAllEntities();
    instance._currentScene = sceneName;
    newScene.onStart();
}

indie::scenes::SceneManager &indie::scenes::SceneManager::getInstance()
{
    static SceneManager instance;
    return instance;
}