/*
** EPITECH PROJECT, 2018
** JFEntityComponentSystem
** File description:
** Transform2D.cpp
*/

/* Created the 02/05/2019 at 15:25 by jfrabel */

#include <cmath>
#include <iomanip>
#include "Events.hpp"
#include "components/Transform.hpp"
#include "maths/Matrices.hpp"

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

indie::maths::Vector3D indie::components::Transform::getForward() const
{
    maths::Matrix4 rotMat = maths::Matrix4::Rotation(_rotation.x, _rotation.y, _rotation.z);
    return maths::Matrix4::MultiplyVector(maths::Vector3D(0, 0, 1), rotMat).normalized();
}

indie::maths::Vector3D indie::components::Transform::getLocalAxes() const
{
    maths::Matrix4 rotMat = maths::Matrix4::Rotation(_rotation.x, _rotation.y, _rotation.z);
    return maths::Matrix4::MultiplyVector(maths::Vector3D(1, 1, 1), rotMat).normalized();
}

void indie::components::Transform::lookAt(const indie::maths::Vector3D &point)
{
    auto forward = maths::Vector3D({0, 0, 1});
    auto target = (point - _position).normalized();
    auto cross = maths::Vector3D::Cross(forward, target);
    if (cross.magnitudeSq() != 0) {
        cross.normalize();
    } else {
        cross = maths::Vector3D(0, 1, 0);
    }
    auto angle = RAD2DEG(acosf(maths::Vector3D::Dot(forward, target)));
    auto rotation = maths::Matrix3::AxisAngle(cross, angle);
    _rotation = maths::Matrix3::ToEulerAngles(rotation);
}

void indie::components::Transform::lookAt(jf::components::ComponentHandler<indie::components::Transform> point)
{
    lookAt(point->_position);
}

std::ostream &indie::components::Transform::operator<<(std::ostream &file)
{
    file << std::setw(8) << R"(<component type="Transform">)" << std::endl;
    file << std::setw(12) << R"(<argument name="position" value=")" << _position << R"("/>)" << std::endl;
    file << std::setw(12) << R"(<argument name="rotation" value=")" << _rotation << R"("/>)" << std::endl;
    file << std::setw(12) << R"(<argument name="scale" value=")" << _scale << R"("/>)" << std::endl;
    file << std::setw(8) << "</component>" << std::endl;
    return file;
}
