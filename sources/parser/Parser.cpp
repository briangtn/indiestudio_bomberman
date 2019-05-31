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
#include <regex>

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
        {(L"Pointlight"), &createPointlight},
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

    for (unsigned int i = 0; _xmlReader->read(); i++) {
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
    for (unsigned int i = 0; _xmlReader->read(); i++) {
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
                    ecs.entityManager.createEntity(currentEntity);
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

}

void indie::Parser::createParticle(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int &line)
{

}

void indie::Parser::createMaterial(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int &line)
{

}

void indie::Parser::createMesh(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                               const std::string &fileName, unsigned int &line)
{

}

void indie::Parser::createPointlight(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                     const std::string &fileName, unsigned int &line)
{

}

void indie::Parser::fillMapArgs(std::map<std::string, std::string> &args, irr::io::IXMLReader *xmlReader, 
                                const std::string &fileName, unsigned int &line, const std::string &from)
{
    ECSWrapper ecs;

    for (; xmlReader->read(); line++) {
        if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            if (irr::core::stringw(L"argument").equals_ignore_case(xmlReader->getNodeName())) {
                std::string name = irr::core::stringc(irr::core::stringw(xmlReader->getAttributeValueSafe(L"name")).c_str()).c_str();
                if (name.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'name' for node 'argument' at line " + std::to_string(line) + " in file " + fileName + ".",
                            from);
                }
                std::string value = irr::core::stringc(irr::core::stringw(xmlReader->getAttributeValueSafe(L"value")).c_str()).c_str();
                if (value.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'value' for node 'argument' at line " + std::to_string(line) + " in file " + fileName + ".",
                            from);
                }
                if (!args.at(name).empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Redefinition of '" + name + "' at line " + std::to_string(line) + " in file " + fileName + ".",
                            from);
                }
                args.at(name) = value;
            } else {
                throw exceptions::ParserInvalidFileException(
                        "Unknown node '" + std::string(irr::core::stringc(irr::core::stringw(xmlReader->getNodeName()).c_str()).c_str())
                        + " at line " + std::to_string(line) + " in file " + fileName + ".", from);
            }


        } else if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT_END) {
            if (!(irr::core::stringw(L"component").equals_ignore_case(xmlReader->getNodeName()))) {
                throw exceptions::ParserInvalidFileException(
                        "Wrong closing node at line " + std::to_string(line) + " in file " + fileName + "(expected 'component' but got '"
                        + irr::core::stringc(irr::core::stringw(xmlReader->getNodeName()).c_str()).c_str() + "').",
                        from);
            }
        } else {
            continue;
        }
    }
}

void indie::Parser::createSound(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {
            {"fileName", ""},
            {"type", ""},
            {"position", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createSound");
    if (args.at("fileName").empty() || args.at("type").empty())
        throw exceptions::ParserInvalidFileException(
                            "Missing mandatory argument in file " + fileName + ".",
                            "indie::Parser::createSound");

    if (args.at("position").empty()) {
        ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::SoundComponent>(
                    args.at("fileName"), getSoundType(args.at("type"), fileName, line));
    } else {
        ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::SoundComponent>(
                    args.at("fileName"), getSoundType(args.at("type"), fileName, line), getVector3D(args.at("position"), fileName, line));
    }
}

void indie::Parser::createTransform(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                    const std::string &fileName, unsigned int &line)
{

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

const indie::maths::Vector3D indie::Parser::getVector3D(const std::string &type, const std::string &fileName,
                                                        unsigned int &line)
{
    float x;
    float y;
    float z;

    size_t n = std::count(type.begin(), type.end(), ',');
    if (n != 2 || type.length() != 5)
        throw exceptions::ParserInvalidFileException(
                "Wrong argument at line " + std::to_string(line) + " in file " + fileName + "(expected 'float, float, float' but got something else",
                "indie::Parser::getVector3d");
    x = std::atof(type.substr(0, 1).c_str());
    y = std::atof(type.substr(2, 1).c_str());
    z = std::atof(type.substr(4, 1).c_str());
    return maths::Vector3D(x, y, z);
}
