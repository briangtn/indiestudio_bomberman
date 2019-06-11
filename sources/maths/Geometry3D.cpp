/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Aabb.cpp
*/

/* Created the 29/05/2019 at 12:45 by jfrabel */

#include <cmath>
#include "maths/Geometry3D.hpp"

#define CLAMP(nb, min, max) (nb = ((nb < min) ? min : ((nb > max) ? max : nb)))

bool indie::maths::OverlapOnAxis(
    const indie::maths::ISATAble &satAbleA,
    const indie::maths::ISATAble &satAbleB,
    const indie::maths::Vector3D &axis)
{
    Interval a = satAbleA.getInterval(axis);
    Interval b = satAbleB.getInterval(axis);
    return b.min <= a.max && a.min <= b.max;
}

indie::maths::AABB::AABB()
    : origin(), size(1, 1, 1)
{

}

indie::maths::AABB::AABB(const indie::maths::Point &o, const indie::maths::Vector3D &s)
    : origin(o), size(s)
{

}

indie::maths::Point indie::maths::AABB::min() const
{
    return GetMin(*this);
}

indie::maths::Point indie::maths::AABB::max() const
{
    return GetMax(*this);
}

indie::maths::AABB indie::maths::AABB::fromMinMax(const indie::maths::Point &min, const indie::maths::Point &max)
{
    return FromMinMax(min, max);
}

bool indie::maths::AABB::collides(const indie::maths::Point &point) const
{
    return PointInAABB(point, *this);
}

indie::maths::Point indie::maths::AABB::closest(const indie::maths::Point &point) const
{
    return ClosestPoint(point, *this);
}

bool indie::maths::AABB::collides(const indie::maths::AABB &aabb) const
{
    return AABBAABBCollision(aabb, *this);
}

indie::maths::Interval indie::maths::AABB::getInterval(const indie::maths::Vector3D &axis) const
{
    Vector3D pMin = min();
    Vector3D pMax = max();

    Vector3D vertices[8] = {
        Vector3D(pMin.x, pMax.y, pMax.z),
        Vector3D(pMin.x, pMax.y, pMin.z),
        Vector3D(pMin.x, pMin.y, pMax.z),
        Vector3D(pMin.x, pMin.y, pMin.z),
        Vector3D(pMax.x, pMax.y, pMax.z),
        Vector3D(pMax.x, pMax.y, pMin.z),
        Vector3D(pMax.x, pMin.y, pMax.z),
        Vector3D(pMax.x, pMin.y, pMin.z),
    };

    Interval result;
    result.min = Vector3D::Dot(axis, vertices[0]);
    result.max = result.min;
    for (int i = 1; i < 8; ++i) {
        float projection = Vector3D::Dot(axis, vertices[i]);
        result.min = (projection < result.min) ? projection : result.min;
        result.max = (projection > result.max) ? projection : result.max;
    }
    return result;
}

bool indie::maths::AABB::collides(const indie::maths::OBB &obb) const
{
    return AABBOBBCollision(*this, obb);
}

indie::maths::Point indie::maths::GetMin(const indie::maths::AABB &aabb)
{
    Point p1 = aabb.origin + aabb.size;
    Point p2 = aabb.origin - aabb.size;

    return indie::maths::Point(fminf(p1.x, p2.x), fminf(p1.y, p2.y), fminf(p1.z, p2.z));
}

indie::maths::Point indie::maths::GetMax(const indie::maths::AABB &aabb)
{
    Point p1 = aabb.origin + aabb.size;
    Point p2 = aabb.origin - aabb.size;

    return indie::maths::Point(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y), fmaxf(p1.z, p2.z));
}

indie::maths::AABB indie::maths::FromMinMax(const indie::maths::Point &min, const indie::maths::Point &max)
{
    return indie::maths::AABB((min + max) * 0.5f, (max - min) * 0.5f);
}

bool indie::maths::PointInAABB(const indie::maths::Point &point, const indie::maths::AABB &aabb)
{
    Point min = aabb.min();
    Point max = aabb.max();

    return !(point.x < min.x || point.y < min.y || point.z < min.z || point.x > max.x || point.y > max.y || point.z > max.z);
}

indie::maths::Point indie::maths::ClosestPoint(const indie::maths::Point &point, const indie::maths::AABB &aabb)
{
    Point result = point;
    Point min = aabb.min();
    Point max = aabb.max();

    CLAMP(result.x, min.x, max.x);
    CLAMP(result.y, min.y, max.y);
    CLAMP(result.z, min.z, max.z);
    return result;
}

bool indie::maths::AABBAABBCollision(const indie::maths::AABB &aabb1, const indie::maths::AABB &aabb2)
{
    Point aMin = aabb1.min();
    Point aMax = aabb1.max();
    Point bMin = aabb2.min();
    Point bMax = aabb2.max();

    return aMin.x <= bMin.x && aMax.x >= bMin.x && aMin.y <= bMax.y && aMax.y >= bMin.y && aMin.z <= bMax.z && aMax.z >= bMin.z;
}

indie::maths::OBB::OBB()
    : origin(), size(1, 1, 1), orientation()
{

}

indie::maths::OBB::OBB(const indie::maths::Point &o, const indie::maths::Vector3D &s)
    : origin(o), size(s), orientation()
{

}

indie::maths::OBB::OBB(const indie::maths::Point &o, const indie::maths::Vector3D &s, const indie::maths::Matrix3 &m)
    : origin(o), size(s), orientation(m)
{

}

bool indie::maths::OBB::collides(const indie::maths::Point &point) const
{
    return PointInOBB(point, *this);
}

indie::maths::Point indie::maths::OBB::closest(const indie::maths::Point &point) const
{
    return ClosestPoint(point, *this);
}

indie::maths::Interval indie::maths::OBB::getInterval(const indie::maths::Vector3D &axis) const
{
    Vector3D vertices[8];
    const float *o = orientation.asArray;
    Vector3D axes[] = {
        Vector3D(o[0], o[1], o[2]),
        Vector3D(o[3], o[4], o[5]),
        Vector3D(o[6], o[7], o[8]),
    };
    vertices[0] = origin + axes[0] * size[0] + axes[1] * size[1] + axes[2] * size[2];
    vertices[1] = origin - axes[0] * size[0] + axes[1] * size[1] + axes[2] * size[2];
    vertices[2] = origin + axes[0] * size[0] - axes[1] * size[1] + axes[2] * size[2];
    vertices[3] = origin + axes[0] * size[0] + axes[1] * size[1] - axes[2] * size[2];
    vertices[4] = origin - axes[0] * size[0] - axes[1] * size[1] - axes[2] * size[2];
    vertices[5] = origin + axes[0] * size[0] - axes[1] * size[1] - axes[2] * size[2];
    vertices[6] = origin - axes[0] * size[0] + axes[1] * size[1] - axes[2] * size[2];
    vertices[7] = origin - axes[0] * size[0] - axes[1] * size[1] + axes[2] * size[2];
    Interval result;
    result.min = Vector3D::Dot(axis, vertices[0]);
    result.max = result.min;
    for (int i = 1; i < 8; ++i) {
        float projection = Vector3D::Dot(axis, vertices[i]);
        result.min = (projection < result.min) ? projection : result.min;
        result.max = (projection > result.max) ? projection : result.max;
    }
    return result;
}

bool indie::maths::OBB::collides(const indie::maths::OBB &obb) const
{
    return OBBOBBCollision(obb, *this);
}

bool indie::maths::OBB::collides(const indie::maths::AABB &aabb) const
{
    return AABBOBBCollision(aabb, *this);
}

bool indie::maths::PointInOBB(const indie::maths::Point &point, const indie::maths::OBB &obb)
{
    Vector3D direction = point - obb.origin;
    for (int i = 0; i < 3; ++i) {
        const float *orientation = &obb.orientation.asArray[i * 3];
        Vector3D axis(orientation[0], orientation[1], orientation[2]);
        float distance = Vector3D::Dot(direction, axis);
        if (distance > obb.size.asArray[i] || distance < -obb.size.asArray[i])
            return false;
    }
    return true;
}

indie::maths::Point indie::maths::ClosestPoint(const indie::maths::Point &point, const indie::maths::OBB &obb)
{
    Point result = obb.origin;
    Vector3D direction = point - obb.origin;
    for (int i = 0; i < 3; ++i) {
        const float *orientation = &obb.orientation.asArray[i * 3];
        Vector3D axis(orientation[0], orientation[1], orientation[2]);
        float distance = Vector3D::Dot(direction, axis);
        CLAMP(distance, -obb.size.asArray[i], obb.size.asArray[i]);
        result = result + (axis * distance);
    }
    return result;
}

bool indie::maths::AABBOBBCollision(const indie::maths::AABB &aabb, const indie::maths::OBB &obb)
{
    const float *o = obb.orientation.asArray;

    Vector3D testAxes[15] = {
        Vector3D(1, 0, 0),
        Vector3D(0, 1, 0),
        Vector3D(0, 0, 1),
        Vector3D(o[0], o[1], o[2]),
        Vector3D(o[3], o[4], o[5]),
        Vector3D(o[6], o[7], o[8]),
    };
    for (int i = 0; i < 3; ++i) {
        testAxes[6 + i * 3 + 0] = Vector3D::Cross(testAxes[i], testAxes[0]);
        testAxes[6 + i * 3 + 1] = Vector3D::Cross(testAxes[i], testAxes[1]);
        testAxes[6 + i * 3 + 2] = Vector3D::Cross(testAxes[i], testAxes[2]);
    }
    for (auto testAxis : testAxes) {
        if (!OverlapOnAxis(aabb, obb, testAxis))
            return false;
    }
    return true;
}

bool indie::maths::OBBOBBCollision(const indie::maths::OBB &obb1, const indie::maths::OBB &obb2)
{
    const float* o1 = obb1.orientation.asArray;
    const float* o2 = obb2.orientation.asArray;

    Vector3D testAxes[15] = {
        Vector3D(o1[0], o1[1], o1[2]),
        Vector3D(o1[3], o1[4], o1[5]),
        Vector3D(o1[6], o1[7], o1[8]),
        Vector3D(o2[0], o2[1], o2[2]),
        Vector3D(o2[3], o2[4], o2[5]),
        Vector3D(o2[6], o2[7], o2[8])
    };
    for (int i = 0; i < 3; ++i) {
        testAxes[6 + i * 3 + 0] = Vector3D::Cross(testAxes[i], testAxes[0]);
        testAxes[6 + i * 3 + 1] = Vector3D::Cross(testAxes[i], testAxes[1]);
        testAxes[6 + i * 3 + 2] = Vector3D::Cross(testAxes[i], testAxes[2]);
    }
    for (auto testAxis : testAxes) {
        if (!OverlapOnAxis(obb1, obb2, testAxis)) {
            return false;
        }
    }
    return true;
}
