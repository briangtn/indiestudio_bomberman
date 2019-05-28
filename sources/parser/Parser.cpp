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
#include <boost/filesystem.hpp>
#include <regex>

indie::Parser::Parser()
    : _device(irr::createDevice(irr::video::EDT_NULL)), _xmlReader(nullptr), _scenes(), _components({
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
    irr::core::stringw path(fileName.c_str());
    std::string currentEntity;

    _xmlReader = _device->getFileSystem()->createXMLReader(path);
    if (!_xmlReader)
        throw indie::exceptions::ParserDeviceException("Failed to create XML reader.", "indie::Parser::loadScene");

    for (unsigned int i = 0; _xmlReader->read(); i++) {
        if (_xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            if (irr::core::stringw(L"entity").equals_ignore_case(_xmlReader->getNodeName())) {
                irr::core::stringw key = _xmlReader->getAttributeValueSafe(L"name");
                if (key.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'name' for node 'entity' at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadScene");
                } else {
                    currentEntity = irr::core::stringc(key.c_str()).c_str();
                    ecs.entityManager.createEntity(currentEntity);
                }
            } else if (irr::core::stringw(L"component").equals_ignore_case(_xmlReader->getNodeName())) {
                if (currentEntity.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Node 'component' outside 'entity' at line " + std::to_string(i) + "in file " + fileName + ".",
                            "indie::Parser::loadScene");
                }
                irr::core::stringw key = _xmlReader->getAttributeValueSafe(L"type");
                if (key.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'type' for node 'component' at line " + std::to_string(i) + "in file " + fileName + ".",
                            "indie::Parser::loadScene");
                } else {
                    _components[key](currentEntity, _xmlReader, fileName, i);
                }
            } else if (irr::core::stringw(L"argument").equals_ignore_case(_xmlReader->getNodeName())) {
                //TODO argument
            }
        }
    }
}

void indie::Parser::createCamera(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                 const std::string &fileName, unsigned int line)
{

}

void indie::Parser::createParticle(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int line)
{

}

void indie::Parser::createMaterial(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int line)
{

}

void indie::Parser::createMesh(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                               const std::string &fileName, unsigned int line)
{

}

void indie::Parser::createPointlight(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                     const std::string &fileName, unsigned int line)
{

}



void indie::Parser::createSound(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                const std::string &fileName, unsigned int line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {
            {"fileName", ""},
            {"type", ""},
            {"position", ""}
    };

    for (; xmlReader->read(); line++) {
        if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            if (irr::core::stringw(L"argument").equals_ignore_case(xmlReader->getNodeName())) {
                std::string name = irr::core::stringc(static_cast<irr::core::stringw>(xmlReader->getAttributeValueSafe(L"name")).c_str()).c_str();
                if (name.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'name' for node 'argument' at line " + std::to_string(line) + " in file " + fileName + ".",
                            "indie::Parser::createSound");
                }
                std::string value = irr::core::stringc(static_cast<irr::core::stringw>(xmlReader->getAttributeValueSafe(L"value")).c_str()).c_str();
                if (value.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'value' for node 'argument' at line " + std::to_string(line) + " in file " + fileName + ".",
                            "indie::Parser::createSound");
                }
                if (!args.at(name).empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Redefinition of '" + name + "' at line " + std::to_string(line) + " in file " + fileName + ".",
                            "indie::Parser::createSound");
                }
                args.at(name) = value;
            }
        } else if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT_END) {
            if (irr::core::stringw(L"component").equals_ignore_case(xmlReader->getNodeName())) {
                if (args.at("position").empty()) {
                    ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::SoundComponent>(args.at("fileName"), getSoundType(args.at("type"), fileName, line));
                } else {
                    ecs.entityManager.getEntitiesByName(entityName)[0]->assignComponent<components::SoundComponent>(args.at("fileName"), getSoundType(args.at("type"), fileName, line), getVector3D(args.at("position"), fileName, line));
                }
            } else {
                throw exceptions::ParserInvalidFileException(
                        "Wrong closing node at line " + std::to_string(line) + " in file " + fileName + "(expected 'component' but got '"
                        + irr::core::stringc(static_cast<irr::core::stringw>(xmlReader->getNodeName()).c_str()).c_str() + "'.",
                        "indie::Parser::createSound");
            }
        }
    }
}

void indie::Parser::createTransform(const std::string &entityName, irr::io::IXMLReader *xmlReader,
                                    const std::string &fileName, unsigned int line)
{

}

const indie::components::SoundComponent::SoundType indie::Parser::getSoundType(const std::string &type, const std::string &fileName,
                                                                               unsigned int line)
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
                                                         unsigned int line)
{
    return maths::Vector3D(0,0,0);
}
