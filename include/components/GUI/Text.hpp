/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Text.hpp
*/

/* Created the 06/06/2019 at 09:40 by brian */

#ifndef INDIESTUDIO_TEXT_HPP
#define INDIESTUDIO_TEXT_HPP

#include <string>
#include "irrlicht.h"
#include "components/GUI/GuiBase.hpp"
#include "Entity.hpp"

namespace indie {
    namespace components {
        class Text : public GUIBase {
        public:
            enum HorizontalAlignement {
                LEFT = irr::gui::EGUIA_UPPERLEFT,
                CENTER = irr::gui::EGUIA_CENTER,
                RIGHT = irr::gui::EGUIA_LOWERRIGHT
            };

            enum VerticalAlignement {
                TOP = irr::gui::EGUIA_UPPERLEFT,
                MIDDLE = irr::gui::EGUIA_CENTER,
                BOTTOM = irr::gui::EGUIA_LOWERRIGHT
            };
        public:
            explicit Text(
                    jf::entities::Entity &entity,
                    const std::string &text,
                    HorizontalAlignement horizontalAlignement = LEFT,
                    VerticalAlignement verticalAlignement = TOP,
                    irr::video::SColor color = irr::video::SColor(255, 0, 0, 0),
                    irr::video::SColor backgroundColor = irr::video::SColor(0, 0, 0, 0),
                    int _id = -1);
            ~Text();

            Text &operator>>(std::ostream &file);

            const std::string &getText() const;
            void setText(const std::string &text);

            irr::gui::IGUIStaticText *getTextNode() const;
            void setTextNode(irr::gui::IGUIStaticText *textNode);

            HorizontalAlignement getHorizontalAlignement() const;
            void setHorizontalAlignement(HorizontalAlignement horizontalAlignement);

            VerticalAlignement getVerticalAlignement() const;
            void setVerticalAlignement(VerticalAlignement verticalAlignement);

            const irr::video::SColor &getColor() const;
            void setColor(const irr::video::SColor &color);

            const irr::video::SColor &getBackgroundColor() const;
            void setBackgroundColor(const irr::video::SColor &backgroundColor);

            bool isInit() const;

        protected:
            std::string _text;
            irr::gui::IGUIStaticText *_textNode;
            irr::video::SColor _color;
            irr::video::SColor _backgroundColor;
            HorizontalAlignement _horizontalAlignement;
            VerticalAlignement _verticalAlignement;
            jf::internal::ID _eventCloseID;
        };

        std::ostream &operator<<(std::ostream &file, Text::HorizontalAlignement alignement);
        std::ostream &operator<<(std::ostream &file, Text::VerticalAlignement alignement);
    }
}

#endif //INDIESTUDIO_TEXT_HPP
