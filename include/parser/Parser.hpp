/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Parser.hpp
*/

/* Created the 27/05/2019 at 16:12 by jbulteau */

#ifndef INDIESTUDIO_PARSER_HPP
#define INDIESTUDIO_PARSER_HPP

#include <string>
#include <vector>
#include <map>
#include <irrlicht.h>
#include <functional>
#include "scenes/IScene.hpp"

namespace indie {

    class Parser {
    private:
        Parser();

    public:
        ~Parser();

        static Parser &getInstance();

        Parser(const Parser &other) = delete;
        Parser &operator=(const Parser &other) = delete;

        const std::vector<std::pair<std::string, scenes::IScene *>> &loadScenes(const std::string &pathToFolder);

    private:
        scenes::IScene *loadScene(const std::string &fileName);

        static void createScene();
        static void createEntity();
        static void createComponent();

    private:
        irr::IrrlichtDevice *_device;
        irr::io::IXMLReader *_xmlReader;

        std::vector<std::pair<std::string, scenes::IScene *>> _scenes;

        std::map<const irr::core::stringw, std::function<void()>> _keys;
    };

}

#endif //INDIESTUDIO_PARSER_HPP
