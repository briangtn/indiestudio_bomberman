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
#include "IrrlichtClosingWindowEvent.hpp"
#include "MeshExceptions.hpp"

jf::components::Mesh::Mesh(jf::entities::Entity &entity, const std::string filename) 
    : Component(entity), 
      _mesh(nullptr), 
      _node(nullptr), 
      _meshFilename(filename),
      _shouldMeshChange(false),
      _shouldTextureChange(false)
{
    ECSWrapper ecs;
    _irrlichtClosingWindowEventID = ecs.eventManager.addListener<Mesh, events::IrrlichtClosingWindowEvent>(this, [](Mesh *mesh, events::IrrlichtClosingWindowEvent e) {
        if (mesh->_node != nullptr) {
            mesh->_node->remove();
            mesh->_node = nullptr;
            mesh->_mesh = nullptr;
        }
    });
    EMIT_CREATE(Mesh);
}

jf::components::Mesh::~Mesh()
{
    EMIT_DELETE(Mesh);
    ECSWrapper ecs;
    ecs.eventManager.removeListener(_irrlichtClosingWindowEventID);
    if (_node)
        _node->remove();
}

void jf::components::Mesh::linkFilenameToMesh()
{
    if (_mesh != nullptr)
        return;
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr)
        throw exceptions::MeshExceptions("No scene Manager available");
    _mesh = sceneManager->getMesh(_meshFilename.c_str());
    if (_mesh == nullptr)
        throw exceptions::MeshExceptions("Mesh creation failed");
}

void jf::components::Mesh::setPos(irr::core::vector3df &vector)
{
    if (!_node)
        throw exceptions::MeshExceptions("Scene Node not available");
    _node->setPosition(vector);
}

void jf::components::Mesh::setScale(irr::core::vector3df &vector)
{
    if (!_node)
        throw exceptions::MeshExceptions("Scene Node not available");
    _node->setScale(vector);
}

void jf::components::Mesh::rotate(irr::core::vector3df &vector)
{
    if (!_node)
        throw exceptions::MeshExceptions("Scene Node not available");
    _node->setRotation(vector);
}

void jf::components::Mesh::setTexture(const std::string &filename)
{
    _textureFilename = filename;
    _shouldTextureChange = true;
}

void jf::components::Mesh::applyChange()
{
    if (_shouldTextureChange) {
        if (_textureFilename.c_str() == nullptr)
            throw exceptions::MeshExceptions("no pass for texture available");
        ECSWrapper ecs;
        irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
        if (sceneManager == nullptr)
            throw exceptions::MeshExceptions("no scene manager available");
        if (!_node)
            throw exceptions::MeshExceptions("Scene Node not available");
        _node->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture(_meshFilename.c_str()));
        _shouldTextureChange = false;
    }

    if (_shouldMeshChange) {
        if (_meshFilename.c_str() == nullptr)
            throw exceptions::MeshExceptions("no pass for mesh available");
        ECSWrapper ecs;
        irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
        if (sceneManager == nullptr)
            throw exceptions::MeshExceptions("no scene manager available");
        _mesh = sceneManager->getMesh(_meshFilename.c_str());
        if (_mesh == nullptr)
            throw exceptions::MeshExceptions("Mesh creation failed");
        _shouldMeshChange = false;
    }
}

void jf::components::Mesh::changeMesh(const std::string &filename)
{
    if (_node)
        _node->remove();
    _node = nullptr;
    _mesh = nullptr;
    _shouldMeshChange = true;
    _meshFilename = filename;
}

void jf::components::Mesh::addToScene()
{
    if (_node != nullptr)
        return;
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr || _mesh == nullptr)
        throw exceptions::MeshExceptions("no scene manager or no mesh available");
    _node = sceneManager->addAnimatedMeshSceneNode(_mesh);
    if (_node == nullptr)
        throw exceptions::MeshExceptions("no scene node available");
    _node->setVisible(true);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void jf::components::Mesh::changeVisibility(bool shouldBeSeen)
{
    if (_node == nullptr)
        throw exceptions::MeshExceptions("no scene node available");
    _node->setVisible(shouldBeSeen);
}