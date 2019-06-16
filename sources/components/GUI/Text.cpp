/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Text.cpp
*/

/* Created the 06/06/2019 at 09:40 by brian */

#include "ECSWrapper.hpp"
#include "Events.hpp"
#include "events/IrrlichtClosingWindowEvent.hpp"
#include "components/GUI/GuiBase.hpp"
#include "components/GUI/Text.hpp"
#include "components/ComponentParticle.hpp"

indie::components::Text::Text(
        jf::entities::Entity &entity,
        const std::string &text,
        HorizontalAlignement horizontalAlignement,
        VerticalAlignement verticalAlignement,
        irr::video::SColor color,
        irr::video::SColor backgroundColor,
        int id)
    :   GUIBase(entity, id),
        _text(text),
        _textNode(nullptr),
        _color(color),
        _backgroundColor(backgroundColor),
        _horizontalAlignement(horizontalAlignement),
        _verticalAlignement(verticalAlignement)
{
    ECSWrapper ecs;

    _eventCloseID = ecs.eventManager.addListener<Text, events::IrrlichtClosingWindowEvent>(this, [](Text *text, events::IrrlichtClosingWindowEvent e){
        if (text->_textNode != nullptr)
            text->_textNode->remove();
        text->_textNode= nullptr;
    });
    EMIT_CREATE(Text);
}

indie::components::Text::~Text()
{
    EMIT_DELETE(Text);

    ECSWrapper ecs;
    ecs.eventManager.removeListener(_eventCloseID);
    if (_textNode != nullptr)
        _textNode->remove();
    _textNode = nullptr;
}

const std::string &indie::components::Text::getText() const
{
    return _text;
}

void indie::components::Text::setText(const std::string &text)
{
    _text = text;
}

irr::gui::IGUIStaticText *indie::components::Text::getTextNode() const
{
    return _textNode;
}

void indie::components::Text::setTextNode(irr::gui::IGUIStaticText *textNode)
{
    _textNode = textNode;
}

bool indie::components::Text::isInit() const
{
    return _textNode != nullptr;
}

indie::components::Text::HorizontalAlignement indie::components::Text::getHorizontalAlignement() const
{
    return _horizontalAlignement;
}

void indie::components::Text::setHorizontalAlignement(indie::components::Text::HorizontalAlignement horizontalAlignement)
{
    _horizontalAlignement = horizontalAlignement;
}

indie::components::Text::VerticalAlignement indie::components::Text::getVerticalAlignement() const
{
    return _verticalAlignement;
}

void indie::components::Text::setVerticalAlignement(indie::components::Text::VerticalAlignement verticalAlignement)
{
    _verticalAlignement = verticalAlignement;
}

const irr::video::SColor &indie::components::Text::getColor() const
{
    return _color;
}

void indie::components::Text::setColor(const irr::video::SColor &color)
{
    _color = color;
}

const irr::video::SColor &indie::components::Text::getBackgroundColor() const
{
    return _backgroundColor;
}

void indie::components::Text::setBackgroundColor(const irr::video::SColor &backgroundColor)
{
    _backgroundColor = backgroundColor;
}

indie::components::Text &indie::components::Text::operator>>(std::ostream &file)
{
    file << R"(        <component type="Text">)" << std::endl;
    file << R"(            <argument name="text" value=")" << _text << R"("/>)" << std::endl;
    file << R"(            <argument name="horizontalAlignement" value=")" << _horizontalAlignement << R"("/>)" << std::endl;
    file << R"(            <argument name="verticalAlignement" value=")" << _verticalAlignement << R"("/>)" << std::endl;
    file << R"(            <argument name="color" value=")" << _color << R"("/>)" << std::endl;
    file << R"(            <argument name="backgroundColor" value=")" << _backgroundColor << R"("/>)" << std::endl;
    file << R"(            <argument name="id" value=")" << _id << R"("/>)" << std::endl;
    file << "        </component>" << std::endl;
    return *this;
}

std::ostream &indie::components::operator<<(std::ostream &file, indie::components::Text::HorizontalAlignement alignement)
{
    if (alignement == Text::LEFT) {
        file << "LEFT";
    } else if (alignement == Text::RIGHT) {
        file << "RIGHT";
    } else {
        file << "CENTER";
    }
    return file;
}

std::ostream &indie::components::operator<<(std::ostream &file, indie::components::Text::VerticalAlignement alignement)
{
    if (alignement == Text::TOP) {
        file << "TOP";
    } else if (alignement == Text::BOTTOM) {
        file << "BOTTOM";
    } else {
        file << "CENTER";
    }
    return file;
}
