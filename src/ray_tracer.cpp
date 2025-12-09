#include "ray_tracer.h"
#include <algorithm>

Color RayTracer::trace(const Ray& ray, const std::vector<Figure*>& scene, 
                      const std::vector<Light>& lights, int iterations, float env) {
    if (iterations <= 0) {
        return Color(0, 0, 0);
    }

    float t = 0.0f;
    Point3D normal;
    Material mat;
    Figure* hit_figure = nullptr;

    // Находим ближайшее пересечение
    for (Figure* fig : scene) {
        float intersect_t;
        Point3D intersect_normal;
        Material intersect_mat;
        
        if (fig->figure_intersection(ray, intersect_t, intersect_normal, intersect_mat)) {
            if (t == 0.0f || intersect_t < t) {
                t = intersect_t;
                normal = intersect_normal;
                mat = intersect_mat;
                hit_figure = fig;
            }
        }
    }

    if (t == 0.0f) {
        return Color(0, 0, 0);
    }

    // Проверяем, выходит ли луч из объекта
    bool refract_out_of_figure = false;
    if (Point3D::scalar(ray.direction, normal) > 0.0f) {
        normal = normal * -1.0f;
        refract_out_of_figure = true;
    }

    Point3D hit_point = ray.start + ray.direction * t;
    Color result_color(0, 0, 0);

    // Освещение от всех источников
    for (const Light& light : lights) {
        // Фоновое освещение
        Color amb = light.color * mat.ambient;
        amb = Color(amb.r * mat.color.r, amb.g * mat.color.g, amb.b * mat.color.b);
        result_color = result_color + amb;

        // Диффузное освещение
        if (is_visible(light.position, hit_point, scene)) {
            Color diff = light.shade(hit_point, normal, mat.color, mat.diffuse);
            result_color = result_color + diff;
        }
    }

    // Зеркальное отражение
    if (mat.reflection > 0.0f) {
        Ray reflected_ray = ray.reflect(hit_point, normal);
        Color reflected_color = trace(reflected_ray, scene, lights, iterations - 1, env);
        result_color = result_color + reflected_color * mat.reflection;
    }

    // Преломление
    if (mat.refraction > 0.0f) {
        float eta;
        if (refract_out_of_figure) {
            eta = mat.environment;
        } else {
            eta = 1.0f / mat.environment;
        }

        Ray refracted_ray = ray.refract(hit_point, normal, eta);
        // Проверяем, что луч валиден (направление не нулевое)
        if (refracted_ray.direction.length() > 0.001f) {
            Color refracted_color = trace(refracted_ray, scene, lights, 
                                         iterations - 1, mat.environment);
            result_color = result_color + refracted_color * mat.refraction;
        }
    }

    result_color.clamp();
    return result_color;
}

bool RayTracer::is_visible(const Point3D& light_pos, const Point3D& hit_point, 
                          const std::vector<Figure*>& scene) {
    float max_t = (light_pos - hit_point).length();
    Ray r(hit_point, light_pos);

    for (Figure* fig : scene) {
        float t;
        Point3D n;
        Material m;
        if (fig->figure_intersection(r, t, n, m)) {
            if (t < max_t && t > Figure::EPS) {
                return false;
            }
        }
    }
    return true;
}

