/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Image.cpp
*/

/* Created the 06/06/2019 at 14:43 by brian */

#include "components/GUI/Image.hpp"

indie::components::Image::Image(jf::entities::Entity &entity, const std::string &path)
    :   Component(entity), _path(path), _textureNode(nullptr)
{

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

bool indie::components::Image::isTextureInit() const
{
    return _textureNode;
}