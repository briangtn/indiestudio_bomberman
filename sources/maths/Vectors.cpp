/*
** EPITECH PROJECT, 2018
** JFEntityComponentSystem
** File description:
** Vectors.cpp
*/

/* Created the 24/04/2019 at 23:23 by jfrabel */

#include "Vectors.hpp"
#include <cmath>
#include <cfloat>

#define CMP(x, y)  (fabsf((x) - (y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

/* ================================================================================================================ */
/* ----------------------------------------------------Vector2D---------------------------------------------------- */
/* ================================================================================================================ */

jf::maths::Vector2D::Vector2D(): x(0), y(0)
{

}

jf::maths::Vector2D::Vector2D(float value): x(value), y(value)
{

}

jf::maths::Vector2D::Vector2D(float _x, float _y): x(_x), y(_y)
{

}

float &jf::maths::Vector2D::operator[](int i)
{
    return asArray[i];
}

const float &jf::maths::Vector2D::operator[](int i) const
{
    return asArray[i];
}

float jf::maths::Vector2D::magnitude() const
{
    return Magnitude(*this);
}

float jf::maths::Vector2D::magnitudeSq() const
{
    return MagnitudeSq(*this);
}

void jf::maths::Vector2D::normalize()
{
    Normalize(*this);
}

jf::maths::Vector2D jf::maths::Vector2D::normalized() const
{
    return Normalized(*this);
}

float jf::maths::Vector2D::Dot(const jf::maths::Vector2D &lhs, const jf::maths::Vector2D &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float jf::maths::Vector2D::Magnitude(const jf::maths::Vector2D &vec)
{
    return sqrtf(Dot(vec, vec));
}

float jf::maths::Vector2D::MagnitudeSq(const jf::maths::Vector2D &vec)
{
    return Dot(vec, vec);
}

float jf::maths::Vector2D::Distance(const jf::maths::Vector2D &p1, const jf::maths::Vector2D &p2)
{
    Vector2D t = p1 - p2;
    return Magnitude(t);
}

void jf::maths::Vector2D::Normalize(jf::maths::Vector2D &vec)
{
    vec = vec * (1.0f / Magnitude(vec));
}

jf::maths::Vector2D jf::maths::Vector2D::Normalized(const jf::maths::Vector2D &vec)
{
    return vec * (1.0f / Magnitude(vec));
}

float jf::maths::Vector2D::Angle(const jf::maths::Vector2D &lhs, const jf::maths::Vector2D &rhs)
{
    float m = sqrtf(MagnitudeSq(lhs) * MagnitudeSq(rhs));
    return acos(Dot(lhs, rhs) / m);
}

jf::maths::Vector2D jf::maths::Vector2D::Project(const jf::maths::Vector2D &len, const jf::maths::Vector2D &dir)
{
    float dot = Dot(len, dir);
    float magSq = MagnitudeSq(dir);
    return dir * (dot / magSq);
}

jf::maths::Vector2D jf::maths::Vector2D::Perpendicular(const jf::maths::Vector2D &len, const jf::maths::Vector2D &dir)
{
    return len - Project(len, dir);
}

jf::maths::Vector2D jf::maths::Vector2D::Reflection(const jf::maths::Vector2D &vec, const jf::maths::Vector2D &normal)
{
    float d = Dot(vec, normal);
    return vec - normal * (d * 2.0f);
}

jf::maths::Vector2D jf::maths::operator+(const jf::maths::Vector2D &lhs, const jf::maths::Vector2D &rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

jf::maths::Vector2D jf::maths::operator-(const jf::maths::Vector2D &lhs, const jf::maths::Vector2D &rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

jf::maths::Vector2D jf::maths::operator*(const jf::maths::Vector2D &lhs, const jf::maths::Vector2D &rhs)
{
    return {lhs.x * rhs.x, lhs.y * rhs.y};
}

jf::maths::Vector2D jf::maths::operator*(const jf::maths::Vector2D &lhs, float rhs)
{
    return {lhs.x * rhs, lhs.y * rhs};
}

bool jf::maths::operator==(const jf::maths::Vector2D &lhs, const jf::maths::Vector2D &rhs)
{
    return CMP(lhs.x, rhs.x) && CMP(lhs.y, rhs.y);
}

bool jf::maths::operator!=(const jf::maths::Vector2D &lhs, const jf::maths::Vector2D &rhs)
{
    return !(lhs == rhs);
}

/* ================================================================================================================ */
/* ----------------------------------------------------Vector3D---------------------------------------------------- */
/* ================================================================================================================ */

jf::maths::Vector3D::Vector3D(): x(0), y(0), z(0)
{

}

jf::maths::Vector3D::Vector3D(float value): x(value), y(value), z(value)
{

}

jf::maths::Vector3D::Vector3D(float _x, float _y, float _z): x(_x), y(_y), z(_z)
{

}

float &jf::maths::Vector3D::operator[](int i)
{
    return asArray[i];
}

const float &jf::maths::Vector3D::operator[](int i) const
{
    return asArray[i];
}

float jf::maths::Vector3D::magnitude() const
{
    return Magnitude(*this);
}

float jf::maths::Vector3D::magnitudeSq() const
{
    return MagnitudeSq(*this);
}

void jf::maths::Vector3D::normalize()
{
    Normalize(*this);
}

jf::maths::Vector3D jf::maths::Vector3D::normalized() const
{
    return Normalized(*this);
}

float jf::maths::Vector3D::Dot(const jf::maths::Vector3D &lhs, const jf::maths::Vector3D &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float jf::maths::Vector3D::Magnitude(const jf::maths::Vector3D &vec)
{
    return sqrtf(Dot(vec, vec));
}

float jf::maths::Vector3D::MagnitudeSq(const jf::maths::Vector3D &vec)
{
    return Dot(vec, vec);
}

float jf::maths::Vector3D::Distance(const jf::maths::Vector3D &p1, const jf::maths::Vector3D &p2)
{
    Vector3D t = p1 - p2;
    return Magnitude(t);
}

void jf::maths::Vector3D::Normalize(jf::maths::Vector3D &vec)
{
    vec = vec * (1.0f / Magnitude(vec));
}

jf::maths::Vector3D jf::maths::Vector3D::Normalized(const jf::maths::Vector3D &vec)
{
    return vec * (1.0f / Magnitude(vec));
}

jf::maths::Vector3D jf::maths::Vector3D::Cross(const jf::maths::Vector3D &lhs, const jf::maths::Vector3D &rhs)
{
    Vector3D result;
    result.x = lhs.y * rhs.z - lhs.z * rhs.y;
    result.y = lhs.z * rhs.x - lhs.x * rhs.z;
    result.z = lhs.x * rhs.y - lhs.y * rhs.x;
    return result;
}

float jf::maths::Vector3D::Angle(const jf::maths::Vector3D &lhs, const jf::maths::Vector3D &rhs)
{
    float m = sqrtf(MagnitudeSq(lhs) * MagnitudeSq(rhs));
    return acos(Dot(lhs, rhs) / m);
}

jf::maths::Vector3D jf::maths::Vector3D::Project(const jf::maths::Vector3D &len, const jf::maths::Vector3D &dir)
{
    float dot = Dot(len, dir);
    float magSq = MagnitudeSq(dir);
    return dir * (dot / magSq);
}

jf::maths::Vector3D jf::maths::Vector3D::Perpendicular(const jf::maths::Vector3D &len, const jf::maths::Vector3D &dir)
{
    return len - Project(len, dir);
}

jf::maths::Vector3D jf::maths::Vector3D::Reflection(const jf::maths::Vector3D &vec, const jf::maths::Vector3D &normal)
{
    float d = Dot(vec, normal);
    return vec - normal * (d * 2.0f);
}

jf::maths::Vector3D jf::maths::operator+(const jf::maths::Vector3D &lhs, const jf::maths::Vector3D &rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

jf::maths::Vector3D jf::maths::operator-(const jf::maths::Vector3D &lhs, const jf::maths::Vector3D &rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

jf::maths::Vector3D jf::maths::operator*(const jf::maths::Vector3D &lhs, const jf::maths::Vector3D &rhs)
{
    return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

jf::maths::Vector3D jf::maths::operator*(const jf::maths::Vector3D &lhs, float rhs)
{
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

bool jf::maths::operator==(const jf::maths::Vector3D &lhs, const jf::maths::Vector3D &rhs)
{
    return CMP(lhs.x, rhs.x) && CMP(lhs.y, rhs.y) && CMP(lhs.z, rhs.z);
}

bool jf::maths::operator!=(const jf::maths::Vector3D &lhs, const jf::maths::Vector3D &rhs)
{
    return !(lhs == rhs);
}
