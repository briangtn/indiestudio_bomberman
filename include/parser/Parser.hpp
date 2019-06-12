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
#include "components/SoundComponent.hpp"
#include "scenes/Scene.hpp"

#define SYSTEMS_FILE_PATH   "../resources/systems.xml"
#define SCENES_FOLDER_PATH  "../resources/scenes"

namespace indie {

    class Parser {
    private:
        Parser();

    public:
        ~Parser();

        static Parser &getInstance();

        Parser(const Parser &other) = delete;
        Parser &operator=(const Parser &other) = delete;

        void loadSystems(const std::string &fileName);
        const std::vector<std::pair<std::string, scenes::IScene *>> &loadScenes(const std::string &pathToFolder);
        void loadScene(const std::string &fileName);
        static void fillMapArgs(std::map<std::string, std::string> &args, irr::io::IXMLReader *xmlReader,
                                const std::string &fileName, unsigned int &line, const std::string &callingMethod,
                                const std::string &node="component");

    private: /* SYSTEMS */
        static void createIrrlichtManager(irr::io::IXMLReader *xmlReader,
                                          const std::string &fileName, unsigned int &line);
        static void createIrrklangAudio(irr::io::IXMLReader *xmlReader,
                                        const std::string &fileName, unsigned int &line);
        static void createMovement(irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int &line);
        static void createTaunt(irr::io::IXMLReader *xmlReader,
                                const std::string &fileName, unsigned int &line);
        static void createAI(irr::io::IXMLReader *xmlReader,
                                const std::string &fileName, unsigned int &line);

    private: /* COMPONENTS */
        static void createAnimator(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int &line);
        static void createBoxCollider(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                      const std::string &fileName, unsigned int &line);
        static void createCamera(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                 const std::string &fileName, unsigned int &line);
        static void createHoverer(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                  const std::string &fileName, unsigned int &line);
        static void createAIController(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                  const std::string &fileName, unsigned int &line);
        static void createMaterial(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int &line);
        static void createMesh(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                               const std::string &fileName, unsigned int &line);
        static void createMoveToTarget(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                       const std::string &fileName, unsigned int &line);
        static void createParticle(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                   const std::string &fileName, unsigned int &line);
        static void createPlayerController(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                           const std::string &fileName, unsigned int &line);
        static void createRotator(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                  const std::string &fileName, unsigned int &line);
        static void createSound(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                const std::string &fileName, unsigned int &line);
        static void createTransform(jf::entities::EntityHandler &entity, irr::io::IXMLReader *xmlReader,
                                    const std::string &fileName, unsigned int &line);

    private: /* CONVERTORS */
        static irr::video::E_MATERIAL_TYPE getMaterialType(const std::string &type);
        static irr::video::E_MATERIAL_FLAG getMaterialFlag(const std::string &flag);
        static const components::SoundComponent::SoundType getSoundType(const std::string &type, const std::string &fileName,
                                                                        unsigned int &line);
        static const maths::Vector2D getVector2D(const std::string &value, const std::string &fileName,
                                                 unsigned int &line);
        static const maths::Vector3D getVector3D(const std::string &value, const std::string &fileName,
                                                 unsigned int &line);
        static const irr::video::SColor getColor(const std::string &value, const std::string &fileName,
                                                 unsigned int &line);
        static bool getBool(const std::string &value, const std::string &fileName, unsigned int &line);

    private:
        irr::IrrlichtDevice *_device;
        irr::io::IXMLReader *_xmlReader;

        std::vector<std::pair<std::string, scenes::IScene *>> _scenes;

        std::map<const irr::core::stringw, std::function<void(irr::io::IXMLReader *, std::string, unsigned int &)>> _systems;
        std::map<const irr::core::stringw, std::function<void(jf::entities::EntityHandler &, irr::io::IXMLReader *, std::string, unsigned int &)>> _components;
        static const std::map<std::string, irr::video::E_MATERIAL_TYPE> _materialTypes;
        static const std::map<std::string, irr::video::E_MATERIAL_FLAG> _materialFlags;
    };

}

#endif //INDIESTUDIO_PARSER_HPP
