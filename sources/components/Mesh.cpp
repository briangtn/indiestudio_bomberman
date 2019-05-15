/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Mesh
*/

#include "Entity.hpp"
#include "Mesh.hpp"
#include "ECSWrapper.hpp"
#include "Events.hpp"

jf::components::Mesh::Mesh(jf::entities::Entity &entity, const std::string filename) : Component(entity), _mesh(nullptr), _node(nullptr), _filename(filename)
{
    EMIT_CREATE(Mesh);
}

jf::components::Mesh::~Mesh()
{
    EMIT_DELETE(Mesh);
}

void jf::components::Mesh::linkFilenameToMesh()
{
    if (_mesh != nullptr)
        return;
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr)
        throw;
    _mesh = sceneManager->getMesh(_filename.c_str());
    if (_mesh == nullptr)
        throw;
}

void jf::components::Mesh::setPos(irr::core::vector3df &vector)
{
    if (!_node)
        throw;
    _node->setPosition(vector);
}

void jf::components::Mesh::setScale(irr::core::vector3df &vector)
{
    if (!_node)
        throw;
    _node->setScale(vector);
}

void jf::components::Mesh::rotate(irr::core::vector3df &vector)
{
    if (!_node)
        throw;
    _node->setRotation(vector);
}

void jf::components::Mesh::setTexture(const std::string &filename)
{
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    _node->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture(filename.c_str()));
}

void jf::components::Mesh::changeMesh(const std::string &filename, bool shouldBeSeen, bool shouldAddToScene)
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
    if (shouldAddToScene) {
        _node = sceneManager->addAnimatedMeshSceneNode(_mesh);
        if (_node == nullptr)
            throw;
        _node->setVisible(true);
    }
}

void jf::components::Mesh::addToScene()
{
    if (_node != nullptr)
        return;
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr || _mesh == nullptr)
        throw;
    _node = sceneManager->addAnimatedMeshSceneNode(_mesh);
    if (_node == nullptr)
        throw;
    _node->setVisible(true);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void jf::components::Mesh::changeVisibility(bool shouldBeSeen)
{
    if (_node == nullptr)
        throw;
    _node->setVisible(shouldBeSeen);
}