/*
** EPITECH PROJECT, 2018
** indieEntityComponentSystem
** File description:
** Matrices.cpp
*/

/* Created the 25/04/2019 at 18:42 by indierabel */

#include <cmath>
#include <cfloat>
#include "maths/Matrices.hpp"

#define CMP(x, y)  (fabsf((x) - (y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

/* ================================================================================================================ */
/* ----------------------------------------------------Matrix2----------------------------------------------------- */
/* ================================================================================================================ */

indie::maths::Matrix2::Matrix2()
{
    _11 = _22 = 1.0f;
    _12 = _21 = 0.0f;
}

indie::maths::Matrix2::Matrix2(float f11, float f12, float f21, float f22)
{
    _11 = f11;
    _12 = f12;
    _21 = f21;
    _22 = f22;
}

float *indie::maths::Matrix2::operator[](int i)
{
    return &asArray[i * 2];
}

const float *indie::maths::Matrix2::operator[](int i) const
{
    return &asArray[i * 2];
}

float indie::maths::Matrix2::det() const
{
    return Determinant(*this);
}

indie::maths::Matrix2 indie::maths::Matrix2::Transpose(const indie::maths::Matrix2 &mat)
{
    Matrix2 res;
    indie::maths::Transpose(mat.asArray, res.asArray, 2, 2);
    return res;
}

float indie::maths::Matrix2::Determinant(const indie::maths::Matrix2 &mat)
{
    return mat._11 * mat._22 - mat._12 * mat._21;
}

indie::maths::Matrix2 indie::maths::Matrix2::Minor(const indie::maths::Matrix2 &mat)
{
    return Matrix2(mat._22, mat._21, mat._12, mat._11);
}

indie::maths::Matrix2 indie::maths::Matrix2::Cofactor(const indie::maths::Matrix2 &mat)
{
    Matrix2 result;
    indie::maths::Cofactor(result.asArray, Minor(mat).asArray, 2, 2);
    return result;
}

indie::maths::Matrix2 indie::maths::Matrix2::Adjugate(const indie::maths::Matrix2 &mat)
{
    return Transpose(Cofactor(mat));
}

indie::maths::Matrix2 indie::maths::Matrix2::Inverse(const indie::maths::Matrix2 &mat)
{
    float det = Determinant(mat);
    if (CMP(det, 0.0f)) {
        return Matrix2();
    }
    return Adjugate(mat) * (1.0f / det);
}

indie::maths::Matrix2 indie::maths::operator*(const indie::maths::Matrix2 &matrix, float scalar)
{
    Matrix2 result;
    for (int i = 0; i < 4; i++) {
        result.asArray[i] = matrix.asArray[i] * scalar;
    }
    return result;
}

indie::maths::Matrix2 indie::maths::operator*(const indie::maths::Matrix2 &matA, const indie::maths::Matrix2 &matB)
{
    Matrix2 result;
    indie::maths::Multiply(result.asArray, matA.asArray, 2, 2, matB.asArray, 2, 2);
    return result;
}

/* ================================================================================================================ */
/* ----------------------------------------------------Matrix3----------------------------------------------------- */
/* ================================================================================================================ */

indie::maths::Matrix3::Matrix3()
{
    _11 = _22 = _33 = 1.0f;
    _12 = _13 = _21 = _23 = _31 = _32 = 0.0f;
}

indie::maths::Matrix3::Matrix3(
    float f11, float f12, float f13,
    float f21, float f22, float f23,
    float f31, float f32, float f33)
{
    _11 = f11;
    _12 = f12;
    _13 = f13;
    _21 = f21;
    _22 = f22;
    _23 = f23;
    _31 = f31;
    _32 = f32;
    _33 = f33;
}

float *indie::maths::Matrix3::operator[](int i)
{
    return &asArray[i * 3];
}

const float *indie::maths::Matrix3::operator[](int i) const
{
    return &asArray[i * 3];
}

indie::maths::Matrix3 indie::maths::Matrix3::Transpose(const indie::maths::Matrix3 &mat)
{
    Matrix3 res;
    indie::maths::Transpose(mat.asArray, res.asArray, 3, 3);
    return res;
}

indie::maths::Matrix2 indie::maths::Matrix3::Cut(const indie::maths::Matrix3 &mat, int row, int col)
{
    Matrix2 result;
    int index = 0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == row || j == col)
                continue;
            int target = index++;
            int source = 3 * i + j;
            result.asArray[target] = mat.asArray[source];
        }
    }
    return result;
}

indie::maths::Matrix3 indie::maths::Matrix3::Minor(const indie::maths::Matrix3 &mat)
{
    Matrix3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i][j] = Matrix2::Determinant(Cut(mat, i, j));
        }
    }
    return result;
}

indie::maths::Matrix3 indie::maths::Matrix3::Cofactor(const indie::maths::Matrix3 &mat)
{
    Matrix3 result;
    indie::maths::Cofactor(result.asArray, Minor(mat).asArray, 3, 3);
    return result;
}

float indie::maths::Matrix3::Determinant(const indie::maths::Matrix3 &mat)
{
    float result = 0.0f;
    Matrix3 cofactor = Cofactor(mat);
    for (int j = 0; j < 3; ++j) {
        int index = 3 * 0 + j;
        result += mat.asArray[index] * cofactor[0][j];
    }
    return result;
}

indie::maths::Matrix3 indie::maths::Matrix3::Adjugate(const indie::maths::Matrix3 &mat)
{
    return Transpose(Cofactor(mat));
}

indie::maths::Matrix3 indie::maths::Matrix3::Inverse(const indie::maths::Matrix3 &mat)
{
    float det = Determinant(mat);
    if (CMP(det, 0.0f)) {
        return Matrix3();
    }
    return Adjugate(mat) * (1.0f / det);
}

indie::maths::Matrix3 indie::maths::Matrix3::Rotation(float pitch, float yaw, float roll)
{
    return ZRotation(roll) * XRotation(pitch) * YRotation(yaw);
}

indie::maths::Matrix3 indie::maths::Matrix3::ZRotation(float angle)
{
    angle = DEG2RAD(angle);
    return indie::maths::Matrix3(
         cosf(angle), sinf(angle), 0.0f,
        -sinf(angle), cosf(angle), 0.0f,
                0.0f,        0.0f, 1.0f);
}

indie::maths::Matrix3 indie::maths::Matrix3::XRotation(float angle)
{
    angle = DEG2RAD(angle);
    return indie::maths::Matrix3(
        1.0f,         0.0f,        0.0f,
        0.0f,  cosf(angle), sinf(angle),
        0.0f, -sinf(angle), cosf(angle));
}

indie::maths::Matrix3 indie::maths::Matrix3::YRotation(float angle)
{
    angle = DEG2RAD(angle);
    return Matrix3(
        cosf(angle), 0.0f, -sinf(angle),
               0.0f, 1.0f,         0.0f,
        sinf(angle), 0.0f,  cosf(angle));
}

indie::maths::Matrix3 indie::maths::Matrix3::AxisAngle(const Vector3D &axis, float angle)
{
    angle = DEG2RAD(angle);
    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - cosf(angle);
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    if (!CMP(axis.magnitudeSq(), 1.0f)) {
        float invLen = 1.0f / axis.magnitude();
        x *= invLen;
        y *= invLen;
        z *= invLen;
    }
    return Matrix3(
        t * (x * x) + c, t * x * y + s * z, t * x * z - s * y,
        t * x * y - s * z, t * (y * y) + c, t * y * z + s * x,
        t * x * z + s * y, t * y * z - s * x, t * (z * z) + c
    );
}

indie::maths::Vector3D indie::maths::Matrix3::MultiplyVector(const indie::maths::Vector3D &vec, const indie::maths::Matrix3 &mat)
{
    Vector3D result;
    result.x = Vector3D::Dot(vec, Vector3D(mat._11, mat._21, mat._31));
    result.y = Vector3D::Dot(vec, Vector3D(mat._12, mat._22, mat._32));
    result.z = Vector3D::Dot(vec, Vector3D(mat._13, mat._23, mat._33));
    return result;
}

indie::maths::Vector3D indie::maths::Matrix3::ToEulerAngles(const Matrix3 &matrix)
{
    if (CMP(matrix._12, -1.0f)) {
        float x = 0;
        float y = M_PI / 2;
        float z = x + atan2f(matrix._21, matrix._31);
        return {RAD2DEG(x), RAD2DEG(y), RAD2DEG(z)};
    } else if (CMP(matrix._12, 1.0f)) {
        float x = 0;
        float y = -M_PI / 2;
        float z = -x + atan2f(-matrix._21, -matrix._31);
        return {RAD2DEG(x), RAD2DEG(y), RAD2DEG(z)};
    } else {
        float y1 = -asinf(matrix._13);
        float y2 = M_PI - y1;
        float x1 = atan2f(matrix._23 / cosf(y1), matrix._33 / cosf(y1));
        float x2 = atan2f(matrix._23 / cosf(y2), matrix._33 / cosf(y2));
        float z1 = atan2f(matrix._12 / cosf(y1), matrix._11 / cosf(y1));
        float z2 = atan2f(matrix._12 / cosf(y2), matrix._11 / cosf(y2));
        if (std::abs(x1) + std::abs(y1) + std::abs(z1) <= std::abs(x2) + std::abs(y2) + std::abs(z2)) {
            return {RAD2DEG(x1), RAD2DEG(y1), RAD2DEG(z1)};
        } else {
            return {RAD2DEG(x2), RAD2DEG(y2), RAD2DEG(z2)};
        }
    }
}

indie::maths::Matrix3 indie::maths::operator*(const indie::maths::Matrix3 &matrix, float scalar)
{
    Matrix3 result;
    for (int i = 0; i < 9; i++) {
        result.asArray[i] = matrix.asArray[i] * scalar;
    }
    return result;
}

indie::maths::Matrix3 indie::maths::operator*(const indie::maths::Matrix3 &matA, const indie::maths::Matrix3 &matB)
{
    Matrix3 result;
    indie::maths::Multiply(result.asArray, matA.asArray, 3, 3, matB.asArray, 3, 3);
    return result;
}

/* ================================================================================================================ */
/* ----------------------------------------------------Matrix4----------------------------------------------------- */
/* ================================================================================================================ */

indie::maths::Matrix4::Matrix4()
{
    _11 = _22 = _33 = _44 = 1.0f;
    _12 = _13 = _14 = 0.0f;
    _21 = _23 = _24 = 0.0f;
    _31 = _32 = _34 = 0.0f;
    _41 = _42 = _43 = 0.0f;
}

indie::maths::Matrix4::Matrix4(
    float f11, float f12, float f13, float f14,
    float f21, float f22, float f23, float f24,
    float f31, float f32, float f33, float f34,
    float f41, float f42, float f43, float f44)
{
    _11 = f11;
    _12 = f12;
    _13 = f13;
    _14 = f14;
    _21 = f21;
    _22 = f22;
    _23 = f23;
    _24 = f24;
    _31 = f31;
    _32 = f32;
    _33 = f33;
    _34 = f34;
    _41 = f41;
    _42 = f42;
    _43 = f43;
    _44 = f44;
}

float *indie::maths::Matrix4::operator[](int i)
{
    return &asArray[i * 4];
}

const float *indie::maths::Matrix4::operator[](int i) const
{
    return &asArray[i * 4];
}

indie::maths::Matrix4 indie::maths::Matrix4::Transpose(const indie::maths::Matrix4 &mat)
{
    Matrix4 res;
    indie::maths::Transpose(mat.asArray, res.asArray, 4, 4);
    return res;
}

indie::maths::Matrix3 indie::maths::Matrix4::Cut(const indie::maths::Matrix4 &mat, int row, int col)
{
    Matrix3 result;
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i == row || j == col)
                continue;
            int target = index++;
            int source = 4 * i + j;
            result.asArray[target] = mat.asArray[source];
        }
    }
    return result;
}

float indie::maths::Matrix4::Determinant(const indie::maths::Matrix4 &mat)
{
    float result = 0.0f;
    Matrix4 cofactor = Cofactor(mat);
    for (int j = 0; j < 4; ++j) {
        result += mat.asArray[4 * 0 + j] * cofactor[0][j];
    }
    return result;
}

indie::maths::Matrix4 indie::maths::Matrix4::Minor(const indie::maths::Matrix4 &mat)
{
    Matrix4 result;
    for (int i = 0; i <4; ++i) {
        for (int j = 0; j <4; ++j) {
            result[i][j] = Matrix3::Determinant(Cut(mat, i, j));
        }
    }
    return result;
}

indie::maths::Matrix4 indie::maths::Matrix4::Cofactor(const indie::maths::Matrix4 &mat)
{
    Matrix4 result;
    indie::maths::Cofactor(result.asArray, Minor(mat).asArray, 4, 4);
    return result;
}

indie::maths::Matrix4 indie::maths::Matrix4::Adjugate(const indie::maths::Matrix4 &mat)
{
    return Transpose(Cofactor(mat));
}

indie::maths::Matrix4 indie::maths::Matrix4::Inverse(const indie::maths::Matrix4 &mat)
{
    float det = Determinant(mat);
    if (CMP(det, 0.0f)) {
        return Matrix4();
    }
    return Adjugate(mat) * (1.0f / det);
}

indie::maths::Matrix4 indie::maths::Matrix4::Translation(float x, float y, float z)
{
    return indie::maths::Matrix4(
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
           x,    y,    z, 0.0f);
}

indie::maths::Matrix4 indie::maths::Matrix4::Translation(const indie::maths::Vector3D &vec)
{
    return indie::maths::Matrix4(
        00.0f, 00.0f, 00.0f, 0.0f,
        00.0f, 00.0f, 00.0f, 0.0f,
        00.0f, 00.0f, 00.0f, 0.0f,
        vec.x, vec.y, vec.z, 0.0f);
}

indie::maths::Vector3D indie::maths::Matrix4::GetTranslation(const indie::maths::Matrix4 &mat)
{
    return indie::maths::Vector3D(mat._41, mat._42, mat._43);
}

indie::maths::Matrix4 indie::maths::Matrix4::Scale(float x, float y, float z)
{
    return indie::maths::Matrix4(
           x, 0.0f, 0.0f, 0.0f,
        0.0f,    y, 0.0f, 0.0f,
        0.0f, 0.0f,    z, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f);
}

indie::maths::Matrix4 indie::maths::Matrix4::Scale(const indie::maths::Vector3D &vec)
{
    return indie::maths::Matrix4(
        vec.x, 00.0f, 00.0f, 00.0f,
        00.0f, vec.y, 00.0f, 00.0f,
        00.0f, 00.0f, vec.z, 00.0f,
        00.0f, 00.0f, 00.0f, 00.0f);
}

indie::maths::Vector3D indie::maths::Matrix4::GetScale(const indie::maths::Matrix4 &mat)
{
    return indie::maths::Vector3D(mat._11, mat._22, mat._33);
}

indie::maths::Matrix4 indie::maths::Matrix4::Rotation(float pitch, float yaw, float roll)
{
    return ZRotation(roll) * XRotation(pitch) * YRotation(yaw);
}

indie::maths::Matrix4 indie::maths::Matrix4::ZRotation(float angle)
{
    angle = DEG2RAD(angle);
    return indie::maths::Matrix4(
         cosf(angle), sinf(angle), 0.0f, 0.0f,
        -sinf(angle), cosf(angle), 0.0f, 0.0f,
                0.0f,        0.0f, 1.0f, 0.0f,
                0.0f,        0.0f, 0.0f, 1.0f);
}

indie::maths::Matrix4 indie::maths::Matrix4::XRotation(float angle)
{
    angle = DEG2RAD(angle);
    return indie::maths::Matrix4(
        1.0f,         0.0f,        0.0f, 0.0f,
        0.0f,  cosf(angle), sinf(angle), 0.0f,
        0.0f, -sinf(angle), cosf(angle), 0.0f,
        0.0f,         0.0f,        0.0f, 1.0f);
}

indie::maths::Matrix4 indie::maths::Matrix4::YRotation(float angle)
{
    angle = DEG2RAD(angle);
    return Matrix4(
        cosf(angle), 0.0f, -sinf(angle), 0.0f,
               0.0f, 1.0f,         0.0f, 0.0f,
        sinf(angle), 0.0f,  cosf(angle), 0.0f,
               0.0f, 0.0f,         0.0f, 1.0f);
}

indie::maths::Matrix4 indie::maths::Matrix4::AxisAngle(const indie::maths::Vector3D &axis, float angle)
{
    angle = DEG2RAD(angle);
    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - cosf(angle);
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    if (!CMP(axis.magnitudeSq(), 1.0f)) {
        float invLen = 1.0f / axis.magnitude();
        x *= invLen;
        y *= invLen;
        z *= invLen;
    }
    return Matrix4(
        t * (x * x) + c, t * x * y + s * z, t * x * z - s * y, 0.0f,
        t * x * y - s * z, t * (y * y) + c, t * y * z + s * x, 0.0f,
        t * x * z + s * y, t * y * z - s * x, t * (z * z) + c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

indie::maths::Vector3D indie::maths::Matrix4::MultiplyPoint(const indie::maths::Vector3D &vec, const indie::maths::Matrix4 &mat)
{
    Vector3D result;
    result.x = vec.x * mat._11 + vec.y * mat._21 + vec.z * mat._31 + 1.0f * mat._41;
    result.y = vec.x * mat._12 + vec.y * mat._22 + vec.z * mat._32 + 1.0f * mat._42;
    result.z = vec.x * mat._13 + vec.y * mat._23 + vec.z * mat._33 + 1.0f * mat._43;
    return result;
}

indie::maths::Vector3D indie::maths::Matrix4::MultiplyVector(const indie::maths::Vector3D &vec, const indie::maths::Matrix4 &mat)
{
    Vector3D result;
    result.x = vec.x * mat._11 + vec.y * mat._21 + vec.z * mat._31;
    result.y = vec.x * mat._12 + vec.y * mat._22 + vec.z * mat._32;
    result.z = vec.x * mat._13 + vec.y * mat._23 + vec.z * mat._33;
    return result;
}

indie::maths::Matrix4 indie::maths::Matrix4::Transform(
    const indie::maths::Vector3D &scale,
    const indie::maths::Vector3D &eulerRotation,
    const indie::maths::Vector3D &translation)
{
    return Scale(scale) * Rotation(eulerRotation.x, eulerRotation.y, eulerRotation.z) * Translation(translation);
}

indie::maths::Matrix4 indie::maths::Matrix4::Transform(
    const indie::maths::Vector3D &scale,
    const indie::maths::Vector3D &rotationAxis, float rotationAngle,
    const indie::maths::Vector3D &translation)
{
    return Scale(scale) * AxisAngle(rotationAxis, rotationAngle) * Translation(translation);
}

indie::maths::Matrix4 indie::maths::Matrix4::LookAt(
    const indie::maths::Vector3D &position,
    const indie::maths::Vector3D &target,
    const indie::maths::Vector3D &up)
{
    Vector3D forward = Vector3D::Normalized(target - position);
    Vector3D right = Vector3D::Normalized(Vector3D::Cross(up, forward));
    Vector3D newUp = Vector3D::Cross(forward, right);

    return indie::maths::Matrix4(
        right.x, newUp.x, forward.x, 0.0f,
        right.y, newUp.y, forward.y, 0.0f,
        right.z, newUp.z, forward.z, 0.0f,
        -Vector3D::Dot(right, position), -Vector3D::Dot(newUp, position), -Vector3D::Dot(forward, position), 1.0f
    );
}

indie::maths::Matrix4 indie::maths::Matrix4::Projection(float fov, float aspect, float zNear, float zFar)
{
    float tanHalfFov = tanf(DEG2RAD((fov * 0.5f)));
    float fovY = 1.0f / tanHalfFov;
    float fovX = fovY / aspect;
    Matrix4 result;
    result._11 = fovX;
    result._22 = fovY;
    result._33 = zFar / (zFar - zNear);
    result._34 = 1.0f;
    result._43 = -zNear * result._33;
    result._44 = 0.0f;
    return result;
}

indie::maths::Matrix4 indie::maths::Matrix4::Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
    float _11 = 2.0f / (right - left);
    float _22 = 2.0f / (top - bottom);
    float _33 = 1.0f / (zFar - zNear);
    float _41 = (left + right) / (left - right);
    float _42 = (top + bottom) / (bottom - top);
    float _43 = (zNear) / (zNear - zFar);
    return Matrix4(
        _11, 0.0f, 0.0f, 0.0f,
        0.0f, _22, 0.0f, 0.0f,
        0.0f, 0.0f, _33, 0.0f,
        _41, _42, _43, 1.0f
    );
}

indie::maths::Vector3D indie::maths::Matrix4::ToEulerAngles(const indie::maths::Matrix4 &matrix)
{
    if (CMP(matrix._12, -1.0f)) {
        float x = 0;
        float y = M_PI / 2;
        float z = x + atan2f(matrix._21, matrix._31);
        return {RAD2DEG(x), RAD2DEG(y), RAD2DEG(z)};
    } else if (CMP(matrix._12, 1.0f)) {
        float x = 0;
        float y = -M_PI / 2;
        float z = -x + atan2f(-matrix._21, -matrix._31);
        return {RAD2DEG(x), RAD2DEG(y), RAD2DEG(z)};
    } else {
        float y1 = -asinf(matrix._13);
        float y2 = M_PI - y1;
        float x1 = atan2f(matrix._23 / cosf(y1), matrix._33 / cosf(y1));
        float x2 = atan2f(matrix._23 / cosf(y2), matrix._33 / cosf(y2));
        float z1 = atan2f(matrix._12 / cosf(y1), matrix._11 / cosf(y1));
        float z2 = atan2f(matrix._12 / cosf(y2), matrix._11 / cosf(y2));
        if (std::abs(x1) + std::abs(y1) + std::abs(z1) <= std::abs(x2) + std::abs(y2) + std::abs(z2)) {
            return {RAD2DEG(x1), RAD2DEG(y1), RAD2DEG(z1)};
        } else {
            return {RAD2DEG(x2), RAD2DEG(y2), RAD2DEG(z2)};
        }
    }
}

indie::maths::Matrix4 indie::maths::operator*(const indie::maths::Matrix4 &matrix, float scalar)
{
    Matrix4 result;
    for (int i = 0; i < 16; i++) {
        result.asArray[i] = matrix.asArray[i] * scalar;
    }
    return result;
}

indie::maths::Matrix4 indie::maths::operator*(const indie::maths::Matrix4 &matA, const indie::maths::Matrix4 &matB)
{
    Matrix4 result;
    indie::maths::Multiply(result.asArray, matA.asArray, 4, 4, matB.asArray, 4, 4);
    return result;
}

/* ================================================================================================================ */
/* ----------------------------------------------------General----------------------------------------------------- */
/* ================================================================================================================ */

void indie::maths::Transpose(const float *srcMat, float *destMat, int srcRows, int srcCols)
{
    for (int i = 0; i < srcRows * srcCols; i++) {
        int row = i / srcRows;
        int col = i % srcRows;
        destMat[i] = srcMat[srcCols * col + row];
    }
}

bool indie::maths::Multiply(float *out, const float *matA, int aRows, int aCols, const float *matB, int bRows, int bCols)
{
    if (aCols != bRows) {
        return false;
    }
    for (int i = 0; i < aRows; ++i) {
        for (int j = 0; j < bCols; ++j) {
            out[bCols * i + j] = 0.0f;
            for (int k = 0; k < bRows; ++k) {
                int a = aCols * i + k;
                int b = bCols * k + j;
                out[bCols * i + j] += matA[a] * matB[b];
            }
        }
    }
    return true;
}

void indie::maths::Cofactor(float *out, const float *minor, int rows, int cols)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int t = cols * j + i;
            int s = cols * j + i;
            float sign = powf(-1.0f, i + j);
            out[t] = minor[s] * sign;
        }
    }
}