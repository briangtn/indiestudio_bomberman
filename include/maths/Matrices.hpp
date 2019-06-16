/*
** EPITECH PROJECT, 2018
** JFEntityComponentSystem
** File description:
** Matrices.hpp
*/

/* Created the 25/04/2019 at 18:42 by jfrabel */

#ifndef JFENTITYCOMPONENTSYSTEM_MATRICES_HPP
#define JFENTITYCOMPONENTSYSTEM_MATRICES_HPP

#include "Vectors.hpp"

namespace indie {

    /*!
     * @namespace jf::maths
     * @brief A namespace containing math related classes
     */
    namespace maths {

        struct Matrix2 {
            union {
                struct {
                    float _11;
                    float _12;
                    float _21;
                    float _22;
                };
                float asArray[4];
            };

            inline Matrix2();
            inline Matrix2(float f11, float f12, float f21, float f22);

            float *operator[](int i);
            const float *operator[](int i) const;

            float det() const;

            static Matrix2 Transpose(const Matrix2 &mat);
            static float Determinant(const Matrix2 &mat);
            static Matrix2 Minor(const Matrix2 &mat);
            static Matrix2 Cofactor(const Matrix2 &mat);
            static Matrix2 Adjugate(const Matrix2 &mat);
            static Matrix2 Inverse(const Matrix2 &mat);
        };

        Matrix2 operator*(const Matrix2 &matrix, float scalar);
        Matrix2 operator*(const Matrix2 &matA, const Matrix2 &matB);

        struct Matrix3 {
            union {
                struct {
                    float _11;
                    float _12;
                    float _13;
                    float _21;
                    float _22;
                    float _23;
                    float _31;
                    float _32;
                    float _33;
                };
                float asArray[9];
            };

            inline Matrix3() {
                _11 = _22 = _33 = 1.0f;
                _12 = _13 = _21 = _23 = _31 = _32 = 0.0f;
            }
            inline Matrix3(
                float f11, float f12, float f13,
                float f21, float f22, float f23,
                float f31, float f32, float f33);

            float *operator[](int i);
            const float *operator[](int i) const;

            static Matrix3 Transpose(const Matrix3 &mat);
            static Matrix2 Cut(const Matrix3 &mat, int row, int col);
            static float Determinant(const Matrix3 &mat);
            static Matrix3 Minor(const Matrix3 &mat);
            static Matrix3 Cofactor(const Matrix3 &mat);
            static Matrix3 Adjugate(const Matrix3 &mat);
            static Matrix3 Inverse(const Matrix3 &mat);

            static Matrix3 Rotation(float pitch, float yaw, float roll);
            static Matrix3 ZRotation(float angle);
            static Matrix3 XRotation(float angle);
            static Matrix3 YRotation(float angle);
            static Matrix3 AxisAngle(const Vector3D &axis, float angle);
            static Vector3D ToEulerAngles(const Matrix3 &matrix);

            static Vector3D MultiplyVector(const Vector3D &vec, const Matrix3 &mat);
        };

        Matrix3 operator*(const Matrix3 &matrix, float scalar);
        Matrix3 operator*(const Matrix3 &matA, const Matrix3 &matB);

        struct Matrix4 {
            union {
                struct {
                    float _11;
                    float _12;
                    float _13;
                    float _14;
                    float _21;
                    float _22;
                    float _23;
                    float _24;
                    float _31;
                    float _32;
                    float _33;
                    float _34;
                    float _41;
                    float _42;
                    float _43;
                    float _44;
                };
                float asArray[16];
            };

            inline Matrix4();
            inline Matrix4(
                float f11, float f12, float f13, float f14,
                float f21, float f22, float f23, float f24,
                float f31, float f32, float f33, float f34,
                float f41, float f42, float f43, float f44);

            float *operator[](int i);
            const float *operator[](int i) const;

            static Matrix4 Transpose(const Matrix4 &mat);
            static Matrix3 Cut(const Matrix4 &mat, int row, int col);
            static float Determinant(const Matrix4 &mat);
            static Matrix4 Minor(const Matrix4 &mat);
            static Matrix4 Cofactor(const Matrix4 &mat);
            static Matrix4 Adjugate(const Matrix4 &mat);
            static Matrix4 Inverse(const Matrix4 &mat);

            static Matrix4 Translation(float x, float y, float z);
            static Matrix4 Translation(const Vector3D &vec);
            static Vector3D GetTranslation(const Matrix4 &mat);

            static Matrix4 Scale(float x, float y, float z);
            static Matrix4 Scale(const Vector3D &vec);
            static Vector3D GetScale(const Matrix4 &mat);

            static Matrix4 Rotation(float pitch, float yaw, float roll);
            static Matrix4 ZRotation(float angle);
            static Matrix4 XRotation(float angle);
            static Matrix4 YRotation(float angle);
            static Matrix4 AxisAngle(const Vector3D &axis, float angle);
            static Vector3D ToEulerAngles(const Matrix4 &matrix);

            static Vector3D MultiplyPoint(const Vector3D &vec, const Matrix4 &mat);
            static Vector3D MultiplyVector(const Vector3D &vec, const Matrix4 &mat);

            static Matrix4 Transform(const Vector3D &scale, const Vector3D &eulerRotation, const Vector3D &translation);
            static Matrix4 Transform(const Vector3D &scale, const Vector3D &rotationAxis, float rotationAngle, const Vector3D &translation);

            static Matrix4 LookAt(const Vector3D &position, const Vector3D &target, const Vector3D &up);

            static Matrix4 Projection(float fov, float aspect, float zNear, float zFar);
            static Matrix4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
        };

        Matrix4 operator*(const Matrix4 &matrix, float scalar);
        Matrix4 operator*(const Matrix4 &matA, const Matrix4 &matB);

        void Transpose(const float *srcMat, float *destMat, int srcRows, int srcCols);
        bool Multiply(float *out, const float *matA, int aRows, int aCols, const float *matB, int bRows, int bCols);
        void Cofactor(float *out, const float *minor, int rows, int cols);
    }
}

#endif //JFENTITYCOMPONENTSYSTEM_MATRICES_HPP
