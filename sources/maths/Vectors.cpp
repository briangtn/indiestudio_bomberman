/*
** EPITECH PROJECT, 2018
** indieEntityComponentSystem
** File description:
** Vectors.cpp
*/

/* Created the 24/04/2019 at 23:23 by indierabel */

#include <cmath>
#include <cfloat>
#include "maths/Vectors.hpp"

#define CMP(x, y)  (fabsf((x) - (y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

/* ================================================================================================================ */
/* ----------------------------------------------------Vector2D---------------------------------------------------- */
/* ================================================================================================================ */

indie::maths::Vector2D::Vector2D(): x(0), y(0)
{

}

indie::maths::Vector2D::Vector2D(float value): x(value), y(value)
{

}

indie::maths::Vector2D::Vector2D(float _x, float _y): x(_x), y(_y)
{

}

float &indie::maths::Vector2D::operator[](int i)
{
    return asArray[i];
}

const float &indie::maths::Vector2D::operator[](int i) const
{
    return asArray[i];
}

float indie::maths::Vector2D::magnitude() const
{
    return Magnitude(*this);
}

float indie::maths::Vector2D::magnitudeSq() const
{
    return MagnitudeSq(*this);
}

void indie::maths::Vector2D::normalize()
{
    Normalize(*this);
}

indie::maths::Vector2D indie::maths::Vector2D::normalized() const
{
    return Normalized(*this);
}

float indie::maths::Vector2D::Dot(const indie::maths::Vector2D &lhs, const indie::maths::Vector2D &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float indie::maths::Vector2D::Magnitude(const indie::maths::Vector2D &vec)
{
    return sqrtf(Dot(vec, vec));
}

float indie::maths::Vector2D::MagnitudeSq(const indie::maths::Vector2D &vec)
{
    return Dot(vec, vec);
}

float indie::maths::Vector2D::Distance(const indie::maths::Vector2D &p1, const indie::maths::Vector2D &p2)
{
    Vector2D t = p1 - p2;
    return Magnitude(t);
}

void indie::maths::Vector2D::Normalize(indie::maths::Vector2D &vec)
{
    vec = vec * (1.0f / Magnitude(vec));
}

indie::maths::Vector2D indie::maths::Vector2D::Normalized(const indie::maths::Vector2D &vec)
{
    return vec * (1.0f / Magnitude(vec));
}

float indie::maths::Vector2D::Angle(const indie::maths::Vector2D &lhs, const indie::maths::Vector2D &rhs)
{
    float m = sqrtf(MagnitudeSq(lhs) * MagnitudeSq(rhs));
    return acos(Dot(lhs, rhs) / m);
}

indie::maths::Vector2D indie::maths::Vector2D::Project(const indie::maths::Vector2D &len, const indie::maths::Vector2D &dir)
{
    float dot = Dot(len, dir);
    float magSq = MagnitudeSq(dir);
    return dir * (dot / magSq);
}

indie::maths::Vector2D indie::maths::Vector2D::Perpendicular(const indie::maths::Vector2D &len, const indie::maths::Vector2D &dir)
{
    return len - Project(len, dir);
}

indie::maths::Vector2D indie::maths::Vector2D::Reflection(const indie::maths::Vector2D &vec, const indie::maths::Vector2D &normal)
{
    float d = Dot(vec, normal);
    return vec - normal * (d * 2.0f);
}

indie::maths::Vector2D indie::maths::operator+(const indie::maths::Vector2D &lhs, const indie::maths::Vector2D &rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

indie::maths::Vector2D indie::maths::operator-(const indie::maths::Vector2D &lhs, const indie::maths::Vector2D &rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

indie::maths::Vector2D indie::maths::operator*(const indie::maths::Vector2D &lhs, const indie::maths::Vector2D &rhs)
{
    return {lhs.x * rhs.x, lhs.y * rhs.y};
}

indie::maths::Vector2D indie::maths::operator*(const indie::maths::Vector2D &lhs, float rhs)
{
    return {lhs.x * rhs, lhs.y * rhs};
}

bool indie::maths::operator==(const indie::maths::Vector2D &lhs, const indie::maths::Vector2D &rhs)
{
    return CMP(lhs.x, rhs.x) && CMP(lhs.y, rhs.y);
}

bool indie::maths::operator!=(const indie::maths::Vector2D &lhs, const indie::maths::Vector2D &rhs)
{
    return !(lhs == rhs);
}

/* ================================================================================================================ */
/* ----------------------------------------------------Vector3D---------------------------------------------------- */
/* ================================================================================================================ */

indie::maths::Vector3D::Vector3D(): x(0), y(0), z(0)
{

}

indie::maths::Vector3D::Vector3D(float value): x(value), y(value), z(value)
{

}

indie::maths::Vector3D::Vector3D(float _x, float _y, float _z): x(_x), y(_y), z(_z)
{

}

float &indie::maths::Vector3D::operator[](int i)
{
    return asArray[i];
}

const float &indie::maths::Vector3D::operator[](int i) const
{
    return asArray[i];
}

float indie::maths::Vector3D::magnitude() const
{
    return Magnitude(*this);
}

float indie::maths::Vector3D::magnitudeSq() const
{
    return MagnitudeSq(*this);
}

void indie::maths::Vector3D::normalize()
{
    Normalize(*this);
}

indie::maths::Vector3D indie::maths::Vector3D::normalized() const
{
    return Normalized(*this);
}

float indie::maths::Vector3D::Dot(const indie::maths::Vector3D &lhs, const indie::maths::Vector3D &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float indie::maths::Vector3D::Magnitude(const indie::maths::Vector3D &vec)
{
    return sqrtf(Dot(vec, vec));
}

float indie::maths::Vector3D::MagnitudeSq(const indie::maths::Vector3D &vec)
{
    return Dot(vec, vec);
}

float indie::maths::Vector3D::Distance(const indie::maths::Vector3D &p1, const indie::maths::Vector3D &p2)
{
    Vector3D t = p1 - p2;
    return Magnitude(t);
}

void indie::maths::Vector3D::Normalize(indie::maths::Vector3D &vec)
{
    vec = vec * (1.0f / Magnitude(vec));
}

indie::maths::Vector3D indie::maths::Vector3D::Normalized(const indie::maths::Vector3D &vec)
{
    return vec * (1.0f / Magnitude(vec));
}

indie::maths::Vector3D indie::maths::Vector3D::Cross(const indie::maths::Vector3D &lhs, const indie::maths::Vector3D &rhs)
{
    Vector3D result;
    result.x = lhs.y * rhs.z - lhs.z * rhs.y;
    result.y = lhs.z * rhs.x - lhs.x * rhs.z;
    result.z = lhs.x * rhs.y - lhs.y * rhs.x;
    return result;
}

float indie::maths::Vector3D::Angle(const indie::maths::Vector3D &lhs, const indie::maths::Vector3D &rhs)
{
    float m = sqrtf(MagnitudeSq(lhs) * MagnitudeSq(rhs));
    return acos(Dot(lhs, rhs) / m);
}

indie::maths::Vector3D indie::maths::Vector3D::Project(const indie::maths::Vector3D &len, const indie::maths::Vector3D &dir)
{
    float dot = Dot(len, dir);
    float magSq = MagnitudeSq(dir);
    return dir * (dot / magSq);
}

indie::maths::Vector3D indie::maths::Vector3D::Perpendicular(const indie::maths::Vector3D &len, const indie::maths::Vector3D &dir)
{
    return len - Project(len, dir);
}

indie::maths::Vector3D indie::maths::Vector3D::Reflection(const indie::maths::Vector3D &vec, const indie::maths::Vector3D &normal)
{
    float d = Dot(vec, normal);
    return vec - normal * (d * 2.0f);
}

indie::maths::Vector3D indie::maths::operator+(const indie::maths::Vector3D &lhs, const indie::maths::Vector3D &rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

indie::maths::Vector3D indie::maths::operator-(const indie::maths::Vector3D &lhs, const indie::maths::Vector3D &rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

indie::maths::Vector3D indie::maths::operator*(const indie::maths::Vector3D &lhs, const indie::maths::Vector3D &rhs)
{
    return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

indie::maths::Vector3D indie::maths::operator*(const indie::maths::Vector3D &lhs, float rhs)
{
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

bool indie::maths::operator==(const indie::maths::Vector3D &lhs, const indie::maths::Vector3D &rhs)
{
    return CMP(lhs.x, rhs.x) && CMP(lhs.y, rhs.y) && CMP(lhs.z, rhs.z);
}

bool indie::maths::operator!=(const indie::maths::Vector3D &lhs, const indie::maths::Vector3D &rhs)
{
    return !(lhs == rhs);
}

std::ostream &indie::operator<<(std::ostream &s, const indie::maths::Vector2D &vec)
{
    s << "Vector2D(x: " << vec.x << ", y: " << vec.y << ")";
    return s;
}

std::ostream &indie::operator<<(std::ostream &s, const indie::maths::Vector3D &vec)
{
    s << "Vector3D(x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << ")";
    return s;
}
