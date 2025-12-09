#include "sphere.h"
#include <cmath>

Sphere::Sphere(const Point3D& center, float r) : radius(r) {
    points.push_back(center);
}

bool Sphere::ray_sphere_intersection(const Ray& r, const Point3D& center, 
                                     float radius, float& t) {
    Point3D k = r.start - center;
    float b = Point3D::scalar(k, r.direction);
    float c = Point3D::scalar(k, k) - radius * radius;
    float d = b * b - c;
    t = 0.0f;

    if (d >= 0.0f) {
        float sqrtd = std::sqrt(d);
        float t1 = -b + sqrtd;
        float t2 = -b - sqrtd;

        float min_t = (t1 < t2) ? t1 : t2;
        float max_t = (t1 > t2) ? t1 : t2;

        t = (min_t > EPS) ? min_t : max_t;
        return t > EPS;
    }
    return false;
}

bool Sphere::figure_intersection(const Ray& r, float& t, Point3D& normal, Material& mat) {
    if (ray_sphere_intersection(r, points[0], radius, t) && t > EPS) {
        Point3D hit_point = r.start + r.direction * t;
        normal = Point3D::normalize(hit_point - points[0]);
        mat = figure_material;
        // Устанавливаем цвет из первой стороны, если она есть, иначе используем белый
        if (!sides.empty()) {
            mat.color = sides[0].color;
        }
        return true;
    }
    return false;
}

