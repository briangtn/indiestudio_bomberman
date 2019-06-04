/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Button.hpp
*/

/* Created the 03/06/2019 at 21:40 by brian */

#ifndef INDIESTUDIO_BUTTON_HPP
#define INDIESTUDIO_BUTTON_HPP

#include <string>
#include <irrlicht.h>
#include "GuiBase.hpp"

typedef void (*onClickedFuncPtr)();

namespace indie {
    namespace components {

        class Button : public GUIBase {
        public:
            explicit Button(
                    jf::entities::Entity &entity,
                    const std::string &text,
                    int _id = -1,
                    const std::string &texturePath = "");
            ~Button();

            const std::string &getText() const;
            void setText(const std::string &text);

            irr::gui::IGUIButton *getButtonNode() const;
            void setButtonNode(irr::gui::IGUIButton *buttonNode);

            const std::string &getTexturePath() const;
            void setTexturePath(const std::string &texturePath);

            irr::video::ITexture *getTextureNode() const;
            void setTextureNode(irr::video::ITexture *textureNode);

            onClickedFuncPtr getOnClicked() const;
            void setOnClicked(onClickedFuncPtr function);

            bool isInit() const;
            bool isTextureNeedInit() const;

        protected:
            std::string _text;
            std::string _texturePath;
            irr::gui::IGUIButton *_buttonNode;
            irr::video::ITexture *_textureNode;
            jf::internal::ID _eventCloseID;
            onClickedFuncPtr _onClicked;
        };
    };
};


#endif //INDIESTUDIO_BUTTON_HPP
