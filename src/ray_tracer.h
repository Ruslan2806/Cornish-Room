#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "geometry/ray.h"
#include "graphics/color.h"
#include "graphics/light.h"
#include "geometry/figure.h"
#include <vector>

class RayTracer {
public:
    static const int MAX_ITERATIONS = 10;

    static Color trace(const Ray& ray, const std::vector<Figure*>& scene, 
                      const std::vector<Light>& lights, int iterations = MAX_ITERATIONS, 
                      float env = 1.0f);

private:
    static bool is_visible(const Point3D& light_pos, const Point3D& hit_point, 
                          const std::vector<Figure*>& scene);
};

#endif // RAY_TRACER_H

