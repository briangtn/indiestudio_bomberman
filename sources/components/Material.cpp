/*
** EPITECH PROJECT, 2018
** JFEntityComponentSystem
** File description:
** Material.cpp
*/

//
// Created by romainfouyer on 5/13/19.
//

#include "components/Material.hpp"
#include "Events.hpp"

indie::components::Material::Material(jf::entities::Entity &entity,
                                      const std::string &materialTexture,
                                      irr::video::E_MATERIAL_TYPE materialType)
: jf::components::Component(entity),
  _materialType(materialType),
  _materialTypeChanged(true),
  _materialTexture(materialTexture),
  _materialTextureChanged(true),
  _materialFlags(DEFAULT_MATERIAL_FLAGS),
  _materialFlagsChanged(true)
{
    EMIT_CREATE(Material);
}

indie::components::Material::~Material()
{
    EMIT_DELETE(Material);
}

void indie::components::Material::setMaterialType(irr::video::E_MATERIAL_TYPE type)
{
    _materialType = type;
    _materialTypeChanged = true;
}

void indie::components::Material::setMaterialTexture(const std::string &textureName)
{
    _materialTexture = textureName;
    _materialTextureChanged = true;
}

void indie::components::Material::setMaterialFlag(irr::video::E_MATERIAL_FLAG materialFlag, bool value)
{
    _materialFlags[materialFlag] = value;
    _materialFlagsChanged = true;
}

irr::video::E_MATERIAL_TYPE indie::components::Material::getMaterialType() const
{
    return _materialType;
}

std::string indie::components::Material::getMaterialTexture() const
{
    return _materialTexture;
}

std::map<irr::video::E_MATERIAL_FLAG, bool> &indie::components::Material::getMaterialFlags()
{
    return _materialFlags;
}

const std::map<irr::video::E_MATERIAL_FLAG, bool> &indie::components::Material::getMaterialFlags() const
{
    return _materialFlags;
}

bool indie::components::Material::getMaterialFlag(irr::video::E_MATERIAL_FLAG materialFlag) const
{
    return _materialFlags.at(materialFlag);
}

bool indie::components::Material::hasMaterialChanged() const
{
    return _materialFlagsChanged || _materialTextureChanged || _materialTypeChanged;
}

void indie::components::Material::resetHasMaterialChanged()
{
    _materialFlagsChanged = false;
    _materialTextureChanged = false;
    _materialTypeChanged = false;
}

bool indie::components::Material::hasMaterialTextureChanged() const
{
    return _materialTextureChanged;
}

bool indie::components::Material::hasMaterialFlagsChanged() const
{
    return _materialFlagsChanged;
}

bool indie::components::Material::hasMaterialTypeChanged() const
{
    return _materialTypeChanged;
}