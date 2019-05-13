/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** IrrlichtManagerParticles
*/

/* Created the 13/05/2019 at 18:23 by Charlie Jeanneau */

#include "IrrlichtParticleSystem.hpp"
#include "ECSWrapper.hpp"
#include <iostream>

jf::IrrlichtParticleSystem::IrrlichtParticleSystem()
{
    std::cout << "IrrlichtParticleSystem Constructor" << std::endl;
}

jf::IrrlichtParticleSystem::~IrrlichtParticleSystem()
{
    std::cour << "IrrlichtParticleSystem Destructor" << std::endl;
}

void jf::IrrlichtParticleSystem::onAwake()
{
    std::cout << "IrrlichtParticleSystem onAwake" << std::endl;
}

void jf::IrrlichtParticleSystem::onStart()
{
    std::cout << "IrrlichtParticleSystem onStart" << std::endl;
}

void jf::IrrlichtParticleSystem::onUpdate(const std::chrono::nanoseconds &elapsedTime)
{
    std::cout << "IrrlichtParticleSystem elapsed time: " << elapsedTime.count() << " ns" << std::endl;
}

void jf::IrrlichtParticleSystem::onStop()
{
    std::cout << "IrrlichtParticleSystem onStop" << std::endl;
}

void jf::IrrlichtParticleSystem::onTearDown()
{
    std::cout << "IrrlichtParticleSystem onTearDown" << std::endl;
}

void jf::IrrlichtParticleSystem::setPosition(int x, int y, int z)
{
    std::cout << "IrrlichtParticleSystem setPosition: x=" << x << " y=" << y << " z=" << z << std::endl;
}

void jf::IrrlichtParticleSystem::setScale(int x, int y, int z)
{
    std::cout << "IrrlichtParticleSystem setScale: x=" << x << " y=" << y << " z=" << z << std::endl;
}

void jf::IrrlichtParticleSystem::setMaterialFlag(irr::video::E_MATERIAL_FLAG flag, bool activate)
{
    std::cout << "IrrlichtParticleSystem setMaterialFlag: videoMode=" << flag << " activate=" << activate << std::endl;
}

void jf::IrrlichtParticleSystem::setMaterialType(irr::video::E_MATERIAL_FLAG flag)
{
    std::cout << "IrrlichtParticleSysyem setMaterialType: videoMode=" << flag << std::endl;
}

void jf::IrrlichtParticleSystem::setMaterialTexture(int number, std::string texture_name)
{
    std::cout << "IrrlichtParticleSystem setMaterialTexture: number= " << number << " textureName= " << texture_name << std::endl;
}