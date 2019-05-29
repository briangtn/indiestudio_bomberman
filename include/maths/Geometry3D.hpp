/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Aabb.hpp
*/

/* Created the 29/05/2019 at 12:45 by jfrabel */

#ifndef INDIESTUDIO_GEOMETRY3D_HPP
#define INDIESTUDIO_GEOMETRY3D_HPP

#include "Vectors.hpp"
#include "Matrices.hpp"

namespace indie {

    /*!
     * @namespace jf::maths
     * @brief A namespace containing math related classes
     */
    namespace maths {

        struct OBB;

        using Point = Vector3D;

        struct Interval {
            float min;
            float max;
        };

        struct ISATAble {
            virtual Interval getInterval(const Vector3D &axis) const = 0;
        };

        bool OverlapOnAxis(const ISATAble &satAbleA, const ISATAble &satAbleB, const Vector3D &axis);

        struct AABB : public ISATAble {
            AABB();
            explicit AABB(const Point &o, const Vector3D &s);

            Point min() const;
            Point max() const;

            bool collides(const Point &point) const;
            bool collides(const AABB &aabb) const;
            bool collides(const OBB &obb) const;
            Point closest(const Point &point) const;

            Interval getInterval(const Vector3D &axis) const override;

            static AABB fromMinMax(const Point &min, const Point &max);

            Point origin;
            Vector3D size;
        };

        Point GetMin(const AABB &aabb);
        Point GetMax(const AABB &aabb);
        AABB FromMinMax(const Point &min, const Point &max);

        bool PointInAABB(const Point &point, const AABB &aabb);
        bool AABBAABBCollision(const AABB &aabb1, const AABB &aabb2);
        Point ClosestPoint(const Point &point, const AABB &aabb);

        struct OBB : public ISATAble {
            OBB();
            explicit OBB(const Point &o, const Vector3D &s);
            explicit OBB(const Point &o, const Vector3D &s, const Matrix3 &m);

            bool collides(const Point &point) const;
            bool collides(const OBB &obb) const;
            bool collides(const AABB &aabb) const;
            Point closest(const Point &point) const;

            Interval getInterval(const Vector3D &axis) const override;

            Point origin;
            Vector3D size;
            Matrix3 orientation;
        };

        bool PointInOBB(const Point &point, const OBB &obb);
        bool AABBOBBCollision(const AABB &aabb, const OBB &obb);
        bool OBBOBBCollision(const OBB &obb1, const OBB &obb2);
        Point ClosestPoint(const Point &point, const OBB &obb);
    }
}

#endif //INDIESTUDIO_GEOMETRY3D_HPP
