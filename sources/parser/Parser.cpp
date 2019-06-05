/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Parser.cpp
*/

/* Created the 27/05/2019 at 16:12 by jbulteau */

#include <iostream>
#include "parser/Parser.hpp"
#include "exceptions/IrrlichtManagerExceptions.hpp"
#include "exceptions/ParserExceptions.hpp"
#include "ECSWrapper.hpp"
#include "scenes/Scene.hpp"
#include "components/SoundComponent.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "systems/IrrklangAudioSystem.hpp"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <regex>
#include "components/Camera.hpp"
#include "components/PointLight.hpp"

const std::map<std::string, irr::video::E_MATERIAL_TYPE> indie::Parser::_materialTypes = {
    {"EMT_SOLID", irr::video::EMT_SOLID},
    {"EMT_SOLID_2_LAYER", irr::video::EMT_SOLID_2_LAYER},
    {"EMT_LIGHTMAP", irr::video::EMT_LIGHTMAP},
    {"EMT_LIGHTMAP_ADD", irr::video::EMT_LIGHTMAP_ADD},
    {"EMT_LIGHTMAP_M2", irr::video::EMT_LIGHTMAP_M2},
    {"EMT_LIGHTMAP_M4", irr::video::EMT_LIGHTMAP_M4},
    {"EMT_LIGHTMAP_LIGHTING", irr::video::EMT_LIGHTMAP_LIGHTING},
    {"EMT_LIGHTMAP_LIGHTING_M2", irr::video::EMT_LIGHTMAP_LIGHTING_M2},
    {"EMT_LIGHTMAP_LIGHTING_M4", irr::video::EMT_LIGHTMAP_LIGHTING_M4},
    {"EMT_DETAIL_MAP", irr::video::EMT_DETAIL_MAP},
    {"EMT_SPHERE_MAP", irr::video::EMT_SPHERE_MAP},
    {"EMT_REFLECTION_2_LAYER", irr::video::EMT_REFLECTION_2_LAYER},
    {"EMT_TRANSPARENT_ADD_COLOR", irr::video::EMT_TRANSPARENT_ADD_COLOR},
    {"EMT_TRANSPARENT_ALPHA_CHANNEL", irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL},
    {"EMT_TRANSPARENT_ALPHA_CHANNEL_REF", irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF},
    {"EMT_TRANSPARENT_VERTEX_ALPHA", irr::video::EMT_TRANSPARENT_VERTEX_ALPHA},
    {"EMT_TRANSPARENT_REFLECTION_2_LAYER", irr::video::EMT_TRANSPARENT_REFLECTION_2_LAYER},
    {"EMT_NORMAL_MAP_SOLID", irr::video::EMT_NORMAL_MAP_SOLID},
    {"EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR", irr::video::EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR},
    {"EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA", irr::video::EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA},
    {"EMT_PARALLAX_MAP_SOLID", irr::video::EMT_PARALLAX_MAP_SOLID},
    {"EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR", irr::video::EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR},
    {"EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA", irr::video::EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA},
    {"EMT_ONETEXTURE_BLEND", irr::video::EMT_ONETEXTURE_BLEND}
};

const std::map<std::string, irr::video::E_MATERIAL_FLAG> indie::Parser::_materialFlags = {
        {"EMF_WIREFRAME", irr::video::EMF_WIREFRAME},
        {"EMF_POINTCLOUD", irr::video::EMF_POINTCLOUD},
        {"EMF_GOURAUD_SHADING", irr::video::EMF_GOURAUD_SHADING},
        {"EMF_LIGHTING", irr::video::EMF_LIGHTING},
        {"EMF_ZBUFFER", irr::video::EMF_ZBUFFER},
        {"EMF_ZWRITE_ENABLE", irr::video::EMF_ZWRITE_ENABLE},
        {"EMF_BACK_FACE_CULLING", irr::video::EMF_BACK_FACE_CULLING},
        {"EMF_FRONT_FACE_CULLING", irr::video::EMF_FRONT_FACE_CULLING},
        {"EMF_BILINEAR_FILTER", irr::video::EMF_BILINEAR_FILTER},
        {"EMF_TRILINEAR_FILTER", irr::video::EMF_TRILINEAR_FILTER},
        {"EMF_ANISOTROPIC_FILTER", irr::video::EMF_ANISOTROPIC_FILTER},
        {"EMF_FOG_ENABLE", irr::video::EMF_FOG_ENABLE},
        {"EMF_NORMALIZE_NORMALS", irr::video::EMF_NORMALIZE_NORMALS},
        {"EMF_TEXTURE_WRAP", irr::video::EMF_TEXTURE_WRAP},
        {"EMF_ANTI_ALIASING", irr::video::EMF_ANTI_ALIASING},
        {"EMF_COLOR_MASK", irr::video::EMF_COLOR_MASK},
        {"EMF_COLOR_MATERIAL", irr::video::EMF_COLOR_MATERIAL},
        {"EMF_USE_MIP_MAPS", irr::video::EMF_USE_MIP_MAPS},
        {"EMF_BLEND_OPERATION", irr::video::EMF_BLEND_OPERATION},
        {"EMF_POLYGON_OFFSET", irr::video::EMF_POLYGON_OFFSET}
};

indie::Parser::Parser()
    : _device(irr::createDevice(irr::video::EDT_NULL))
    , _xmlReader(nullptr)
    , _scenes()
    , _systems({
        {(L"IrrlichtManager"), &createIrrlichtManager},
        {(L"IrrklangAudio"), &createIrrklangAudio}
    })
    , _components({
        {(L"Camera"), &createCamera},
        {(L"Particle"), &createParticle},
        {(L"Material"), &createMaterial},
        {(L"Mesh"), &createMesh},
        {(L"Sound"), &createSound},
        {(L"Transform"), &createTransform}
    })
{
    if (!_device)
        throw indie::exceptions::IrrlichtManagerDeviceException("Failed to create device.", "indie::Parser::Parser");
}

indie::Parser::~Parser()
{
    _device->closeDevice();
    _device->drop();
}

indie::Parser &indie::Parser::getInstance()
{
    static Parser parser;
    return parser;
}

void indie::Parser::loadSystems(const std::string &fileName)
{
    bool ecs = false;

    _xmlReader = _device->getFileSystem()->createXMLReader(fileName.c_str());
    if (!_xmlReader)
        throw indie::exceptions::ParserDeviceException("Failed to create XML reader.", "indie::Parser::loadSystems");

    for (unsigned int i = 1; _xmlReader->read(); i++) {
            if (_xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
                if (irr::core::stringw(L"ecs").equals_ignore_case(_xmlReader->getNodeName())) {
                    if (ecs) {
                        throw exceptions::ParserInvalidFileException(
                                "Node 'ecs' reopened inside node 'ecs' at line " + std::to_string(i) + " in file " + fileName + ".",
                                "indie::Parser::loadSystems");
                    } else {
                        ecs = true;
                    }
                } else if (irr::core::stringw(L"system").equals_ignore_case(_xmlReader->getNodeName())) {
                    if (!ecs) {
                        throw exceptions::ParserInvalidFileException(
                                "Node 'system' outside 'ecs' at line " + std::to_string(i) + " in file " + fileName + ".",
                                "indie::Parser::loadSystems");
                    } else {
                        irr::core::stringw type = _xmlReader->getAttributeValueSafe(L"type");
                        if (type.empty()) {
                            throw exceptions::ParserInvalidFileException(
                                    "Missing attribute 'type' for node 'system' at line " + std::to_string(i) + " in file " + fileName + ".",
                                    "indie::Parser::loadSystems");
                        } else {
                            _systems.at(type)(_xmlReader, fileName, i);
                        }
                    }
                } else if (irr::core::stringw(L"argument").equals_ignore_case(_xmlReader->getNodeName())) {
                    throw exceptions::ParserInvalidFileException(
                            "Node 'argument' outside 'system' at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadSystems");
                } else {

                }
            } else if (_xmlReader->getNodeType() == irr::io::EXN_ELEMENT_END) {
                if (irr::core::stringw(L"ecs").equals_ignore_case(_xmlReader->getNodeName())) {
                    ecs = false;
                } else if (irr::core::stringw(L"system").equals_ignore_case(_xmlReader->getNodeName())) {
                    throw exceptions::ParserInvalidFileException(
                            "Closing node 'system' but none has been opened, at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadSystems");
                } else if (irr::core::stringw(L"argument").equals_ignore_case(_xmlReader->getNodeName())) {
                    throw exceptions::ParserInvalidFileException(
                            "Closing node 'argument' but none has been opened, at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadSystems");
                } else {
                    throw exceptions::ParserInvalidFileException(
                            "Unknown closing node '" + std::string(irr::core::stringc(irr::core::stringw(_xmlReader->getNodeName()).c_str()).c_str())
                            + "' at line " + std::to_string(i) + " in file " + fileName + ".", "indie::Parser::loadSystems");
                }
            } else {
                continue;
            }
    }
    _xmlReader->drop();
    _xmlReader = nullptr;
}

const std::vector<std::pair<std::string, indie::scenes::IScene *>> &indie::Parser::loadScenes(const std::string &pathToFolder)
{
    boost::filesystem::path path(pathToFolder);
    boost::filesystem::directory_iterator start(path);
    boost::filesystem::directory_iterator end;
    std::for_each(start, end, [&](const boost::filesystem::directory_entry &entry) {
        std::string fileName = entry.path().leaf().string();
        std::regex regex(".*\\.xml$");
        if (std::regex_search(fileName, regex))
            _scenes.emplace_back(std::pair<std::string, scenes::IScene *>(fileName.substr(0, fileName.length() - 4), new scenes::Scene(fileName)));
    });
    return _scenes;
}

void indie::Parser::loadScene(const std::string &fileName)
{
    ECSWrapper ecs;
    std::string currentEntity;
    bool scene = false;

    _xmlReader = _device->getFileSystem()->createXMLReader(fileName.c_str());
    if (!_xmlReader) {
        throw indie::exceptions::ParserDeviceException("Failed to create XML reader.", "indie::Parser::loadScene");
    }
    for (unsigned int i = 1; _xmlReader->read(); i++) {
        if (_xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            if (irr::core::stringw(L"scene").equals_ignore_case(_xmlReader->getNodeName())) {
                if (scene) {
                    throw exceptions::ParserInvalidFileException(
                            "Node 'scene' reopened inside node 'scene' at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadScene");
                } else {
                    scene = true;
                }
            } else if (irr::core::stringw(L"entity").equals_ignore_case(_xmlReader->getNodeName())) {
                if (!scene) {
                    throw exceptions::ParserInvalidFileException(
                            "Node 'entity' outside 'scene' at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadScene");
                }
                irr::core::stringw name = _xmlReader->getAttributeValueSafe(L"name");
                if (name.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'name' for node 'entity' at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadScene");
                } else {
                    currentEntity = irr::core::stringc(name.c_str()).c_str();
                    auto entity = ecs.entityManager.createEntity(currentEntity);
                    irr::core::stringw shouldBeKeeped = _xmlReader->getAttributeValueSafe(L"shouldBeKeeped");
                    if (shouldBeKeeped.empty() || std::string(irr::core::stringc(shouldBeKeeped.c_str()).c_str()) == "false") {
                        entity->setShouldBeKeeped(false);
                    } else if (std::string(irr::core::stringc(shouldBeKeeped.c_str()).c_str()) == "true") {
                        entity->setShouldBeKeeped(true);
                    } else {
                        throw exceptions::ParserInvalidFileException(
                                "Invalid value for attribute 'shouldBeKeeped', expected 'true' or 'false', but got '"
                                + std::string(irr::core::stringc(shouldBeKeeped.c_str()).c_str()) + "' at line "
                                + std::to_string(i) + " in file " + fileName + ".", "indie::Parser::loadScene");
                    }
                }
            } else if (irr::core::stringw(L"component").equals_ignore_case(_xmlReader->getNodeName())) {
                if (currentEntity.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Node 'component' outside 'entity' at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadScene");
                }
                irr::core::stringw type = _xmlReader->getAttributeValueSafe(L"type");
                if (type.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'type' for node 'component' at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadScene");
                } else {
                    _components.at(type)(currentEntity, _xmlReader, fileName, i);
                }
            } else if (irr::core::stringw(L"argument").equals_ignore_case(_xmlReader->getNodeName())) {
                throw exceptions::ParserInvalidFileException(
                        "Node 'argument' outside 'component' at line " + std::to_string(i) + " in file " + fileName + ".",
                        "indie::Parser::loadScene");
            } else {
                throw exceptions::ParserInvalidFileException(
                        "Unknown node '" + std::string(irr::core::stringc(irr::core::stringw(_xmlReader->getNodeName()).c_str()).c_str())
                        + " at line " + std::to_string(i) + " in file " + fileName + ".", "indie::Parser::loadScene");
            }
        } else if (_xmlReader->getNodeType() == irr::io::EXN_ELEMENT_END) {
            if (irr::core::stringw(L"scene").equals_ignore_case(_xmlReader->getNodeName())) {
                if (!currentEntity.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Closing node 'scene' while node 'entity' is still opened, at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadScene");
                } else {
                    scene = false;
                }
            } else if (irr::core::stringw(L"entity").equals_ignore_case(_xmlReader->getNodeName())) {
                if (!currentEntity.empty()) {
                    currentEntity.clear();
                } else {
                    throw exceptions::ParserInvalidFileException(
                            "Closing node 'entity' but none has been opened, at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadScene");
                }
            } else if (irr::core::stringw(L"component").equals_ignore_case(_xmlReader->getNodeName())) {
                throw exceptions::ParserInvalidFileException(
                        "Closing node 'component' but none has been opened, at line " + std::to_string(i) + " in file " + fileName + ".",
                        "indie::Parser::loadScene");
            } else if (irr::core::stringw(L"argument").equals_ignore_case(_xmlReader->getNodeName())) {
                throw exceptions::ParserInvalidFileException(
                        "Closing node 'argument' but none has been opened, at line " + std::to_string(i) + " in file " + fileName + ".",
                        "indie::Parser::loadScene");
            } else {
                throw exceptions::ParserInvalidFileException(
                        "Unknown closing node '" + std::string(irr::core::stringc(irr::core::stringw(_xmlReader->getNodeName()).c_str()).c_str())
                        + "' at line " + std::to_string(i) + " in file " + fileName + ".", "indie::Parser::loadScene");
            }
        } else {
            continue;
        }
    }
    _xmlReader->drop();
    _xmlReader = nullptr;
}

void indie::Parser::createIrrlichtManager(irr::io::IXMLReader *xmlReader, const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;

    for (; xmlReader->read(); line++) {
        if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            throw exceptions::ParserInvalidFileException(
                    "Node 'system' of type 'IrrlichtManager' does not required subnodes, at line "
                    + std::to_string(line) + " in file " + fileName + ".", "indie::Parser::createIrrlichtManager");
        } else if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT_END) {
            if (irr::core::stringw(L"system").equals_ignore_case(xmlReader->getNodeName())) {
                ecs.systemManager.addSystem<systems::IrrlichtManagerSystem>();
                ecs.systemManager.startSystem<systems::IrrlichtManagerSystem>();
                break;
            } else {
                throw exceptions::ParserInvalidFileException(
                        "Wrong closing node at line " + std::to_string(line) + " in file " + fileName + "(expected 'system' but got '"
                        + irr::core::stringc(irr::core::stringw(xmlReader->getNodeName()).c_str()).c_str() + "').",
                        "indie::Parser::createIrrlichtManager");
            }
        } else {
            continue;
        }
    }
}

void indie::Parser::createIrrklangAudio(irr::io::IXMLReader *xmlReader, const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;

    for (; xmlReader->read(); line++) {
        if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            throw exceptions::ParserInvalidFileException(
                    "Node 'system' of type 'IrrklangAudio' does not required subnodes, at line "
                    + std::to_string(line) + " in file " + fileName + ".", "indie::Parser::createIrrklangAudio");
        } else if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT_END) {
            if (irr::core::stringw(L"system").equals_ignore_case(xmlReader->getNodeName())) {
                ecs.systemManager.addSystem<systems::IrrklangAudioSystem>();
                ecs.systemManager.startSystem<systems::IrrklangAudioSystem>();
                break;
            } else {
                throw exceptions::ParserInvalidFileException(
                        "Wrong closing node at line " + std::to_string(line) + " in file " + fileName + "(expected 'system' but got '"
                        + irr::core::stringc(irr::core::stringw(xmlReader->getNodeName()).c_str()).c_str() + "').",
                        "indie::Parser::createIrrklangAudio");
            }
        } else {
            continue;
        }
    }
}

void indie::Parser::createCamera(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                 const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {
            {"FOV", ""}
    };

    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createCamera");
    if (args["FOV"].empty()) {
        ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::Camera>();
    } else {
        ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::Camera>(
                std::atof(args["FOV"].c_str()));
    }
}

void indie::Parser::createMaterial(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int &line)
{
    fflush(stdout);
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {
            {"fileName", ""},
            {"type", ""},
            {"flags", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createMaterial");
    if (args["fileName"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument in file " + fileName + ".", "indie::Parser::createMaterial");
    }
    jf::components::ComponentHandler<components::Material> component;
    if (args["type"].empty()) {
        component = ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::Material>(
                args["type"]);
    } else {
         component = ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::Material>(
                args["name"], getMaterialType(args["type"]));
    }
    if (!args["flags"].empty()) {
        std::vector<std::string> flags;
        boost::split(flags, args["flags"], [](char c){ return c == ';'; });
        for (auto &it : flags) {
            if (it[0] == '!') {
                component->setMaterialFlag(getMaterialFlag(&it[1]), false);
            } else {
                component->setMaterialFlag(getMaterialFlag(it), true);
            }
        }
    }
}

void indie::Parser::createMesh(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                               const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {
            {"fileName", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createTransform");
    if (args["fileName"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument in file " + fileName + ".", "indie::Parser::createMesh");
    }
    ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::Mesh>(
        args["fileName"]);
}

void indie::Parser::createParticle(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {
            {"name",        ""},
            {"fileName",    ""},
            {"layer",       ""},
            {"position",    ""},
            {"scale",       ""},
            {"rotation",    ""},
            {"emitterSize", ""},
            {"direction",   ""},
            {"emitRate",    ""},
            {"brightColor", ""},
            {"age",         ""},
            {"angle",       ""},
            {"size",        ""},
            {"fadeColor",   ""},
            {"fadeTime",    ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createParticle");
    if (args["name"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument in file " + fileName + ".", "indie::Parser::createParticle");
    }
    auto component = ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::Particle>(
        args["name"]);
    if (!args["fileName"].empty() && !args["layer"].empty()) {
        component->setTexture(std::atoi(args["layer"].c_str()), args["fileName"]);
    } else if (!args["fileName"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing argument 'layer' for texture setting for component 'Particle' at line "
                + std::to_string(line) + " in file " + fileName + ".", "indie::Parser::createParticle");
    } else if (!args["layer"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing argument 'fileName' for texture setting for component 'Particle' at line "
                + std::to_string(line) + " in file " + fileName + ".", "indie::Parser::createParticle");
    }
    if (!args["position"].empty()) {
        component->setPosition(getVector3D(args["position"], fileName, line));
    }
    if (!args["scale"].empty()) {
        component->setScale(getVector3D(args["scale"], fileName, line));
    }
    if (!args["rotation"].empty()) {
        component->setRotation(getVector3D(args["rotation"], fileName, line));
    }
    if (!args["emitterSize"].empty()) {
        component->setEmitterSize(irr::core::aabbox3d<irr::f32>(
                getVector3D(args["emitterSize"].substr(0, args["emitterSize"].find(';')), fileName, line),
                getVector3D(args["emitterSize"].substr(args["emitterSize"].find(';') + 1), fileName, line)));
    }
    if (!args["direction"].empty()) {
        component->setInitialDirection(getVector3D(args["direction"], fileName, line));
    }
    if (!args["emitRate"].empty()) {
        component->setEmitRate(std::make_pair(std::atoi(args["emitRate"].substr(0, args["emitRate"].find(',')).c_str()),
                std::atoi(args["emitRate"].substr(args["emitRate"].find(',') + 1).c_str())));
    }
    if (!args["brightColor"].empty()) {
        component->setDarkBrightColor(std::make_pair(
                getColor(args["brightColor"].substr(0, args["brightColor"].find(';')), fileName, line),
                getColor(args["brightColor"].substr(args["brightColor"].find(';') + 1), fileName, line)));
    }
    if (!args["age"].empty()) {
        component->setMinMaxAge(std::make_pair(std::atoi(args["age"].substr(0, args["emitRate"].find(',')).c_str()),
                std::atoi(args["age"].substr(args["age"].find(',') + 1).c_str())));
    }
    if (!args["angle"].empty()) {
        component->setAngle(std::atoi(args["angle"].c_str()));
    }
    if (!args["size"].empty()) {
        component->setMinMaxSize(std::make_pair(
                getVector2D(args["size"].substr(0, args["size"].find(';')), fileName, line),
                getVector2D(args["size"].substr(args["size"].find(';') + 1), fileName, line)));
    }
    if (!args["fadeColor"].empty()) {
        component->setFadeColor(getColor(args["fadeColor"], fileName, line));
    }
    if (!args["fadeTime"].empty()) {
        component->setFadeTime(std::atoi(args["fadeTime"].c_str()));
    }
}

void indie::Parser::createSound(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {
            {"fileName", ""},
            {"type",     ""},
            {"position", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createSound");
    if (args["fileName"].empty() || args["type"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument in file " + fileName + ".", "indie::Parser::createSound");
    }
    if (args["position"].empty()) {
        ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::SoundComponent>(
                args["fileName"], getSoundType(args["type"], fileName, line));
    } else {
        ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::SoundComponent>(
                args["fileName"], getSoundType(args["type"], fileName, line),
                getVector3D(args["position"], fileName, line));
    }
}

void indie::Parser::createTransform(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                    const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {
            {"position", ""},
            {"rotation", ""},
            {"scale",    ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createTransform");
    if (args["position"].empty()) {
        args["position"] = "0,0,0";
    }
    if (args["rotation"].empty()) {
        args["rotation"] = "0,0,0";
    }
    if (args["scale"].empty()) {
        args["scale"] = "1,1,1";
    }
    ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::Transform>(
            getVector3D(args["position"], fileName, line), getVector3D(args["rotation"], fileName, line),
            getVector3D(args["scale"], fileName, line));
}

void indie::Parser::fillMapArgs(std::map<std::string, std::string> &args, irr::io::IXMLReader *xmlReader,
                                const std::string &fileName, unsigned int &line, const std::string &callingMethod)
{
    for (; xmlReader->read(); line++) {
        if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            if (irr::core::stringw(L"argument").equals_ignore_case(xmlReader->getNodeName())) {
                std::string name = irr::core::stringc(irr::core::stringw(xmlReader->getAttributeValueSafe(L"name")).c_str()).c_str();
                if (name.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'name' for node 'argument' at line " + std::to_string(line) + " in file " + fileName + ".",
                            callingMethod);
                }
                std::string value = irr::core::stringc(irr::core::stringw(xmlReader->getAttributeValueSafe(L"value")).c_str()).c_str();
                value.erase(remove_if(value.begin(), value.end(), isspace), value.end());
                if (value.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'value' for node 'argument' at line " + std::to_string(line) + " in file " + fileName + ".",
                            callingMethod);
                }
                if (!args.at(name).empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Redefinition of '" + name + "' at line " + std::to_string(line) + " in file " + fileName + ".",
                            callingMethod);
                }
                args.at(name) = value;
            } else {
                throw exceptions::ParserInvalidFileException(
                        "Unknown node '" + std::string(irr::core::stringc(irr::core::stringw(xmlReader->getNodeName()).c_str()).c_str())
                        + " at line " + std::to_string(line) + " in file " + fileName + ".", callingMethod);
            }
        } else if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT_END) {
            if (!(irr::core::stringw(L"component").equals_ignore_case(xmlReader->getNodeName()))) {
                throw exceptions::ParserInvalidFileException(
                        "Wrong closing node at line " + std::to_string(line) + " in file " + fileName + "(expected 'component' but got '"
                        + irr::core::stringc(irr::core::stringw(xmlReader->getNodeName()).c_str()).c_str() + "').",
                        callingMethod);
            }
            line++;
            return;
        } else {
            continue;
        }
    }
}

irr::video::E_MATERIAL_TYPE indie::Parser::getMaterialType(const std::string &type)
{
    return _materialTypes.at(type);
}

irr::video::E_MATERIAL_FLAG indie::Parser::getMaterialFlag(const std::string &flag)
{
    return _materialFlags.at(flag);
}

const indie::components::SoundComponent::SoundType indie::Parser::getSoundType(const std::string &type, const std::string &fileName,
                                                                               unsigned int &line)
{
    if (type == "MUSIC") {
        return components::SoundComponent::MUSIC;
    } else if (type == "EFFECT") {
        return components::SoundComponent::EFFECT;
    } else {
        throw exceptions::ParserInvalidFileException(
                "Invalid type for component 'Sound' at line + " + std::to_string(line) + " in file " + fileName + ".",
                "indie::Parser::getSoundType");
    }
}

const indie::maths::Vector2D indie::Parser::getVector2D(const std::string &value, const std::string &fileName,
                                                        unsigned int &line)
{
    float x, y;

    size_t n = std::count(value.begin(), value.end(), ',');
    if (n != 1) {
        throw exceptions::ParserInvalidFileException(
                "Wrong argument at line " + std::to_string(line) + " in file " + fileName
                + "(expected 'float, float' but got something else.", "indie::Parser::getVector2D");
    }
    auto pos = value.find(',');
    x = std::atof(value.substr(0, pos).c_str());
    y = std::atof(value.substr(pos + 1).c_str());
    return indie::maths::Vector2D(x, y);
}

const indie::maths::Vector3D indie::Parser::getVector3D(const std::string &value, const std::string &fileName,
                                                        unsigned int &line)
{
    float x, y, z;

    size_t n = std::count(value.begin(), value.end(), ',');
    if (n != 2) {
        throw exceptions::ParserInvalidFileException(
                "Wrong argument at line " + std::to_string(line) + " in file " + fileName
                + "(expected 'float, float, float' but got something else.", "indie::Parser::getVector3D");
    }
    auto pos = value.find(',');
    x = std::atof(value.substr(0, pos).c_str());
    auto newPos = value.find(',', pos + 1);
    y = std::atof(value.substr(pos + 1, newPos - (pos + 1)).c_str());
    pos = newPos;
    z = std::atof(value.substr(pos + 1).c_str());
    return maths::Vector3D(x, y, z);
}

const irr::video::SColor indie::Parser::getColor(const std::string &value, const std::string &fileName,
                                                 unsigned int &line)
{
    int a, r, g, b;

    size_t n = std::count(value.begin(), value.end(), ',');
    if (n != 3) {
        throw exceptions::ParserInvalidFileException(
                "Wrong argument at line " + std::to_string(line) + " in file " + fileName
                + "(expected 'int, int, int, int' but got something else.", "indie::Parser::getColor");
    }
    auto pos = value.find(',');
    a = std::atoi(value.substr(0, pos).c_str());
    auto newPos = value.find(',', pos + 1);
    r = std::atoi(value.substr(pos + 1, newPos - (pos + 1)).c_str());
    pos = newPos;
    newPos = value.find(',', pos + 1);
    g = std::atoi(value.substr(pos + 1, newPos - (pos + 1)).c_str());
    pos = newPos;
    b = std::atoi(value.substr(pos + 1).c_str());
    return irr::video::SColor(a, r, g, b);
}
