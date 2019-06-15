/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Image.cpp
*/

/* Created the 06/06/2019 at 14:43 by brian */

#include "events/IrrlichtClosingWindowEvent.hpp"
#include "ECSWrapper.hpp"
#include "Events.hpp"
#include "components/GUI/Image.hpp"

indie::components::Image::Image(jf::entities::Entity &entity, const std::string &path, int id)
        :   GUIBase(entity, id),
            _path(path),
            _textureNode(nullptr),
            _imageNode(nullptr),
            _useAlpha(false),
            _needReload(false)
{
    ECSWrapper ecs;

    _eventCloseID = ecs.eventManager.addListener<Image, events::IrrlichtClosingWindowEvent>(this, [](Image *image, events::IrrlichtClosingWindowEvent e) {
        if (image->_imageNode != nullptr) {
            image->_imageNode->remove();
            image->_imageNode = nullptr;
        }
    });
    EMIT_CREATE(Image);
}

indie::components::Image::~Image()
{
    EMIT_DELETE(Image);
    ECSWrapper ecs;

    ecs.eventManager.removeListener(_eventCloseID);
    if (_imageNode != nullptr) {
        _imageNode->remove();
    }
}

const std::string &indie::components::Image::getPath() const
{
    return _path;
}

void indie::components::Image::setPath(const std::string &path)
{
    _path = path;
}

irr::video::ITexture *indie::components::Image::getTextureNode() const
{
    return _textureNode;
}

void indie::components::Image::setTextureNode(irr::video::ITexture *textureNode)
{
    _textureNode = textureNode;
}

irr::gui::IGUIImage *indie::components::Image::getImageNode() const
{
    return _imageNode;
}

void indie::components::Image::setImageNode(irr::gui::IGUIImage *imageNode)
{
    _imageNode = imageNode;
}

bool indie::components::Image::isTextureInit() const
{
    return _textureNode != nullptr;
}

bool indie::components::Image::isImageInit() const
{
    return _imageNode != nullptr;
}

bool indie::components::Image::isUseAlpha() const
{
    return _useAlpha;
}

void indie::components::Image::setUseAlpha(bool useAlpha)
{
    _useAlpha = useAlpha;
}

void indie::components::Image::reload()
{
    _needReload = true;
}

void indie::components::Image::setNeedReload(bool reload)
{
    _needReload = reload;
}

bool indie::components::Image::isWaitReload() const
{
    return _needReload;
}

indie::components::Image &indie::components::Image::operator>>(std::ostream &file)
{
    file << R"(        <component type="Image">)" << std::endl;
    file << R"(            <argument name="fileName" value=")" << _path << R"("/>)" << std::endl;
    file << "        </component>" << std::endl;
    return *this;
}
