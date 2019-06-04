/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Font.hpp
*/

/* Created the 03/06/2019 at 21:45 by brian */

#ifndef INDIESTUDIO_FONT_HPP
#define INDIESTUDIO_FONT_HPP

#include <string>
#include <irrlicht.h>
#include "Entity.hpp"

namespace indie {
    namespace components {
        class Font : public jf::components::Component {
        public:
            explicit Font(jf::entities::Entity &entity, const std::string &path);
            ~Font();

            const std::string &getPath() const;
            void setPath(const std::string &path);

            irr::gui::IGUIFont *getFontNode() const;
            void setFontNode(irr::gui::IGUIFont *fontNode);

            bool isInit() const;

        protected:
            std::string _path;
            irr::gui::IGUIFont *_fontNode;
            jf::internal::ID _eventCloseID;
        };
    }
}

#endif //INDIESTUDIO_FONT_HPP
