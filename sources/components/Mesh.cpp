/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Mesh
*/

#include "Mesh.hpp"
#include "ECSWrapper.hpp"
#include "Events.hpp"

jf::components::Mesh::Mesh(jf::entities::Entity &entity, const std::string filename) : Component(entity), _mesh(nullptr), _node(nullptr)
{
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr)
        throw;
    _mesh = sceneManager->getMesh(filename.c_str());
    if (_mesh == nullptr)
        throw;
    EMIT_CREATE(Mesh);
}

jf::components::Mesh::~Mesh()
{
    EMIT_DELETE(Mesh);
}

void jf::components::Mesh::changeMesh(const std::string filename, bool shouldBeSeen)
{
    _node->drop();
    _mesh->drop();
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr)
        throw;
    _mesh = sceneManager->getMesh(filename.c_str());
    if (_mesh == nullptr)
        throw;
    //DON'T FORGET TO ADDTOSCENE THE NEW MESH
}

void jf::components::Mesh::addToScene()
{
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr || _mesh == nullptr || _node == nullptr)
        throw;
    _node = sceneManager->addAnimatedMeshSceneNode(_mesh);
    _node->setVisible(true);
}

void jf::components::Mesh::changeVisibility(bool shouldBeSeen)
{
    if (_node == nullptr)
        throw;
    _node->setVisible(shouldBeSeen);
}