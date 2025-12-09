#ifndef SPHERE_H
#define SPHERE_H

#include "figure.h"
#include "ray.h"

class Sphere : public Figure {
public:
    float radius;

    Sphere(const Point3D& center, float r);

    bool figure_intersection(const Ray& r, float& t, Point3D& normal, Material& mat) override;

private:
    static bool ray_sphere_intersection(const Ray& r, const Point3D& center, 
                                        float radius, float& t);
};

#endif // SPHERE_H

