/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Button.cpp
*/

/* Created the 03/06/2019 at 21:40 by brian */

#include "ECSWrapper.hpp"
#include "events/IrrlichtClosingWindowEvent.hpp"
#include "Events.hpp"
#include "components/GUI/Button.hpp"

indie::components::Button::Button(
        jf::entities::Entity &entity,
        const std::string &text,
        int id,
        const std::string &texturePath)
    :   GUIBase(entity, id),
        _text(text),
        _buttonNode(nullptr),
        _textureNode(nullptr),
        _texturePath(texturePath),
        _onClicked(nullptr),
        _onHovered(nullptr)
{
    ECSWrapper ecs;

    _eventCloseID = ecs.eventManager.addListener<Button, events::IrrlichtClosingWindowEvent>(this, [](Button *button, events::IrrlichtClosingWindowEvent e){
        if (button->_buttonNode != nullptr)
            button->_buttonNode->remove();
        button->_buttonNode = nullptr;
    });
    EMIT_CREATE(Button);
}

indie::components::Button::~Button()
{
    EMIT_DELETE(Button);

    ECSWrapper ecs;
    ecs.eventManager.removeListener(_eventCloseID);
    if (_buttonNode != nullptr)
        _buttonNode->remove();
}

const std::string &indie::components::Button::getText() const
{
    return _text;
}

void indie::components::Button::setText(const std::string &text)
{
    _text = text;
}

irr::gui::IGUIButton *indie::components::Button::getButtonNode() const
{
    return _buttonNode;
}

void indie::components::Button::setButtonNode(irr::gui::IGUIButton *buttonNode)
{
    _buttonNode = buttonNode;
}

bool indie::components::Button::isInit() const
{
    return _buttonNode != nullptr;
}

const std::string &indie::components::Button::getTexturePath() const
{
    return _texturePath;
}

void indie::components::Button::setTexturePath(const std::string &texturePath)
{
    _texturePath = texturePath;
    if (_textureNode != nullptr) {
        _textureNode->drop();
        _textureNode = nullptr;
    }
}

irr::video::ITexture *indie::components::Button::getTextureNode() const
{
    return _textureNode;
}

void indie::components::Button::setTextureNode(irr::video::ITexture *textureNode)
{
    _textureNode = textureNode;
}

bool indie::components::Button::isTextureNeedInit() const
{
    return _texturePath != "" && _textureNode == nullptr;
}

onClickedFuncPtr indie::components::Button::getOnClicked() const
{
    return _onClicked;
}

void indie::components::Button::setOnClicked(onClickedFuncPtr function)
{
    _onClicked = function;
}

onHoverFuncPtr indie::components::Button::getOnHovered() const
{
    return _onHovered;
}

void indie::components::Button::setOnHovered(onHoverFuncPtr func)
{
    _onHovered = func;
}

indie::components::Button &indie::components::Button::operator>>(std::ostream &file)
{
    file << R"(        <component type="Button">)" << std::endl;
    file << R"(            <argument name="text" value=")" << _text << R"("/>)" << std::endl;
    file << R"(            <argument name="id" value=")" << _id << R"("/>)" << std::endl;
    if (!_texturePath.empty()) {
        file << R"(            <argument name="textureFileName" value=")" << _texturePath << R"("/>)" << std::endl;
    }
    file << "        </component>" << std::endl;
    return *this;
}
