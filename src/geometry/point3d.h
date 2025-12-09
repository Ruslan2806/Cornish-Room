#ifndef POINT3D_H
#define POINT3D_H

#include <cmath>

struct Point3D {
    float x, y, z;

    Point3D() : x(0), y(0), z(0) {}
    Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

    Point3D operator+(const Point3D& other) const {
        return Point3D(x + other.x, y + other.y, z + other.z);
    }

    Point3D operator-(const Point3D& other) const {
        return Point3D(x - other.x, y - other.y, z - other.z);
    }

    Point3D operator*(float scalar) const {
        return Point3D(x * scalar, y * scalar, z * scalar);
    }

    Point3D operator/(float scalar) const {
        return Point3D(x / scalar, y / scalar, z / scalar);
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    static float scalar(const Point3D& a, const Point3D& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static Point3D cross(const Point3D& a, const Point3D& b) {
        return Point3D(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    static Point3D normalize(const Point3D& p) {
        float len = p.length();
        if (len < 1e-6f) return p;
        return p / len;
    }
};

#endif // POINT3D_H

