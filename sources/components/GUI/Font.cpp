/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Font.cpp
*/

/* Created the 03/06/2019 at 21:45 by brian */

#include <ECSWrapper.hpp>
#include <events/IrrlichtClosingWindowEvent.hpp>
#include "Events.hpp"
#include "components/GUI/Font.hpp"

indie::components::Font::Font(jf::entities::Entity &entity, const std::string &path)
    :   Component(entity),
        _path(path),
        _fontNode(nullptr)
{
    ECSWrapper ecs;
    _eventCloseID = ecs.eventManager.addListener<Font, events::IrrlichtClosingWindowEvent>(this, [](Font *font, events::IrrlichtClosingWindowEvent e){
        font->_fontNode = nullptr;
    });
    EMIT_CREATE(Font);
}

indie::components::Font::~Font()
{
    EMIT_DELETE(Font);
    ECSWrapper ecs;
    ecs.eventManager.removeListener(_eventCloseID);
}

const std::string &indie::components::Font::getPath() const
{
    return _path;
}

void indie::components::Font::setPath(const std::string &path)
{
    _path = path;
}

irr::gui::IGUIFont *indie::components::Font::getFontNode() const
{
    return _fontNode;
}

void indie::components::Font::setFontNode(irr::gui::IGUIFont *fontNode)
{
    _fontNode = fontNode;
}

bool indie::components::Font::isInit() const
{
    return _fontNode != nullptr;
}

indie::components::Font &indie::components::Font::operator>>(std::ostream &file)
{
    file << R"(        <component type="Font">)" << std::endl;
    file << R"(            <argument name="fileName" value=")" << _path << R"("/>)" << std::endl;
    file << "        </component>" << std::endl;
    return *this;
}
