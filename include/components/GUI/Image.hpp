/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Image.hpp
*/

/* Created the 06/06/2019 at 14:43 by brian */

#ifndef INDIESTUDIO_IMAGE_HPP
#define INDIESTUDIO_IMAGE_HPP

#include <irrlicht.h>
#include "Entity.hpp"

namespace indie {
    namespace components {
        class Image : public jf::components::Component {
        public:
            explicit Image(jf::entities::Entity &entity, const std::string &path);

            const std::string &getPath() const;
            void setPath(const std::string &path);

            irr::video::ITexture *getTextureNode() const;
            void setTextureNode(irr::video::ITexture *textureNode);

            bool isTextureInit() const;

        protected:
            std::string _path;
            irr::video::ITexture *_textureNode;
        };
    }
}

#endif //INDIESTUDIO_IMAGE_HPP
