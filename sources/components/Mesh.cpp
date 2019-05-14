/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Mesh
*/

#include "Mesh.hpp"
#include "ECSWrapper.hpp"

Mesh::Mesh(const std::string filename) : _mesh(nullptr), _node(nullptr)
{
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr)
        throw;
    _mesh = sceneManager->getMesh(filename.c_str());
    _node = sceneManager->addAnimatedMeshSceneNode(_mesh);
}

Mesh::~Mesh()
{
}