/*
** EPITECH PROJECT, 2018
** JFEntityComponentSystem
** File description:
** Material.hpp
*/

//
// Created by romainfouyer on 5/13/19.
//

#ifndef INDIESTUDIO_MATERIAL_HPP
#define INDIESTUDIO_MATERIAL_HPP

#include <map>
#include <irrlicht.h>
#include <string>
#include "Component.hpp"

#define DEFAULT_MATERIAL_FLAGS {\
{irr::video::EMF_WIREFRAME, false},\
{irr::video::EMF_POINTCLOUD, false},\
{irr::video::EMF_GOURAUD_SHADING, true},\
{irr::video::EMF_LIGHTING, true},\
{irr::video::EMF_ZBUFFER, true},\
{irr::video::EMF_ZWRITE_ENABLE, true},\
{irr::video::EMF_BACK_FACE_CULLING, true},\
{irr::video::EMF_FRONT_FACE_CULLING, false},\
{irr::video::EMF_BILINEAR_FILTER, true},\
{irr::video::EMF_TRILINEAR_FILTER, false},\
{irr::video::EMF_ANISOTROPIC_FILTER, false},\
{irr::video::EMF_FOG_ENABLE, false},\
{irr::video::EMF_NORMALIZE_NORMALS, false},\
{irr::video::EMF_TEXTURE_WRAP, false},\
{irr::video::EMF_ANTI_ALIASING, true},\
{irr::video::EMF_COLOR_MASK, true},\
{irr::video::EMF_COLOR_MATERIAL, true},\
{irr::video::EMF_USE_MIP_MAPS, true},\
{irr::video::EMF_BLEND_OPERATION, false},\
{irr::video::EMF_POLYGON_OFFSET, false}\
}

namespace indie {

    namespace components {

        class Material : public jf::components::Component {
        public:
            explicit Material(jf::entities::Entity &entity,
                              const std::string &materialTexture,
                              irr::video::E_MATERIAL_TYPE materialType = irr::video::EMT_SOLID);
            ~Material() override;

            irr::video::E_MATERIAL_TYPE getMaterialType() const;
            void setMaterialType(irr::video::E_MATERIAL_TYPE type);

            std::string getMaterialTexture() const;
            void setMaterialTexture(const std::string &textureName);

            std::map<irr::video::E_MATERIAL_FLAG, bool> &getMaterialFlags();
            const std::map<irr::video::E_MATERIAL_FLAG, bool> &getMaterialFlags() const;
            bool getMaterialFlag(irr::video::E_MATERIAL_FLAG) const;
            void setMaterialFlag(irr::video::E_MATERIAL_FLAG materialFlag, bool value);

            bool hasMaterialChanged() const;
            bool hasMaterialTextureChanged() const;
            bool hasMaterialFlagsChanged() const;
            bool hasMaterialTypeChanged() const;
            void resetHasMaterialChanged();

            std::ostream &operator<<(std::ostream &file);

        private:
            irr::video::E_MATERIAL_TYPE _materialType;
            bool _materialTypeChanged;
            std::string _materialTexture;
            bool _materialTextureChanged;
            std::map<irr::video::E_MATERIAL_FLAG, bool> _materialFlags;
            bool _materialFlagsChanged;

            static const std::map<irr::video::E_MATERIAL_TYPE, std::string> materialTypes;
            static const std::map<irr::video::E_MATERIAL_FLAG, std::string> materialFlags;
        };
    }
}


#endif //INDIESTUDIO_MATERIAL_HPP
