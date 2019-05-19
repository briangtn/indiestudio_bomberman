/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** PointLight.cpp
*/

/* Created the 19/05/2019 at 15:46 by jfrabel */

#include "Events.hpp"
#include "components/PointLight.hpp"

indie::components::PointLight::PointLight(jf::entities::Entity &entity)
    : Component(entity),
      _castShadows(true),
      _showBillboard(true),
      _showLight(true),
      _lightColor(irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f)),
      _radius(1000.0f),
      _billboardDimensions(1, 1),
      _billboardTexture(DEFAULT_BILLBOARD_TEXTURE),
      _billboardNode(nullptr),
      _lightNode(nullptr),
      _changes(POINT_LIGHT_NO_CHANGES)
{
    EMIT_CREATE(PointLight);
}

indie::components::PointLight::~PointLight()
{
    EMIT_DELETE(PointLight);
}

bool indie::components::PointLight::isInit()
{
    return _lightNode != nullptr && _billboardNode != nullptr;
}

void indie::components::PointLight::setCastShadows(bool value)
{
    if (_castShadows == value)
        return;
    _castShadows = value;
    _changes |= POINT_LIGHT_SHOW_SHADOWS_CHANGES;
}

bool indie::components::PointLight::getCastShadows() const
{
    return _castShadows;
}

void indie::components::PointLight::setShowBillboard(bool value)
{
    if (_showBillboard == value)
        return;
    _showBillboard = value;
    _changes |= POINT_LIGHT_SHOW_BILLBOARD_CHANGES;
}

bool indie::components::PointLight::getShowBillboard() const
{
    return _showBillboard;
}

void indie::components::PointLight::setShowLight(bool value)
{
    if (_showLight == value)
        return;
    _showLight = value;
    _changes |= POINT_LIGHT_SHOW_LIGHT_CHANGES;
}

bool indie::components::PointLight::getShowLight() const
{
    return _showLight;
}

void indie::components::PointLight::setLightColot(const irr::video::SColorf &value)
{
    if (_lightColor.toSColor() == value.toSColor())
        return;
    _lightColor = value;
    _changes |= POINT_LIGHT_LIGHT_COLOR_CHANGES;
}

const irr::video::SColorf &indie::components::PointLight::getLightColor() const
{
    return _lightColor;
}

void indie::components::PointLight::setRadius(const irr::f32 &radius)
{
    if (_radius == radius)
        return;
    _radius = radius;
    _changes |= POINT_LIGHT_LIGHT_RADIUS_CHANGES;
}

const irr::f32 &indie::components::PointLight::getRadius() const
{
    return _radius;
}

void indie::components::PointLight::setBillboardDimensions(const irr::core::dimension2df &dimensions)
{
    if (_billboardDimensions == dimensions)
        return;
    _billboardDimensions = dimensions;
    _changes |= POINT_LIGHT_BILLBOARD_DIM_CHANGES;
}

const irr::core::dimension2df &indie::components::PointLight::getBillboardDimensions() const
{
    return _billboardDimensions;
}

void indie::components::PointLight::setBillboardTexture(const std::string &texture)
{
    if (_billboardTexture == texture)
        return;
    _billboardTexture = texture;
    _changes |= POINT_LIGHT_BILLBOARD_TEX_CHANGES;
}

const std::string &indie::components::PointLight::getBillboardTexture() const
{
    return _billboardTexture;
}

irr::scene::IBillboardSceneNode *indie::components::PointLight::getBillboardNode() const
{
    return _billboardNode;
}

void indie::components::PointLight::setBillboardNode(irr::scene::IBillboardSceneNode *node)
{
    _billboardNode = node;
}

irr::scene::ILightSceneNode *indie::components::PointLight::getLightNode() const
{
    return _lightNode;
}

void indie::components::PointLight::setLightNode(irr::scene::ILightSceneNode *node)
{
    _lightNode = node;
}

unsigned int indie::components::PointLight::getChanges() const
{
    return _changes;
}

void indie::components::PointLight::resetChanges()
{
    _changes = POINT_LIGHT_NO_CHANGES;
}