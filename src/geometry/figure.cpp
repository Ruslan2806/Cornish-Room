#include "figure.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include "../utils/math_utils.h"

const float Figure::EPS = 0.0001f;

Figure::Figure() : isRoom(false) {}

Figure::Figure(const Figure& f) : isRoom(f.isRoom) {
    points = f.points;
    sides = f.sides;
    for (size_t i = 0; i < sides.size(); ++i) {
        sides[i].host = this;
    }
    front_wall_material = f.front_wall_material;
    back_wall_material = f.back_wall_material;
    left_wall_material = f.left_wall_material;
    right_wall_material = f.right_wall_material;
    up_wall_material = f.up_wall_material;
    down_wall_material = f.down_wall_material;
    figure_material = f.figure_material;
}

bool Figure::ray_intersects_triangle(const Ray& r, const Point3D& p0, 
                                      const Point3D& p1, const Point3D& p2, float& t) {
    Point3D edge1 = p1 - p0;
    Point3D edge2 = p2 - p0;
    Point3D h = Point3D::cross(r.direction, edge2);
    float a = Point3D::scalar(edge1, h);

    if (a > -EPS && a < EPS) {
        return false;  // Луч параллелен треугольнику
    }

    float f = 1.0f / a;
    Point3D s = r.start - p0;
    float u = f * Point3D::scalar(s, h);

    if (u < 0.0f || u > 1.0f) {
        return false;
    }

    Point3D q = Point3D::cross(s, edge1);
    float v = f * Point3D::scalar(r.direction, q);

    if (v < 0.0f || u + v > 1.0f) {
        return false;
    }

    t = f * Point3D::scalar(edge2, q);
    return t > EPS;
}

bool Figure::figure_intersection(const Ray& r, float& t, Point3D& normal, Material& mat) {
    t = 0.0f;
    int wall_index = -1;
    Side* hit_side = nullptr;

    for (size_t i = 0; i < sides.size(); ++i) {
        if (sides[i].points.size() == 3) {
            float intersect_t;
            if (ray_intersects_triangle(r, 
                    sides[i].get_point(0), 
                    sides[i].get_point(1), 
                    sides[i].get_point(2), 
                    intersect_t) && 
                (t == 0.0f || intersect_t < t)) {
                t = intersect_t;
                hit_side = &sides[i];
            }
        } else if (sides[i].points.size() == 4) {
            float intersect_t;
            bool found = false;
            
            if (ray_intersects_triangle(r, 
                    sides[i].get_point(0), 
                    sides[i].get_point(1), 
                    sides[i].get_point(3), 
                    intersect_t) && 
                (t == 0.0f || intersect_t < t)) {
                t = intersect_t;
                wall_index = i;
                hit_side = &sides[i];
                found = true;
            }
            
            if (ray_intersects_triangle(r, 
                    sides[i].get_point(1), 
                    sides[i].get_point(2), 
                    sides[i].get_point(3), 
                    intersect_t) && 
                (t == 0.0f || intersect_t < t)) {
                t = intersect_t;
                wall_index = i;
                hit_side = &sides[i];
            }
        }
    }

    if (t > 0.0f && hit_side) {
        normal = Side::normal(*hit_side);
        
        if (isRoom) {
            switch (wall_index) {
                case 0: mat = back_wall_material; break;
                case 1: mat = front_wall_material; break;
                case 2: mat = right_wall_material; break;
                case 3: mat = left_wall_material; break;
                case 4: mat = up_wall_material; break;
                case 5: mat = down_wall_material; break;
                default: mat = figure_material; break;
            }
        } else {
            mat = figure_material;
        }
        
        mat.color = hit_side->color;
        return true;
    }

    return false;
}

void Figure::set_color(const Color& color) {
    // Если нет сторон (например, для сферы), создаем одну фиктивную сторону для хранения цвета
    if (sides.empty()) {
        Side s(this);
        s.color = color;
        sides.push_back(s);
    } else {
        for (size_t i = 0; i < sides.size(); ++i) {
            sides[i].color = color;
        }
    }
}

void Figure::offset(float x, float y, float z) {
    for (size_t i = 0; i < points.size(); ++i) {
        points[i].x += x;
        points[i].y += y;
        points[i].z += z;
    }
}

void Figure::rotate_around(float angle, const char* type) {
    // Упрощенная реализация - можно расширить при необходимости
    float rad = angle * M_PI / 180.0f;
    Point3D center(0, 0, 0);
    for (const auto& p : points) {
        center = center + p;
    }
    center = center * (1.0f / points.size());

    for (size_t i = 0; i < points.size(); ++i) {
        Point3D p = points[i] - center;
        float x = p.x, y = p.y, z = p.z;
        
        if (std::strcmp(type, "CZ") == 0) {
            float cos_a = std::cos(rad);
            float sin_a = std::sin(rad);
            points[i].x = center.x + x * cos_a - y * sin_a;
            points[i].y = center.y + x * sin_a + y * cos_a;
            points[i].z = center.z + z;
        }
        // Можно добавить другие оси при необходимости
    }
}

void Figure::scale_axis(float xs, float ys, float zs) {
    for (size_t i = 0; i < points.size(); ++i) {
        points[i].x *= xs;
        points[i].y *= ys;
        points[i].z *= zs;
    }
}

Figure Figure::GetHexahedron(float size) {
    Figure res;
    
    float half = size / 2.0f;
    
    // Вершины куба
    res.points.push_back(Point3D(half, half, half));      // 0
    res.points.push_back(Point3D(-half, half, half));      // 1
    res.points.push_back(Point3D(-half, half, -half));    // 2
    res.points.push_back(Point3D(half, half, -half));     // 3
    res.points.push_back(Point3D(half, -half, half));     // 4
    res.points.push_back(Point3D(-half, -half, half));    // 5
    res.points.push_back(Point3D(-half, -half, -half));   // 6
    res.points.push_back(Point3D(half, -half, -half));    // 7

    // Создаем стороны
    Side s0(&res);
    s0.points = {3, 2, 1, 0};
    res.sides.push_back(s0);

    Side s1(&res);
    s1.points = {4, 5, 6, 7};
    res.sides.push_back(s1);

    Side s2(&res);
    s2.points = {2, 6, 5, 1};
    res.sides.push_back(s2);

    Side s3(&res);
    s3.points = {0, 4, 7, 3};
    res.sides.push_back(s3);

    Side s4(&res);
    // Верхняя стена: изменяем порядок вершин для правильной нормали (направленной вниз)
    s4.points = {0, 1, 5, 4};
    res.sides.push_back(s4);

    Side s5(&res);
    s5.points = {2, 3, 7, 6};
    res.sides.push_back(s5);

    return res;
}

