/*
** EPITECH PROJECT, 2018
** JFEntityComponentSystem
** File description:
** Material.cpp
*/

//
// Created by romainfouyer on 5/13/19.
//

#include <iomanip>
#include "components/Material.hpp"
#include "Events.hpp"
#include "parser/Parser.hpp"

const std::map<irr::video::E_MATERIAL_TYPE, std::string> indie::components::Material::materialTypes = {
        {irr::video::EMT_SOLID, "EMT_SOLID"},
        {irr::video::EMT_SOLID_2_LAYER, "EMT_SOLID_2_LAYER"},
        {irr::video::EMT_LIGHTMAP, "EMT_LIGHTMAP"},
        {irr::video::EMT_LIGHTMAP_ADD, "EMT_LIGHTMAP_ADD"},
        {irr::video::EMT_LIGHTMAP_M2, "EMT_LIGHTMAP_M2"},
        {irr::video::EMT_LIGHTMAP_M4, "EMT_LIGHTMAP_M4"},
        {irr::video::EMT_LIGHTMAP_LIGHTING, "EMT_LIGHTMAP_LIGHTING"},
        {irr::video::EMT_LIGHTMAP_LIGHTING_M2, "EMT_LIGHTMAP_LIGHTING_M2"},
        {irr::video::EMT_LIGHTMAP_LIGHTING_M4, "EMT_LIGHTMAP_LIGHTING_M4"},
        {irr::video::EMT_DETAIL_MAP, "EMT_DETAIL_MAP"},
        {irr::video::EMT_SPHERE_MAP, "EMT_SPHERE_MAP"},
        {irr::video::EMT_REFLECTION_2_LAYER, "EMT_REFLECTION_2_LAYER"},
        {irr::video::EMT_TRANSPARENT_ADD_COLOR, "EMT_TRANSPARENT_ADD_COLOR"},
        {irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL, "EMT_TRANSPARENT_ALPHA_CHANNEL"},
        {irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF, "EMT_TRANSPARENT_ALPHA_CHANNEL_REF"},
        {irr::video::EMT_TRANSPARENT_VERTEX_ALPHA, "EMT_TRANSPARENT_VERTEX_ALPHA"},
        {irr::video::EMT_TRANSPARENT_REFLECTION_2_LAYER, "EMT_TRANSPARENT_REFLECTION_2_LAYER"},
        {irr::video::EMT_NORMAL_MAP_SOLID, "EMT_NORMAL_MAP_SOLID"},
        {irr::video::EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR, "EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR"},
        {irr::video::EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA, "EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA"},
        {irr::video::EMT_PARALLAX_MAP_SOLID, "EMT_PARALLAX_MAP_SOLID"},
        {irr::video::EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR, "EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR"},
        {irr::video::EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA, "EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA"},
        {irr::video::EMT_ONETEXTURE_BLEND, "EMT_ONETEXTURE_BLEND"}
};

const std::map<irr::video::E_MATERIAL_FLAG, std::string> indie::components::Material::materialFlags = {
        {irr::video::EMF_WIREFRAME, "EMF_WIREFRAME"},
        {irr::video::EMF_POINTCLOUD, "EMF_POINTCLOUD"},
        {irr::video::EMF_GOURAUD_SHADING, "EMF_GOURAUD_SHADING"},
        {irr::video::EMF_LIGHTING, "EMF_LIGHTING"},
        {irr::video::EMF_ZBUFFER, "EMF_ZBUFFER"},
        {irr::video::EMF_ZWRITE_ENABLE, "EMF_ZWRITE_ENABLE"},
        {irr::video::EMF_BACK_FACE_CULLING, "EMF_BACK_FACE_CULLING"},
        {irr::video::EMF_FRONT_FACE_CULLING, "EMF_FRONT_FACE_CULLING"},
        {irr::video::EMF_BILINEAR_FILTER, "EMF_BILINEAR_FILTER"},
        {irr::video::EMF_TRILINEAR_FILTER, "EMF_TRILINEAR_FILTER"},
        {irr::video::EMF_ANISOTROPIC_FILTER, "EMF_ANISOTROPIC_FILTER"},
        {irr::video::EMF_FOG_ENABLE, "EMF_FOG_ENABLE"},
        {irr::video::EMF_NORMALIZE_NORMALS, "EMF_NORMALIZE_NORMALS"},
        {irr::video::EMF_TEXTURE_WRAP, "EMF_TEXTURE_WRAP"},
        {irr::video::EMF_ANTI_ALIASING, "EMF_ANTI_ALIASING"},
        {irr::video::EMF_COLOR_MASK, "EMF_COLOR_MASK"},
        {irr::video::EMF_COLOR_MATERIAL, "EMF_COLOR_MATERIAL"},
        {irr::video::EMF_USE_MIP_MAPS, "EMF_USE_MIP_MAPS"},
        {irr::video::EMF_BLEND_OPERATION, "EMF_BLEND_OPERATION"},
        {irr::video::EMF_POLYGON_OFFSET, "EMF_POLYGON_OFFSET"}
};

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

indie::components::Material &indie::components::Material::operator>>(std::ostream &file)
{
    std::map<irr::video::E_MATERIAL_FLAG, bool> defaultMap = DEFAULT_MATERIAL_FLAGS;
    unsigned int nbFlags = 0;

    file << R"(        <component type="Material">)" << std::endl;
    file << R"(            <argument name="fileName" value=")" << _materialTexture << R"("/>)" << std::endl;
    file << R"(            <argument name="type" value=")" << materialTypes.at(_materialType) << R"("/>)" << std::endl;
    file << R"(            <argument name="flags" value=")";
    for (auto &it : _materialFlags) {
        if (it.second != defaultMap[it.first]) {
            if (nbFlags > 0) {
                file << ";";
            }
            if (!it.second) {
                file << "!" << materialFlags.at(it.first);
            } else {
                file << materialFlags.at(it.first);
            }
            nbFlags++;
        }
    }
    file << R"("/>)" << std::endl;
    file << R"(        </component>)" << std::endl;
    return *this;
}
