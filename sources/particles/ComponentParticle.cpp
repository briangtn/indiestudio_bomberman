/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** ComponentParticle
*/

/* Created the 14/05/2019 at 14:03 by Charlie Jeanneau */

#include "ComponentParticle.hpp"

jf::ComponentParticle::ComponentParticle(jf::entities::Entity &entity, irr::core::aabbox3d<irr::f32> emiterSize,\
irr::core::vector3df initialDirection, std::pair<int, int> emitRate, std::pair<irr::video::SColor,\
irr::video::SColor> darkBrightColor, std::pair<int, int> minMaxAge, int angle,\
std::pair<irr::core::dimension2df, irr::core::dimension2df> minMaxsize)
    : Component(entity), _emiterSize(emiterSize), _initialDirection(initialDirection), _emitRate(emitRate),\
_darkBrightColor(darkBrightColor), _minMaxAge(minMaxAge), _angle(angle), _minMaxSize(minMaxsize)
{
    EMIT_CREATE(ComponentParticle);
}

irr::core::aabbox3d<irr::f32> jf::ComponentParticle::getEmiterSize() const
{
    return _emiterSize;
}

void jf::ComponentParticle::setEmiterSize(irr::core::aabbox3d<irr::f32> emiterSize)
{
    _emiterSize = emiterSize;
}

irr::core::vector3df jf::ComponentParticle::getInitialDirection() const
{
    return _initialDirection;
}

void jf::ComponentParticle::setInitialDirection(irr::core::vector3df initialDirection)
{
    _initialDirection = initialDirection;
}

std::pair<int, int> jf::ComponentParticle::getEmitRate() const
{
    return _emitRate;
}

void jf::ComponentParticle::setEmitRate(std::pair<int, int> emitRate)
{
    _emitRate = emitRate;
}

std::pair<irr::video::SColor, irr::video::SColor> jf::ComponentParticle::getDarkBrightColor() const
{
    return _darkBrightColor;
}

void jf::ComponentParticle::setDarkBrightColor(std::pair<irr::video::SColor, irr::video::SColor> darkBrightColor)
{
    _darkBrightColor = darkBrightColor;
}

std::pair<int, int> jf::ComponentParticle::getMinMaxAge() const
{
    return _minMaxAge;
}

void jf::ComponentParticle::setMinMaxAge(std::pair<int, int> minMaxAge)
{
    _minMaxAge = minMaxAge;
}

int jf::ComponentParticle::getAngle() const
{
    return _angle;
}

void jf::ComponentParticle::setAngle(int angle)
{
    _angle = angle;
}

std::pair<irr::core::dimension2df, irr::core::dimension2df> jf::ComponentParticle::getMinMaxSize() const
{
    return _minMaxSize;
}

void jf::ComponentParticle::setMinMaxSize(std::pair<irr::core::dimension2df, irr::core::dimension2df> minMaxSize)
{
    _minMaxSize = minMaxSize;
}