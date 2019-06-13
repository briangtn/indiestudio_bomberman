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
#include "GuiBase.hpp"

namespace indie {
    namespace components {
        class Image : public GUIBase {
        public:
            explicit Image(jf::entities::Entity &entity, const std::string &path, int id = -1);
            ~Image();

            Image &operator>>(std::ostream &file);

            const std::string &getPath() const;
            void setPath(const std::string &path);

            irr::video::ITexture *getTextureNode() const;
            void setTextureNode(irr::video::ITexture *textureNode);

            irr::gui::IGUIImage *getImageNode() const;
            void setImageNode(irr::gui::IGUIImage *imageNode);

            bool isTextureInit() const;
            bool isImageInit() const;

            bool isUseAlpha() const;
            void setUseAlpha(bool useAlpha);

            void reload();
            void setNeedReload(bool reload);
            bool isWaitReload() const;

        protected:
            std::string _path;
            irr::video::ITexture *_textureNode;
            irr::gui::IGUIImage *_imageNode;
            jf::internal::ID _eventCloseID;
            bool _useAlpha;
            bool _needReload;
        };
    }
}

#endif //INDIESTUDIO_IMAGE_HPP
