#ifndef CAMERA_H
#define CAMERA_H

#include "../geometry/point3d.h"

struct Camera {
    Point3D focus;
    Point3D up_left, up_right, down_left, down_right;
    int width, height;

    Camera() : width(800), height(600) {}
};

#endif // CAMERA_H

