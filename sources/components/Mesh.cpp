/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** Mesh
*/

#include <iomanip>
#include "Entity.hpp"
#include "components/Mesh.hpp"
#include "ECSWrapper.hpp"
#include "Events.hpp"
#include "events/IrrlichtClosingWindowEvent.hpp"
#include "exceptions/MeshExceptions.hpp"

indie::components::Mesh::Mesh(jf::entities::Entity &entity, const std::string filename)
    : Component(entity), 
      _mesh(nullptr), 
      _node(nullptr), 
      _meshFilename(filename),
      _shouldMeshChange(false)
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

indie::components::Mesh::~Mesh()
{
    EMIT_DELETE(Mesh);
    ECSWrapper ecs;
    ecs.eventManager.removeListener(_irrlichtClosingWindowEventID);
    if (_node)
        _node->remove();
}

bool indie::components::Mesh::linkFilenameToMesh()
{
    if (_mesh != nullptr)
        return false;
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr)
        throw exceptions::MeshExceptions("No scene Manager available");
    _mesh = sceneManager->getMesh(_meshFilename.c_str());
    if (_mesh == nullptr)
        throw exceptions::MeshExceptions("Mesh creation failed");
    return true;
}

void indie::components::Mesh::setPos(irr::core::vector3df &vector)
{
    if (!_node)
        throw exceptions::MeshExceptions("Mesh Node not available");
    _node->setPosition(vector);
}

void indie::components::Mesh::setScale(irr::core::vector3df &vector)
{
    if (!_node)
        throw exceptions::MeshExceptions("Mesh Node not available");
    _node->setScale(vector);
}

void indie::components::Mesh::rotate(irr::core::vector3df &vector)
{
    if (!_node)
        throw exceptions::MeshExceptions("Mesh Node not available");
    _node->setRotation(vector);
}

void indie::components::Mesh::setMaterialTexture(const std::string &filename)
{
    if (!_node)
        throw exceptions::MeshExceptions("Mesh Node not available");
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr)
        throw exceptions::MeshExceptions("No scene manager available");
    if (filename.c_str() == nullptr)
        throw exceptions::MeshExceptions("No path for texture available");
    _node->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture(filename.c_str()));
}

void indie::components::Mesh::setMaterialType(irr::video::E_MATERIAL_TYPE type)
{
    if (!_node)
        throw exceptions::MeshExceptions("Mesh Node not available");
    _node->setMaterialType(type);
}

void indie::components::Mesh::setMaterialFlag(irr::video::E_MATERIAL_FLAG flag, bool value)
{
    if (!_node)
        throw exceptions::MeshExceptions("Mesh Node not available");
    _node->setMaterialFlag(flag, value);
}

bool indie::components::Mesh::applyChanges()
{
    if (_shouldMeshChange) {
        if (_meshFilename.c_str() == nullptr)
            throw exceptions::MeshExceptions("No path for mesh available");
        ECSWrapper ecs;
        irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().getSceneManager();
        if (sceneManager == nullptr)
            throw exceptions::MeshExceptions("no scene manager available");
        _mesh = sceneManager->getMesh(_meshFilename.c_str());
        if (_mesh == nullptr)
            throw exceptions::MeshExceptions("Mesh creation failed");
        _shouldMeshChange = false;
        return true;
    }
    return false;
}

void indie::components::Mesh::changeMesh(const std::string &filename)
{
    if (_node)
        _node->remove();
    _node = nullptr;
    _mesh = nullptr;
    _shouldMeshChange = true;
    _meshFilename = filename;
}

void indie::components::Mesh::addToScene()
{
    if (_node != nullptr)
        return;
    ECSWrapper ecs;
    irr::scene::ISceneManager *sceneManager = ecs.systemManager.getSystem<indie::systems::IrrlichtManagerSystem>().getSceneManager();
    if (sceneManager == nullptr || _mesh == nullptr)
        throw exceptions::MeshExceptions("no scene manager or no mesh available");
    _node = sceneManager->addAnimatedMeshSceneNode(_mesh);
    if (_node == nullptr)
        throw exceptions::MeshExceptions("no Mesh Node available");
    _node->setVisible(true);
}

void indie::components::Mesh::changeVisibility(bool shouldBeSeen)
{
    if (_node == nullptr)
        throw exceptions::MeshExceptions("no Mesh Node available");
    _node->setVisible(shouldBeSeen);
}

irr::scene::IAnimatedMeshSceneNode *indie::components::Mesh::getAnimatedMeshNode()
{
    return _node;
}

std::ostream &indie::components::Mesh::operator<<(std::ostream &file)
{
    file << std::setw(8) << R"(<component type="Mesh">)" << std::endl;
    file << std::setw(12) << R"(<argument name="fileName" value=")" << _meshFilename << R"("/>)" << std::endl;
    file << std::setw(8) << "</component>" << std::endl;
    return file;
}
