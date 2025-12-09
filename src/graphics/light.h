#ifndef LIGHT_H
#define LIGHT_H

#include "../geometry/point3d.h"
#include "color.h"
#include "material.h"

struct Light {
    Point3D position;
    Color color;

    Light() {}
    Light(const Point3D& pos, const Color& col) : position(pos), color(col) {}

    // Вычисление локальной модели освещения
    Color shade(const Point3D& hit_point, const Point3D& normal, 
                const Color& obj_color, float diffuse_coef) const {
        Point3D dir = Point3D::normalize(position - hit_point);
        float dot = Point3D::scalar(normal, dir);
        if (dot < 0.0f) dot = 0.0f;
        
        Color diff = color * (diffuse_coef * dot);
        return Color(diff.r * obj_color.r, diff.g * obj_color.g, diff.b * obj_color.b);
    }
};

#endif // LIGHT_H

