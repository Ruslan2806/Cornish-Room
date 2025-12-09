#ifndef FIGURE_H
#define FIGURE_H

#include "point3d.h"
#include "ray.h"
#include "side.h"
#include "../graphics/material.h"
#include "../graphics/color.h"
#include <vector>

class Figure {
public:
    static const float EPS;
    
    std::vector<Point3D> points;
    std::vector<Side> sides;
    bool isRoom;
    
    // Материалы для стен комнаты
    Material front_wall_material;
    Material back_wall_material;
    Material left_wall_material;
    Material right_wall_material;
    Material up_wall_material;
    Material down_wall_material;
    Material figure_material;

    Figure();
    Figure(const Figure& f);

    virtual ~Figure() {}

    // Пересечение луча с фигурой
    virtual bool figure_intersection(const Ray& r, float& t, Point3D& normal, Material& mat);

    void set_color(const Color& color);
    
    // Преобразования
    void offset(float x, float y, float z);
    void rotate_around(float angle, const char* type);
    void scale_axis(float xs, float ys, float zs);

    // Статический метод получения куба
    static Figure GetHexahedron(float size);

protected:
    bool ray_intersects_triangle(const Ray& r, const Point3D& p0, 
                                  const Point3D& p1, const Point3D& p2, float& t);
};

#endif // FIGURE_H

