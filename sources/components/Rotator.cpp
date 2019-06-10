/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Rotator.cpp
*/

/* Created the 24/05/2019 at 13:58 by jfrabel */

#include <iomanip>
#include "Events.hpp"
#include "components/Rotator.hpp"

indie::components::Rotator::Rotator(jf::entities::Entity &entity)
    : Component(entity), _speed(0, 0, 0)
{
    EMIT_CREATE(Rotator);
}

indie::components::Rotator::Rotator(jf::entities::Entity &entity, float speedX, float speedY, float speedZ)
    : Component(entity), _speed(speedX, speedY, speedZ)
{
    EMIT_CREATE(Rotator);
}

indie::components::Rotator::Rotator(jf::entities::Entity &entity, const indie::maths::Vector3D &speed)
    : Component(entity), _speed(speed)
{
    EMIT_CREATE(Rotator);
}

indie::components::Rotator::~Rotator()
{
    EMIT_DELETE(Rotator);
}

void indie::components::Rotator::setSpeed(const indie::maths::Vector3D &speed)
{
    _speed = speed;
}

const indie::maths::Vector3D &indie::components::Rotator::getSpeed() const
{
    return _speed;
}

void indie::components::Rotator::setSpeedX(float speedX)
{
    _speed.x = speedX;
}

float indie::components::Rotator::getSpeedX() const
{
    return _speed.x;
}

void indie::components::Rotator::setSpeedY(float speedY)
{
    _speed.y = speedY;
}

float indie::components::Rotator::getSpeedY() const
{
    return _speed.y;
}

void indie::components::Rotator::setSpeedZ(float speedZ)
{
    _speed.z = speedZ;
}

float indie::components::Rotator::getSpeedZ() const
{
    return _speed.z;
}

std::ostream &indie::components::Rotator::operator<<(std::ostream &file)
{
    file << std::setw(8) << R"(<component type="Rotator"/>)" << std::endl;
    file << std::setw(12) << R"(<argument name="speed" value=")" << _speed << R"("/>)" << std::endl;
    file << std::setw(8) << "</component>" << std::endl;
    return file;
}
