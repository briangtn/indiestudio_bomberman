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
#include <boost/filesystem.hpp>
#include <regex>

indie::Parser::Parser()
    : _device(irr::createDevice(irr::video::EDT_NULL)), _xmlReader(nullptr), _scenes(), _keys(
        {
            {(L"scene"),     &createScene },
            {(L"entity"),    &createEntity },
            {(L"component"), &createComponent },
            {(L"argument"),  []() { std::cout << "argument" << std::endl; }}
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
        std::regex regex(".*\\.xml$");
        if (std::regex_search(entry.path().leaf().string(), regex))
            _scenes.emplace_back(std::pair<std::string, scenes::IScene *>(entry.path().leaf().string(), nullptr));
    });
    for (auto &_it : _scenes)
        _it.second = loadScene(_it.first);
    return _scenes;
}

indie::scenes::IScene *indie::Parser::loadScene(const std::string &fileName)
{
    irr::core::stringw path(fileName.c_str());

    _xmlReader = _device->getFileSystem()->createXMLReader(path);
    if (!_xmlReader)
        throw indie::exceptions::ParserDeviceException("Failed to create XML reader.", "indie::Parser::loadScene");

    while (_xmlReader->read()) {
        if (_xmlReader->getNodeType() == irr::io::EXN_ELEMENT) {
            _keys[_xmlReader->getNodeName()]();
        }
    }
}

void indie::Parser::createScene()
{

}

void indie::Parser::createEntity()
{

}

void indie::Parser::createComponent()
{

}
