/*
** EPITECH PROJECT, 2018
** JFEntityComponentSystem
** File description:
** Material.cpp
*/

//
// Created by romainfouyer on 5/13/19.
//

#include "Material.hpp"
#include "Events.hpp"

indie::components::Material::Material(jf::entities::Entity &entity, const std::string &materialTexture,
                                      irr::video::E_MATERIAL_TYPE materialType,
                                      irr::video::E_MATERIAL_FLAG materialFlag)
: jf::components::Component(entity), _materialType(materialType), _materialTexture(materialTexture), _materialFlag(materialFlag)
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
}

void indie::components::Material::setMaterialTexture(const std::string &textureName)
{
    _materialTexture = textureName;
}

void indie::components::Material::setMaterialFlag(irr::video::E_MATERIAL_FLAG materialFlag)
{
    _materialFlag = materialFlag;
}

irr::video::E_MATERIAL_TYPE indie::components::Material::getMaterialType() const
{
    return _materialType;
}

std::string indie::components::Material::getMaterialTexture() const
{
    return _materialTexture;
}

irr::video::E_MATERIAL_FLAG indie::components::Material::getMaterialFlag() const
{
    return _materialFlag;
}