/*
** EPITECH PROJECT, 2018
** Shaders
** File description:
** Shaders.cpp
*/

//
// Created by romainfouyer on 5/13/19.
//

#include "IrrlichtManagerSystem.hpp"
#include "ECSWrapper.hpp"
#include "Shaders.hpp"

void indie::Shaders::OnSetConstants(irr::video::IMaterialRendererServices *services, irr::s32 userData)
{
    ECSWrapper ecs;
    irr::core::vector3df camPos;
    irr::core::matrix4 viewProjection;
    irr::core::matrix4 world;
    irr::s32 TextureLayerID = 0;
    irr::video::SColorf lightColor(0.0f,1.0f,1.0f,0.0f);
    irr::core::matrix4 invWorld;

    invWorld = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getVideoDriver()->getTransform(irr::video::ETS_WORLD);
    invWorld.makeInverse();
    services->setVertexShaderConstant("mInvWorld", invWorld.pointer(), 16);
    viewProjection = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getVideoDriver()->getTransform(irr::video::ETS_PROJECTION);
    viewProjection *= ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getVideoDriver()->getTransform(irr::video::ETS_VIEW);
    viewProjection *= ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getVideoDriver()->getTransform(irr::video::ETS_WORLD);
    services->setVertexShaderConstant("mWorldViewProj", viewProjection.pointer(), 16);
    camPos = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getDevice()->getSceneManager()->getActiveCamera()->getAbsolutePosition();
    services->setVertexShaderConstant("mLightPos", reinterpret_cast<irr::f32 *>(&camPos), 3);
    services->setVertexShaderConstant("mLightColor", reinterpret_cast<irr::f32 *>(&lightColor), 4);
    world = ecs.systemManager.getSystem<jf::systems::IrrlichtManagerSystem>().getVideoDriver()->getTransform(irr::video::ETS_WORLD);
    world = world.getTransposed();
    services->setVertexShaderConstant("mTransWorld", world.pointer(), 16);
    services->setPixelShaderConstant("myTexture", &TextureLayerID, 1);
}