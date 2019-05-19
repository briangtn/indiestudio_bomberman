/*
** EPITECH PROJECT, 2018
** Shaders
** File description:
** Transform2D.cpp
*/

//
// Created by romainfouyer on 5/13/19.
//

#ifndef INDIESTUDIO_SHADERS_HPP
#define INDIESTUDIO_SHADERS_HPP

#include <irrlicht.h>

namespace indie {
    class Shaders : public irr::video::IShaderConstantSetCallBack {
    public:
        virtual void OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData);
    };
}

#endif //INDIESTUDIO_SHADERS_HPP
