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

#include "Component.hpp"
#include <irrlicht.h>
#include <string>

namespace indie {

    namespace components {

        enum MaterialType
        {
            SOLID,
            ADDITIVE
        };

        class Material : public jf::components::Component {
        public:
            explicit Material(jf::entities::Entity &entity, const std::string &materialTexture, components::MaterialType materialType, irr::video::E_MATERIAL_FLAG materialFlag);
            ~Material() override;

            components::MaterialType getMaterialType() const;
            void setMaterialType(components::MaterialType type);

            std::string getMaterialTexture() const;
            void setMaterialTexture(const std::string &textureName);

            irr::video::E_MATERIAL_FLAG getMaterialFlag() const;
            void setMaterialFlag(irr::video::E_MATERIAL_FLAG materialFlag);

        private:
            components::MaterialType _materialType;
            std::string _materialTexture;
            irr::video::E_MATERIAL_FLAG _materialFlag;
        };
    }
}


#endif //INDIESTUDIO_MATERIAL_HPP
