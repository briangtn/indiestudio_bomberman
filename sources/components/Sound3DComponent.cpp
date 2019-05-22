/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Sound3DComponent.cpp
*/

/* Created the 22/05/2019 at 23:38 by jbulteau */

#include "Sound3DComponent.hpp"

indie::components::Sound3DComponent::Sound3DComponent(jf::entities::Entity &entity, const std::string &sourceFile,
                                                      indie::components::ASoundComponent::SoundType soundType,
                                                      jf::maths::Vector3D position)
    : ASoundComponent(entity, sourceFile, soundType), _position(position)
{

}

const jf::maths::Vector3D indie::components::Sound3DComponent::getPosition() const
{
    if (_sound) {
        irrklang::vec3df position = _sound->getPosition();
        return jf::maths::Vector3D(position.X, position.Y, position.Z);
    }
    return _position;
}

void indie::components::Sound3DComponent::setPosition(const jf::maths::Vector3D &position)
{
    if (_sound) {
        _sound->setPosition(irrklang::vec3df(position.x, position.y, position.z));
    }
}

const jf::maths::Vector3D indie::components::Sound3DComponent::getVelocity() const
{
    if (_sound) {
        irrklang::vec3df velocity = _sound->getVelocity();
        return jf::maths::Vector3D(velocity.X, velocity.Y, velocity.Z);
    }
    return jf::maths::Vector3D(0, 0, 0);
}

void indie::components::Sound3DComponent::setVelocity(const jf::maths::Vector3D &velocity)
{
    if (_sound) {
        _sound->setVelocity(irrklang::vec3df(velocity.x, velocity.y, velocity.z));
    }
}
