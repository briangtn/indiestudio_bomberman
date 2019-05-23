/*
** EPITECH PROJECT, 2018
** JFEntityComponentSystem
** File description:
** Transform2D.cpp
*/

/* Created the 02/05/2019 at 15:25 by jfrabel */

#include "Events.hpp"
#include "components/Transform.hpp"

/* ================================================================================================================ */
/* ----------------------------------------------------Ctor&Dtor--------------------------------------------------- */
/* ================================================================================================================ */


indie::components::Transform::Transform(jf::entities::Entity &entity, indie::maths::Vector3D position, indie::maths::Vector3D rotation, indie::maths::Vector3D scale)
    : Component(entity), _position(position), _rotation(rotation), _scale(scale)
{
    EMIT_CREATE(Transform);
}

indie::components::Transform::~Transform()
{
    EMIT_DELETE(Transform);
}

/* ================================================================================================================ */
/* -----------------------------------------------Setters and Getters---------------------------------------------- */
/* ================================================================================================================ */

const indie::maths::Vector3D &indie::components::Transform::getPosition() const
{
    return _position;
}

void indie::components::Transform::setPosition(const indie::maths::Vector3D &position)
{
    _position = position;
}

const indie::maths::Vector3D &indie::components::Transform::getRotation() const
{
    return _rotation;
}

void indie::components::Transform::setRotation(const indie::maths::Vector3D &rotation)
{
    _rotation = rotation;
}

const indie::maths::Vector3D &indie::components::Transform::getScale() const
{
    return _scale;
}

void indie::components::Transform::setScale(const indie::maths::Vector3D &scale)
{
    _scale = scale;
}
