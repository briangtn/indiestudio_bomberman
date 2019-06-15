/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Parser.cpp
*/

/* Created the 27/05/2019 at 16:12 by jbulteau */

#include <iostream>
#include <regex>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "parser/Parser.hpp"
#include "exceptions/IrrlichtManagerExceptions.hpp"
#include "exceptions/ParserExceptions.hpp"
#include "Exceptions.hpp"
#include "ECSWrapper.hpp"
#include "components/SoundComponent.hpp"
#include "systems/AISystem.hpp"
#include "systems/IrrlichtManagerSystem.hpp"
#include "systems/IrrklangAudioSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/TauntSystem.hpp"
#include "components/Camera.hpp"
#include "components/PointLight.hpp"
#include "components/Hoverer.hpp"
#include "components/AIController.hpp"
#include "components/Rotator.hpp"
#include "components/PlayerController.hpp"
#include "systems/BonusSystem.hpp"
#include "systems/BombManagerSystem.hpp"
#include "systems/DestroyOnTimeSystem.hpp"
#include "components/GUI/Font.hpp"
#include "components/GUI/Image.hpp"
#include "components/DynamicCamera.hpp"
#include "components/PlayerAlive.hpp"
#include "components/LeaderBoard.hpp"
#include "systems/LiveSystem.hpp"

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

const std::map<std::string, indie::components::BonusType> indie::Parser::_bonusTypes = {
        {"BONUS_T_BOMB_UP", indie::components::BONUS_T_BOMB_UP},
        {"BONUS_T_SPEED_UP", indie::components::BONUS_T_SPEED_UP},
        {"BONUS_T_FIRE_UP", indie::components::BONUS_T_FIRE_UP},
        {"BONUS_T_WALL_PASS", indie::components::BONUS_T_WALL_PASS},
        {"BONUS_T_NB", indie::components::BONUS_T_NB}
};

const std::map<std::string, indie::components::Text::VerticalAlignement> indie::Parser::_verticalAlignements = {
        {"TOP", indie::components::Text::TOP},
        {"MIDDLE", indie::components::Text::MIDDLE},
        {"BOTTOM", indie::components::Text::BOTTOM},
};

const std::map<std::string, indie::components::Text::HorizontalAlignement> indie::Parser::_horizontalAlignements = {
        {"LEFT", indie::components::Text::LEFT},
        {"CENTER", indie::components::Text::CENTER},
        {"RIGHT", indie::components::Text::RIGHT},
};

indie::Parser::Parser()
    : _device(irr::createDevice(irr::video::EDT_NULL))
    , _xmlReader(nullptr)
    , _scenes()
    , _systems({
        {(L"BombManager"), &createBombManager},
        {(L"Bonus"), &createBonus},
        {(L"DestroyManager"), &createDestroyManager},
        {(L"IrrlichtManager"), &createIrrlichtManager},
        {(L"IrrklangAudio"), &createIrrklangAudio},
        {(L"Live"), &createLive},
        {(L"Movement"), &createMovement},
        {(L"Taunt"), &createTaunt},
        {(L"AI"), &createAI}
    })
    , _components({
        {(L"AIController"), &createAIController},
        {(L"Animator"), &createAnimator},
        {(L"Bomb"), &createBomb},
        {(L"BonusEffector"), &createBonusEffector},
        {(L"BonusSpawner"), &createBonusSpawner},
        {(L"BoxCollider"), &createBoxCollider},
        {(L"Button"), &createButton},
        {(L"Camera"), &createCamera},
        {(L"Destroy"), &createDestroy},
        {(L"DynamicCamera"), &createDynamicCamera},
        {(L"Font"), &createFont},
        {(L"Hoverer"), &createHoverer},
        {(L"Image"), &createImage},
        {(L"LeaderBoard"), &createLeaderBoard},
        {(L"Particle"), &createParticle},
        {(L"PlayerAlive"), &createPlayerAlive},
        {(L"PlayerController"), &createPlayerController},
        {(L"Material"), &createMaterial},
        {(L"Mesh"), &createMesh},
        {(L"MoveToTarget"), &createMoveToTarget},
        {(L"Rotator"), &createRotator},
        {(L"Sound"), &createSound},
        {(L"Text"), &createText},
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
                                "Node 'ecs' reopened inside node 'ecs' at line " + std::to_string(i) + " in file "
                                + fileName + ".", "indie::Parser::loadSystems");
                    } else {
                        ecs = true;
                    }
                } else if (irr::core::stringw(L"system").equals_ignore_case(_xmlReader->getNodeName())) {
                    if (!ecs) {
                        throw exceptions::ParserInvalidFileException(
                                "Node 'system' outside 'ecs' at line " + std::to_string(i) + " in file "
                                + fileName + ".", "indie::Parser::loadSystems");
                    } else {
                        irr::core::stringw type = _xmlReader->getAttributeValueSafe(L"type");
                        if (type.empty()) {
                            throw exceptions::ParserInvalidFileException(
                                    "Missing attribute 'type' for node 'system' at line " + std::to_string(i)
                                    + " in file " + fileName + ".", "indie::Parser::loadSystems");
                        } else {
                            _systems.at(type)(_xmlReader, fileName, i);
                        }
                    }
                } else if (irr::core::stringw(L"argument").equals_ignore_case(_xmlReader->getNodeName())) {
                    throw exceptions::ParserInvalidFileException(
                            "Node 'argument' outside 'system' at line " + std::to_string(i) + " in file "
                            + fileName + ".", "indie::Parser::loadSystems");
                } else {

                }
            } else if (_xmlReader->getNodeType() == irr::io::EXN_ELEMENT_END) {
                if (irr::core::stringw(L"ecs").equals_ignore_case(_xmlReader->getNodeName())) {
                    ecs = false;
                } else if (irr::core::stringw(L"system").equals_ignore_case(_xmlReader->getNodeName())) {
                    throw exceptions::ParserInvalidFileException(
                            "Closing node 'system' but none has been opened, at line " + std::to_string(i)
                            + " in file " + fileName + ".", "indie::Parser::loadSystems");
                } else if (irr::core::stringw(L"argument").equals_ignore_case(_xmlReader->getNodeName())) {
                    throw exceptions::ParserInvalidFileException(
                            "Closing node 'argument' but none has been opened, at line " + std::to_string(i)
                            + " in file " + fileName + ".", "indie::Parser::loadSystems");
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
            _scenes.emplace_back(std::pair<std::string, scenes::IScene *>(
                    fileName.substr(0, fileName.length() - 4), new scenes::Scene(fileName)));
    });
    return _scenes;
}

indie::scenes::IScene *indie::Parser::loadSingleScene(const std::string &name, const std::string &path)
{
    indie::scenes::IScene *scene =  new scenes::Scene(path);

    _scenes.emplace_back(std::pair<std::string, scenes::IScene *>(name, scene));
    return scene;
}

void indie::Parser::loadScene(const std::string &fileName)
{
    ECSWrapper ecs;
    std::string currentEntity;
    jf::entities::EntityHandler entity;
    bool sceneNode = false;

    _xmlReader = _device->getFileSystem()->createXMLReader(fileName.c_str());
    if (!_xmlReader) {
        throw indie::exceptions::ParserDeviceException("Failed to create XML reader.", "indie::Parser::loadScene");
    }
    for (unsigned int i = 1; _xmlReader->read(); i++) {
        if (_xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            if (irr::core::stringw(L"scene").equals_ignore_case(_xmlReader->getNodeName())) {
                if (sceneNode) {
                    throw exceptions::ParserInvalidFileException(
                            "Node 'scene' reopened inside node 'scene' at line " + std::to_string(i) + " in file " +
                            fileName + ".",
                            "indie::Parser::loadScene");
                } else {
                    sceneNode = true;
                }
            } else if (irr::core::stringw(L"entity").equals_ignore_case(_xmlReader->getNodeName())) {
                if (!sceneNode) {
                    throw exceptions::ParserInvalidFileException(
                            "Node 'entity' outside 'scene' at line " + std::to_string(i) + " in file " + fileName + ".",
                            "indie::Parser::loadScene");
                }
                irr::core::stringw name = _xmlReader->getAttributeValueSafe(L"name");
                if (name.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'name' for node 'entity' at line " + std::to_string(i) + " in file "
                            + fileName + ".", "indie::Parser::loadScene");
                } else {
                    currentEntity = irr::core::stringc(name.c_str()).c_str();
                    entity = ecs.entityManager.createEntity(currentEntity);
                    irr::core::stringw shouldBeKeeped = _xmlReader->getAttributeValueSafe(L"shouldBeKeeped");
                    if (shouldBeKeeped.empty()) {
                        entity->setShouldBeKeeped(false);
                    } else {
                        entity->setShouldBeKeeped(getBool(irr::core::stringc(shouldBeKeeped.c_str()).c_str(), fileName, i));
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
                    _components.at(type)(entity, _xmlReader, fileName, i);
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
                    sceneNode = false;
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

void indie::Parser::createAI(irr::io::IXMLReader *xmlReader, const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;

    for (; xmlReader->read(); line++) {
        if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            throw exceptions::ParserInvalidFileException(
                    "Node 'system' of type 'AI' does not required subnodes, at line "
                    + std::to_string(line) + " in file " + fileName + ".", "indie::Parser::createIrrlichtManager");
        } else if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT_END) {
            if (irr::core::stringw(L"system").equals_ignore_case(xmlReader->getNodeName())) {
                ecs.systemManager.addSystem<systems::AISystem>();
                ecs.systemManager.startSystem<systems::AISystem>();
                break;
            } else {
                throw exceptions::ParserInvalidFileException(
                        "Wrong closing node at line " + std::to_string(line) + " in file " + fileName + "(expected 'system' but got '"
                        + irr::core::stringc(irr::core::stringw(xmlReader->getNodeName()).c_str()).c_str() + "').",
                        "indie::Parser::createIA");
            }
        } else {
            continue;
        }
    }
}

void indie::Parser::createBombManager(irr::io::IXMLReader *xmlReader, const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {{"", ""}};

    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createBombManager", "system");
    ecs.systemManager.addSystem<systems::BombManagerSystem>();
    ecs.systemManager.startSystem<systems::BombManagerSystem>();
}

void indie::Parser::createBonus(irr::io::IXMLReader *xmlReader, const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {{"", ""}};

    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createBonus", "system");
    ecs.systemManager.addSystem<systems::BonusSystem>();
    ecs.systemManager.startSystem<systems::BonusSystem>();
}

void indie::Parser::createDestroyManager(irr::io::IXMLReader *xmlReader, const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {{"", ""}};

    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createDestroyManager", "system");
    ecs.systemManager.addSystem<systems::DestroyOnTimeSystem>();
    ecs.systemManager.startSystem<systems::DestroyOnTimeSystem>();
}

void indie::Parser::createIrrlichtManager(irr::io::IXMLReader *xmlReader, const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {
            {"fullScreen", ""},
            {"vSync", ""},
            {"windowCaption", ""},
            {"windowDimension", ""}
    };

    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createIrrlichtManager", "system");
    ecs.systemManager.addSystem<systems::IrrlichtManagerSystem>();
    ecs.systemManager.startSystem<systems::IrrlichtManagerSystem>();
    auto &system = ecs.systemManager.getSystem<systems::IrrlichtManagerSystem>();
    if (!args["fullScreen"].empty()) {
        system.setFullScreenEnabled(getBool(args["fullScreen"], fileName, line));
    }
    if (!args["vSync"].empty()) {
        system.setVSyncEnabled(getBool(args["vSync"], fileName, line));
    }
    if (!args["windowCaption"].empty()) {
        system.setWindowCaption(args["windowCaption"]);
    }
    if (!args["windowDimension"].empty()) {
        system.setWindowDimension(getVector2D(args["windowDimension"], fileName, line));
    }
}

void indie::Parser::createIrrklangAudio(irr::io::IXMLReader *xmlReader, const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {{"", ""}};

    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createIrrklangAudio", "system");
    ecs.systemManager.addSystem<systems::IrrklangAudioSystem>();
    ecs.systemManager.startSystem<systems::IrrklangAudioSystem>();
}

void indie::Parser::createLive(irr::io::IXMLReader *xmlReader, const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {{"", ""}};

    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createLive", "system");
    ecs.systemManager.addSystem<systems::LiveSystem>();
    ecs.systemManager.startSystem<systems::LiveSystem>();
}

void indie::Parser::createMovement(irr::io::IXMLReader *xmlReader, const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {{"mapSize", ""}};

    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createMovement", "system");
    ecs.systemManager.addSystem<systems::MovementSystem>();
    auto &system = ecs.systemManager.getSystem<systems::MovementSystem>();
    if (!args["mapSize"].empty()) {
        system.setMapSize(getVector2D(args["mapSize"], fileName, line));
    } else {
        system.setMapSize({15, 15});
    }
    ecs.systemManager.startSystem<systems::MovementSystem>();
}

void indie::Parser::createTaunt(irr::io::IXMLReader *xmlReader, const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {{"", ""}};

    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createTaunt", "system");
    ecs.systemManager.addSystem<systems::TauntSystem>();
    ecs.systemManager.startSystem<systems::TauntSystem>();
}

void indie::Parser::createAIController(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                       const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args {
        {"", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createAIController");
    entity->assignComponent<components::AIController>();
}

void indie::Parser::createAnimator(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"start",      ""},
            {"end",        ""},
            {"speed",      ""},
            {"loop",       ""},
            {"transition", ""}
    };
    bool currentAnimation = false;
    std::string animationName;
    auto component = entity->assignComponent<components::Animator>();
    for (; xmlReader->read(); line++) {
        if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            if (irr::core::stringw(L"animation").equals_ignore_case(xmlReader->getNodeName())) {
                animationName = irr::core::stringc(irr::core::stringw(xmlReader->getAttributeValueSafe(L"name")).c_str()).c_str();
                if (animationName.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'name' for node 'animation' at line " + std::to_string(line) + " in file "
                            + fileName + ".", "indie::Parser::createAnimator");
                }
                fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createAnimator", "animation");
                for (auto &it : args) {
                    if (it.second.empty() && it.first != "transition") {
                        throw exceptions::ParserInvalidFileException(
                                "Missing mandatory argument '" + it.first + "' for component 'Animator' at line "
                                + std::to_string(line) + " in file " + fileName + ".", "indie::Parser::createMaterial");
                    }
                }
                bool loop = getBool(args["loop"], fileName, line);
                component->addAnimation(animationName, {
                        static_cast<unsigned int>(std::stoul(args["start"], nullptr, 16)),
                        static_cast<unsigned int>(std::stoul(args["end"], nullptr, 16)),
                        static_cast<unsigned int>(std::stoul(args["speed"], nullptr, 16)),
                        loop,
                        args["transition"]
                });
                for (auto &it : args) {
                    it.second = "";
                }
                animationName.clear();
            } else if (irr::core::stringw(L"argument").equals_ignore_case(xmlReader->getNodeName())) {
                std::string name = irr::core::stringc(irr::core::stringw(xmlReader->getAttributeValueSafe(L"name")).c_str()).c_str();
                if (name.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'name' for node 'argument' at line " + std::to_string(line)
                            + " in file " + fileName + ".", "indie::Parser::createAnimator");
                } else if (name != "currentAnimation") {
                    throw exceptions::ParserInvalidFileException(
                            "Invalid attribute 'name' for node 'argument' at line " + std::to_string(line)
                            + " in file " + fileName + ".", "indie::Parser::createAnimator");
                }
                if (currentAnimation) {
                    throw exceptions::ParserInvalidFileException(
                            "Redefinition of 'currentAnimation' at line " + std::to_string(line) + " in file "
                            + fileName + ".", "indie::Parser::createAnimator");
                }
                currentAnimation = true;
                std::string value = irr::core::stringc(irr::core::stringw(xmlReader->getAttributeValueSafe(L"value")).c_str()).c_str();
                if (value.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'value' for node 'argument' at line " + std::to_string(line) +
                            " in file " + fileName + ".", "indie::Parser::createAnimator");
                }
                std::string trimmed = irr::core::stringc(irr::core::stringw(xmlReader->getAttributeValueSafe(L"trimmed")).c_str()).c_str();
                if (trimmed.empty() || getBool(trimmed, fileName, line)) {
                    value.erase(remove_if(value.begin(), value.end(), isspace), value.end());
                }
                component->setCurrentAnimation(value);
            } else {
                throw exceptions::ParserInvalidFileException(
                        "Unknown node '" + std::string(irr::core::stringc(irr::core::stringw(xmlReader->getNodeName()).c_str()).c_str())
                        + " at line " + std::to_string(line) + " in file " + fileName + ".", "indie::Parser::createAnimator");
            }
        } else if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT_END) {
            if (!(irr::core::stringw(L"component").equals_ignore_case(xmlReader->getNodeName()))) {
                throw exceptions::ParserInvalidFileException(
                        "Wrong closing node at line " + std::to_string(line) + " in file " + fileName + "(expected 'component' but got '"
                        + irr::core::stringc(irr::core::stringw(xmlReader->getNodeName()).c_str()).c_str() + "').",
                        "indie::Parser::createAnimator");
            }
            line++;
            return;
        } else {
            continue;
        }
    }
}

void indie::Parser::createBomb(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                               const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"strength", ""},
            {"timeBeforeExplode", ""},
            {"bombType", ""},
            {"player", ""},
            {"texturePath", ""},
            {"textureMesh", ""},
            {"position", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createBomb");
    if (args["strength"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument 'strength' for component 'Bomb' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createBomb");
    }
    if (args["timeBeforeExplode"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument 'timeBeforeExplode' for component 'Bomb' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createBomb");
    }
    if (args["bombType"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument 'bombType' for component 'Bomb' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createBomb");
    }
    if (args["player"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument 'player' for component 'Bomb' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createBomb");
    }
    auto component = entity->assignComponent<components::Bomb>(
            std::stoi(args["strength"]),
            std::stof(args["timeBeforeExplode"]),
            static_cast<components::BombType>(std::stoi(args["bombType"])),
            static_cast<components::PlayerType>(std::stoi(args["player"])));
    if (!args["texturePath"].empty()) {
        component->setTexturePath(args["texturePath"]);
    }
    if (!args["textureMesh"].empty()) {
        component->setTextureMesh(args["textureMesh"]);
    }
    if (!args["position"].empty()) {
        component->setInitialPosition(getVector3D(args["position"], fileName, line));
    }
}

void indie::Parser::createBonusEffector(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                        const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"bonusType", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createBonusEffector");
    if (args["bonusType"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument 'bonusType' for component 'BonusEffector' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createBonusEffector");
    }
    entity->assignComponent<components::BonusEffector>(getBonusType(args["bonusType"]));
}

void indie::Parser::createBonusSpawner(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                       const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"spawnerType", ""},
            {"bonusType",   ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createBonusSpawner");
    if (args["spawnerType"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument 'spawnerType' for component 'BonusSpawner' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createBonusSpawner");
    }
    if (args["bonusType"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument 'bonusType' for component 'BonusSpawner' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createBonusSpawner");
    }
    entity->assignComponent<components::BonusSpawner>(getSpawnerType(args["spawnerType"]), getBonusType(args["bonusType"]));
}

void indie::Parser::createBoxCollider(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                      const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"size",   ""},
            {"offset", ""},
            {"layer",  ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createBoxCollider");
    if (args["size"].empty()) {
        args["size"] = "1,1,1";
    }
    if (args["offset"].empty()) {
        args["offset"] = "0,0,0";
    }
    if (args["layer"].empty()) {
        args["layer"] = "0xffffffff";
    }
    entity->assignComponent<components::BoxCollider>(
            getVector3D(args["size"], fileName, line), getVector3D(args["offset"], fileName, line),
            std::stoull(args["layer"], nullptr, 16));
}

void indie::Parser::createButton(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                 const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;

    std::map<std::string, std::string> args = {
            {"text", ""},
            {"id", ""},
            {"textureFileName", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createButton");
    if (args["text"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument in file " + fileName + ".", "indie::Parser::createButton");
    }
    auto component = entity->assignComponent<indie::components::Button>(args["text"]);
    if (!args["id"].empty())
        component->setId(static_cast<int>(std::stol(args["id"])));
    if (!args["textureFileName"].empty())
        component->setTexturePath(args["textureFileName"]);
}

void indie::Parser::createCamera(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                 const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"FOV", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createCamera");
    if (args["FOV"].empty()) {
        entity->assignComponent<components::Camera>();
    } else {
        entity->assignComponent<components::Camera>(
                std::stof(args["FOV"]));
    }
}

void indie::Parser::createDestroy(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                  const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"time", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createDestroy");
    if (args["time"].empty()) {
        entity->assignComponent<components::DestroyOnTime>();
    } else {
        entity->assignComponent<components::DestroyOnTime>(std::stof(args["time"]));
    }
}

void indie::Parser::createFont(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                               const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;

    std::map<std::string, std::string> args = {
            {"fileName", ""},
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createFont");
    if (args["fileName"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument in file " + fileName + ".", "indie::Parser::createFont");
    }
    auto component = entity->assignComponent<indie::components::Font>(args["fileName"]);
}

void indie::Parser::createDynamicCamera(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                        const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
        {"movementSpeed", ""},
        {"blockBorders",  ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createDynamicCamera");
    auto component = entity->assignComponent<components::DynamicCamera>();
    if (!args["movementSpeed"].empty()) {
        component->setMovementSpeed(std::atof(args["movementSpeed"].c_str()));
    }
    if (!args["blockBorders"].empty()) {
        component->setBlockBorders(std::atoi(args["blockBorders"].c_str()));
    }
}

void indie::Parser::createHoverer(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                  const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"speed",       ""},
            {"amplitude",   ""},
            {"advancement", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createHoverer");
    jf::components::ComponentHandler<components::Hoverer> component;
    if (!args["speed"].empty() && !args["amplitude"].empty()) {
        component = entity->assignComponent<components::Hoverer>(
                getVector3D(args["speed"], fileName, line), getVector3D(args["amplitude"], fileName, line));
    } else {
        component = entity->assignComponent<components::Hoverer>();
        if (!args["speed"].empty()) {
            component->setSpeed(getVector3D(args["speed"], fileName, line));
        } else if (!args["amplitude"].empty()) {
            component->setAmplitude(getVector3D(args["amplitude"], fileName, line));
        }
    }
    if (!args["advancement"].empty()) {
        component->setAdvancement(getVector3D(args["advancement"], fileName, line));
    }
}

void indie::Parser::createImage(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;

    std::map<std::string, std::string> args = {
            {"fileName", ""},
            {"alphaChannel", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createImage");
    if (args["fileName"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument in file " + fileName + ".", "indie::Parser::createImage");
    }
    auto component = entity->assignComponent<indie::components::Image>(args["fileName"]);
    if (!args["alphaChannel"].empty()) {
        component->setUseAlpha(getBool(args["alphaChannel"], fileName, line));
    }
}

void indie::Parser::createLeaderBoard(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                      const std::string &fileName, unsigned int &line)
{
    components::LeaderBoard::PlayerLeaderBoard playerLeaderboard;
    auto component = entity->assignComponent<indie::components::LeaderBoard>();
    for (; xmlReader->read(); line++) {
        if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            if (irr::core::stringw(L"player").equals_ignore_case(xmlReader->getNodeName())) {
                std::string id = irr::core::stringc(irr::core::stringw(xmlReader->getAttributeValueSafe(L"id")).c_str()).c_str();
                if (id.empty()) {
                    throw exceptions::ParserInvalidFileException(
                        "Missing attribute 'id' for node 'player' at line " + std::to_string(line) + " in file "
                        + fileName + ".", "indie::Parser::createLeaderBoard");
                }
                std::string ranking = irr::core::stringc(irr::core::stringw(xmlReader->getAttributeValueSafe(L"ranking")).c_str()).c_str();
                ranking.erase(remove_if(ranking.begin(), ranking.end(), isspace), ranking.end());
                if (ranking.empty()) {
                    throw exceptions::ParserInvalidFileException(
                        "Missing attribute 'ranking' for node 'player' at line " + std::to_string(line) + " in file "
                        + fileName + ".", "indie::Parser::createLeaderBoard");
                }
                playerLeaderboard.emplace_back(std::stoi(id), std::stoi(ranking));
            } else {
                throw exceptions::ParserInvalidFileException(
                    "Unknown node '" + std::string(irr::core::stringc(irr::core::stringw(xmlReader->getNodeName()).c_str()).c_str())
                    + " at line " + std::to_string(line) + " in file " + fileName + ".", "indie::createLeaderBoard");
            }
        } else if (xmlReader->getNodeType() == irr::io::EXN_ELEMENT_END) {
            if (!(irr::core::stringw("component").equals_ignore_case(xmlReader->getNodeName()))) {
                throw exceptions::ParserInvalidFileException(
                    "Wrong closing node at line " + std::to_string(line) + " in file " + fileName + "(expected 'component' but got '"
                    + irr::core::stringc(irr::core::stringw(xmlReader->getNodeName()).c_str()).c_str() + "').",
                    "indie::parser::createLeaderBoard");
            }
            line++;
            return;
        } else {
            continue;
        }
    }
}

void indie::Parser::createMaterial(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"fileName", ""},
            {"type", ""},
            {"flags", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createMaterial");
    if (args["fileName"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument 'fileName' for component 'Material' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createMaterial");
    }
    jf::components::ComponentHandler<components::Material> component;
    if (args["type"].empty()) {
        component = entity->assignComponent<components::Material>(
                args["fileName"]);
    } else {
         component = entity->assignComponent<components::Material>(
                args["fileName"], getMaterialType(args["type"]));
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

void indie::Parser::createMesh(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                               const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"fileName", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createTransform");
    if (args["fileName"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument 'fileName' for component 'Transform' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createMesh");
    }
    entity->assignComponent<components::Mesh>(
        args["fileName"]);
}

void indie::Parser::createMoveToTarget(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                       const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
        {"target",        ""},
        {"followTarget",  ""},
        {"reachedTarget", ""},
        {"speed",         ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createMoveToTarget");
    auto component = entity->assignComponent<components::MoveToTarget>();

    if (!args["target"].empty()) {
        component->setTarget(getVector3D(args["target"], fileName, line));
    }
    if (!args["followTarget"].empty()) {
        component->setFollowTarget(getBool(args["followTarget"], fileName, line));
    }
    if (!args["reachedTarget"].empty()) {
        component->setReachedTarget(getBool(args["reachedTarget"], fileName, line));
    }
    if (!args["speed"].empty()) {
        component->setSpeed(std::atof(args["speed"].c_str()));
    }
}

void indie::Parser::createParticle(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"name",        ""},
            {"fileName",    ""},
            {"layer",       ""},
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
                "Missing mandatory argument 'name' for component 'Particle' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createParticle");
    }
    auto component = entity->assignComponent<components::Particle>(
        args["name"]);
    if (!args["fileName"].empty() && !args["layer"].empty()) {
        component->setTexture(std::stoi(args["layer"]), args["fileName"]);
    } else if (!args["fileName"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing argument 'layer' for texture setting for component 'Particle' at line "
                + std::to_string(line) + " in file " + fileName + ".", "indie::Parser::createParticle");
    } else if (!args["layer"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing argument 'fileName' for texture setting for component 'Particle' at line "
                + std::to_string(line) + " in file " + fileName + ".", "indie::Parser::createParticle");
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
        component->setEmitRate(std::make_pair(std::stoi(args["emitRate"].substr(0, args["emitRate"].find(','))),
                std::stoi(args["emitRate"].substr(args["emitRate"].find(',') + 1))));
    }
    if (!args["brightColor"].empty()) {
        component->setDarkBrightColor(std::make_pair(
                getColor(args["brightColor"].substr(0, args["brightColor"].find(';')), fileName, line),
                getColor(args["brightColor"].substr(args["brightColor"].find(';') + 1), fileName, line)));
    }
    if (!args["age"].empty()) {
        component->setMinMaxAge(std::make_pair(std::stoi(args["age"].substr(0, args["emitRate"].find(','))),
                std::stoi(args["age"].substr(args["age"].find(',') + 1))));
    }
    if (!args["angle"].empty()) {
        component->setAngle(std::stoi(args["angle"]));
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
        component->setFadeTime(std::stoi(args["fadeTime"]));
    }
}

void indie::Parser::createPlayerAlive(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                      const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
        {"lives",        ""},
        {"markedAsDead", ""},
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createPlayerController");
    auto component = entity->assignComponent<components::PlayerAlive>();
    if (!args["lives"].empty()) {
        component->setLives(std::atoi(args["lives"].c_str()));
    }
    if (!args["markedAsDead"].empty()) {
        component->setMarkedAsDead(getBool(args["markedAsDead"], fileName, line));
    }
}

void indie::Parser::createPlayerController(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                           const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"xMove",            ""},
            {"yMove",            ""},
            {"zMove",            ""},
            {"lockXMove",        ""},
            {"lockYMove",        ""},
            {"lockZMove",        ""},
            {"relativeMove",     ""},
            {"moveSpeed",        ""},
            {"xRotate",          ""},
            {"yRotate",          ""},
            {"zRotate",          ""},
            {"lockXRotate",      ""},
            {"lockYRotate",      ""},
            {"lockZRotate",      ""},
            {"lookForward",      ""},
            {"rotateSpeed",      ""},
            {"idleAnimation",    ""},
            {"walkingAnimation", ""},
            {"isWalking",        ""},
            {"isTaunting",       ""},
            {"tauntButton",      ""},
            {"tauntAnimation",   ""},
            {"isPlacingBomb",    ""},
            {"bombButton",       ""},
            {"bombAnimation",    ""},
            {"bombForce",        ""},
            {"maxBomb",          ""},
            {"playerType",       ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createPlayerController");
    auto component = entity->assignComponent<components::PlayerController>();
    if (!args["xMove"].empty()) {
        component->setXMovementAxis(args["xMove"]);
    }
    if (!args["yMove"].empty()) {
        component->setYMovementAxis(args["yMove"]);
    }
    if (!args["zMove"].empty()) {
        component->setZMovementAxis(args["zMove"]);
    }
    if (!args["lockXMove"].empty()) {
        component->setLockMovementX(getBool(args["lockXMove"], fileName, line));
    }
    if (!args["lockYMove"].empty()) {
        component->setLockMovementY(getBool(args["lockYMove"], fileName, line));
    }
    if (!args["lockZMove"].empty()) {
        component->setLockMovementZ(getBool(args["lockZMove"], fileName, line));
    }
    if (!args["relativeMove"].empty()) {
        component->setMovementRelativeToCamera(getBool(args["relativeMove"], fileName, line));
    }
    if (!args["moveSpeed"].empty()) {
        component->setMovementSpeed(std::stof(args["moveSpeed"]));
    }
    if (!args["xRotate"].empty()) {
        component->setXRotationAxis(args["xRotate"]);
    }
    if (!args["yRotate"].empty()) {
        component->setYRotationAxis(args["yRotate"]);
    }
    if (!args["zRotate"].empty()) {
        component->setZRotationAxis(args["zRotate"]);
    }
    if (!args["lockXRotate"].empty()) {
        component->setLockRotationX(getBool(args["lockXRotate"], fileName, line));
    }
    if (!args["lockYRotate"].empty()) {
        component->setLockRotationY(getBool(args["lockYRotate"], fileName, line));
    }
    if (!args["lockZRotate"].empty()) {
        component->setLockRotationZ(getBool(args["lockZRotate"], fileName, line));
    }
    if (!args["lookForward"].empty()) {
        component->setAlwaysLookForward(getBool(args["lookForward"], fileName, line));
    }
    if (!args["rotateSpeed"].empty()) {
        component->setRotationSpeed(std::stof(args["rotateSpeed"]));
    }
    if (!args["idleAnimation"].empty()) {
        component->setIdleAnimation(args["idleAnimation"]);
    }
    if (!args["walkingAnimation"].empty()) {
        component->setWalkingAnimation(args["walkingAnimation"]);
    }
    if (!args["isWalking"].empty()) {
        component->setIsWalking(getBool(args["isWalking"], fileName, line));
    }
    if (!args["isTaunting"].empty()) {
        component->setIsTaunting(getBool(args["isTaunting"], fileName, line));
    }
    if (!args["tauntButton"].empty()) {
        component->setTauntButton(args["tauntButton"]);
    }
    if (!args["tauntAnimation"].empty()) {
        component->setTauntAnimation(args["tauntAnimation"]);
    }
    if (!args["isPlacingBomb"].empty()) {
        component->setIsPlacingBomb(getBool(args["isPlacingBomb"], fileName, line));
    }
    if (!args["bombButton"].empty()) {
        component->setBombPlacementButton(args["bombButton"]);
    }
    if (!args["bombAnimation"].empty()) {
        component->setBombPlacementAnimation(args["bombAnimation"]);
    }
    if (!args["bombForce"].empty()) {
        component->setBombForce(std::stoi(args["bombForce"]));
    }
    if (!args["maxBomb"].empty()) {
        component->setMaxBomb(std::stoi(args["maxBomb"]));
    }
    if (!args["playerType"].empty()) {
        component->setPlayerType(static_cast<components::PlayerType>(std::stoi(args["playerType"])));
    }
}

void indie::Parser::createRotator(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                  const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"speed", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createRotator");
    if (args["speed"].empty()) {
        entity->assignComponent<components::Rotator>();
    } else {
        entity->assignComponent<components::Rotator>(
                getVector3D(args["speed"], fileName, line));
    }
}

void indie::Parser::createSound(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                const std::string &fileName, unsigned int &line)
{
    ECSWrapper ecs;
    std::map<std::string, std::string> args = {
            {"fileName",     ""},
            {"type",         ""},
            {"position",     ""},
            {"playLooped",   ""},
            {"startPaused",  ""},
            {"volume",       ""},
            {"playPosition", ""},
            {"velocity",     ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createSound");
    if (args["fileName"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument 'fileName' for component 'Sound' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createSound");
    }
    if (args["type"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument 'type' for component 'Sound' at line " + std::to_string(line)
                + " in file " + fileName + ".", "indie::Parser::createSound");
    }
    jf::components::ComponentHandler<components::SoundComponent> component;
    if (args["position"].empty()) {
        component = entity->assignComponent<components::SoundComponent>(
                args["fileName"], getSoundType(args["type"], fileName, line));
    } else {
        component = entity->assignComponent<components::SoundComponent>(
                args["fileName"], getSoundType(args["type"], fileName, line),
                getVector3D(args["position"], fileName, line));
    }
    if (!args["playLooped"].empty()) {
        component->setIsLooped(getBool(args["playLooped"], fileName, line));
    }
    if (!args["startPaused"].empty()) {
        component->setIsPaused(getBool(args["startPaused"], fileName, line));
    }
    try {
        auto &audioSystem = ecs.systemManager.getSystem<systems::IrrklangAudioSystem>();
        if (component->getSpatialization()) {
            component->setSound(audioSystem.add3DSound(
                component->getSourceFile(), component->getPosition(), component->getIsLooped(), component->getIsPaused()));
        } else {
            component->setSound(audioSystem.add2DSound(
                component->getSourceFile(), component->getIsLooped(), component->getIsPaused()));
        }
    } catch (jf::SystemNotFoundException &e) {
        std::cerr << "[WARNING][IrrklangAudioSystem] Parser found a sound to add but system is uninitialized" << std::endl;
    }
    if (!args["volume"].empty()) {
        component->setVolume(std::stof(args["volume"]));
    }
    if (!args["playPosition"].empty()) {
        component->setPlayPosition(std::stoul(args["playPosition"], nullptr, 16));
    }
    if (!args["velocity"].empty()) {
        component->setVelocity(getVector3D(args["velocity"], fileName, line));
    }
}

void indie::Parser::createText(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                               const std::string &fileName, unsigned int &line)
{
    std::map<std::string, std::string> args = {
            {"text", ""},
            {"horizontalAlignement", ""},
            {"verticalAlignement", ""},
            {"color", ""},
            {"backgroundColor", ""},
            {"id", ""}
    };
    fillMapArgs(args, xmlReader, fileName, line, "indie::Parser::createText");
    if (args["text"].empty()) {
        throw exceptions::ParserInvalidFileException(
                "Missing mandatory argument in file " + fileName + ".", "indie::Parser::createText");
    }
    auto component = entity->assignComponent<indie::components::Text>(args["text"]);
    if (!args["horizontalAlignement"].empty())
        component->setHorizontalAlignement(getHorizontalAlignement(args["horizontalAlignement"]));
    if (!args["verticalAlignement"].empty())
        component->setVerticalAlignement(getVerticalAlignement(args["verticalAlignement"]));
    if (!args["color"].empty())
        component->setColor(getColor(args["color"], fileName, line));
    if (!args["backgroundColor"].empty())
        component->setBackgroundColor(getColor(args["backgroundColor"], fileName, line));
    if (!args["id"].empty())
        component->setId(static_cast<int>(std::stol(args["id"])));
}

void indie::Parser::createTransform(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                    const std::string &fileName, unsigned int &line)
{
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
    entity->assignComponent<components::Transform>(
            getVector3D(args["position"], fileName, line), getVector3D(args["rotation"], fileName, line),
            getVector3D(args["scale"], fileName, line));
}

void indie::Parser::fillMapArgs(std::map<std::string, std::string> &args, irr::io::IXMLReader *xmlReader,
                                const std::string &fileName, unsigned int &line, const std::string &callingMethod,
                                const std::string &node)
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
                if (value.empty()) {
                    throw exceptions::ParserInvalidFileException(
                            "Missing attribute 'value' for node 'argument' at line " + std::to_string(line) + " in file " + fileName + ".",
                            callingMethod);
                }
                std::string trimmed = irr::core::stringc(irr::core::stringw(xmlReader->getAttributeValueSafe(L"trimmed")).c_str()).c_str();
                if (trimmed.empty() || getBool(trimmed, fileName, line)) {
                    value.erase(remove_if(value.begin(), value.end(), isspace), value.end());
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
            if (!(irr::core::stringw(node.c_str()).equals_ignore_case(xmlReader->getNodeName()))) {
                throw exceptions::ParserInvalidFileException(
                        "Wrong closing node at line " + std::to_string(line) + " in file " + fileName + "(expected '" + node + "' but got '"
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
    x = std::stof(value.substr(0, pos));
    y = std::stof(value.substr(pos + 1));
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
    x = std::stof(value.substr(0, pos));
    auto newPos = value.find(',', pos + 1);
    y = std::stof(value.substr(pos + 1, newPos - (pos + 1)));
    pos = newPos;
    z = std::stof(value.substr(pos + 1));
    return maths::Vector3D(x, y, z);
}

const irr::video::SColor indie::Parser::getColor(const std::string &value, const std::string &fileName,
                                                 unsigned int &line)
{
    unsigned int a, r, g, b;

    size_t n = std::count(value.begin(), value.end(), ',');
    if (n != 3) {
        throw exceptions::ParserInvalidFileException(
                "Wrong argument at line " + std::to_string(line) + " in file " + fileName
                + "(expected 'int, int, int, int' but got something else.", "indie::Parser::getColor");
    }
    auto pos = value.find(',');
    a = std::stoul(value.substr(0, pos), nullptr, 16);
    auto newPos = value.find(',', pos + 1);
    r = std::stoul(value.substr(pos + 1, newPos - (pos + 1)), nullptr, 16);
    pos = newPos;
    newPos = value.find(',', pos + 1);
    g = std::stoul(value.substr(pos + 1, newPos - (pos + 1)), nullptr, 16);
    pos = newPos;
    b = std::stoul(value.substr(pos + 1), nullptr, 16);
    return irr::video::SColor(a, r, g, b);
}

bool indie::Parser::getBool(const std::string &value, const std::string &fileName, unsigned int &line)
{
    if (value == "true") {
        return true;
    } else if (value == "false") {
        return false;
    } else {
        throw exceptions::ParserInvalidFileException(
                "Invalid value for attribute 'shouldBeKeeped', expected 'true' or 'false', but got '"
                + value + "' at line " + std::to_string(line) + " in file " + fileName + ".",
                "indie::Parser::getBool");
    }
}

indie::components::BonusType indie::Parser::getBonusType(const std::string &type)
{
    return _bonusTypes.at(type);
}

indie::components::BonusSpawner::BonusSpawnerType indie::Parser::getSpawnerType(const std::string &type)
{
    if (type == "BONUS_SPAWNER_T_RANDOM") {
        return components::BonusSpawner::BONUS_SPAWNER_T_RANDOM;
    } else if (type == "BONUS_SPAWNER_T_SPECIFIC") {
        return components::BonusSpawner::BONUS_SPAWNER_T_SPECIFIC;
    } else {
        throw exceptions::ParserInvalidFileException("Invalid BonusSpawerType", "indie::Parser::getSpawnerType");
    }
}

indie::components::Text::VerticalAlignement indie::Parser::getVerticalAlignement(const std::string &align)
{
    return _verticalAlignements.at(align);
}

indie::components::Text::HorizontalAlignement indie::Parser::getHorizontalAlignement(const std::string &align)
{
    return _horizontalAlignements.at(align);
}