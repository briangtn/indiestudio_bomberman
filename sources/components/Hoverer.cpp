/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Hoverer.cpp
*/

/* Created the 24/05/2019 at 14:28 by jfrabel */

#include <iomanip>
#include "Events.hpp"
#include "components/Hoverer.hpp"

indie::components::Hoverer::Hoverer(jf::entities::Entity &entity)
    : Component(entity), _speed(), _amplitude(), _advancement()
{
    EMIT_CREATE(Hoverer);
}

indie::components::Hoverer::Hoverer(jf::entities::Entity &entity, const indie::maths::Vector3D &speed, const indie::maths::Vector3D &amplitude)
    : Component(entity), _speed(speed), _amplitude(amplitude), _advancement()
{
    EMIT_CREATE(Hoverer);
}

indie::components::Hoverer::~Hoverer()
{
    EMIT_DELETE(Hoverer);
}

void indie::components::Hoverer::setSpeed(const indie::maths::Vector3D &speed)
{
    _speed = speed;
}

indie::maths::Vector3D indie::components::Hoverer::getSpeed() const
{
    return _speed;
}

void indie::components::Hoverer::setAmplitude(const indie::maths::Vector3D &amplitude)
{
    _amplitude = amplitude;
}

const indie::maths::Vector3D &indie::components::Hoverer::getAmplitude() const
{
    return _amplitude;
}

void indie::components::Hoverer::setAdvancement(const indie::maths::Vector3D &advancement)
{
    _advancement = advancement;
}

const indie::maths::Vector3D &indie::components::Hoverer::getAdvancement() const
{
    return _advancement;
}

std::ostream &indie::components::Hoverer::operator<<(std::ostream &file)
{
    file << std::setw(8) << R"(<component type="Hoverer">)" << std::endl;
    file << std::setw(12) << R"(<argument name="speed" value=")" << _speed << R"("/>)" << std::endl;
    file << std::setw(12) << R"(<argument name="amplitude" value=")" << _amplitude << R"("/>)" << std::endl;
    file << std::setw(12) << R"(<argument name="advancement" value=")" << _advancement << R"("/>)" << std::endl;
    file << std::setw(8) << "</component>" << std::endl;
    return file;
}
