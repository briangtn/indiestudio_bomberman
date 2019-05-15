/*
** EPITECH PROJECT, 2018
** JFEntityComponentSystem
** File description:
** Transform2D.cpp
*/

/* Created the 02/05/2019 at 15:25 by jfrabel */

#include "Events.hpp"
#include "Transform.hpp"

/* ================================================================================================================ */
/* ----------------------------------------------------Ctor&Dtor--------------------------------------------------- */
/* ================================================================================================================ */


jf::components::Transform::Transform(jf::entities::Entity &entity, jf::maths::Vector3D position, jf::maths::Vector3D rotation, jf::maths::Vector3D scale)
    : Component(entity), _position(position), _rotation(rotation), _scale(scale)
{
    EMIT_CREATE(Transform);
}

jf::components::Transform::~Transform()
{
    EMIT_DELETE(Transform);
}

/* ================================================================================================================ */
/* -----------------------------------------------Setters and Getters---------------------------------------------- */
/* ================================================================================================================ */

const jf::maths::Vector3D &jf::components::Transform::getPosition() const
{
    return _position;
}

void jf::components::Transform::setPosition(const jf::maths::Vector3D &position)
{
    _position = position;
}

const jf::maths::Vector3D &jf::components::Transform::getRotation() const
{
    return _rotation;
}

void jf::components::Transform::setRotation(const jf::maths::Vector3D &rotation)
{
    _rotation = rotation;
}

const jf::maths::Vector3D &jf::components::Transform::getScale() const
{
    return _scale;
}

void jf::components::Transform::setScale(const jf::maths::Vector3D &scale)
{
    _scale = scale;
}
