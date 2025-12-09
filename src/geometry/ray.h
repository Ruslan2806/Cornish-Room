#ifndef RAY_H
#define RAY_H

#include "point3d.h"

struct Ray {
    Point3D start;
    Point3D direction;

    Ray() {}
    Ray(const Point3D& start, const Point3D& end) 
        : start(start), direction(Point3D::normalize(end - start)) {}

    // Отражение луча
    Ray reflect(const Point3D& hit_point, const Point3D& normal) const {
        float dot = Point3D::scalar(direction, normal);
        Point3D reflect_dir = direction - normal * (2.0f * dot);
        return Ray(hit_point, hit_point + reflect_dir);
    }

    // Преломление луча
    Ray refract(const Point3D& hit_point, const Point3D& normal, float eta) const {
        float sclr = Point3D::scalar(normal, direction);
        float k = 1.0f - eta * eta * (1.0f - sclr * sclr);
        
        if (k >= 0.0f) {
            float cos_theta = std::sqrt(k);
            Point3D refracted_dir = Point3D::normalize(
                direction * eta - normal * (cos_theta + eta * sclr)
            );
            return Ray(hit_point, hit_point + refracted_dir);
        } else {
            // Полное внутреннее отражение
            return Ray();
        }
    }
};

#endif // RAY_H

