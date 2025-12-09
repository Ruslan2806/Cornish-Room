#include "side.h"
#include "figure.h"

Side::Side(Figure* h) : host(h) {}

Side::Side(const Side& s) 
    : host(s.host), points(s.points), color(s.color) {}

Point3D Side::get_point(int index) const {
    if (host && index >= 0 && index < (int)points.size()) {
        return host->points[points[index]];
    }
    return Point3D();
}

Point3D Side::normal(const Side& s) {
    if (s.points.size() < 3) {
        return Point3D(0, 0, 0);
    }
    
    Point3D u = s.get_point(1) - s.get_point(0);
    Point3D v = s.get_point(s.points.size() - 1) - s.get_point(0);
    Point3D n = Point3D::cross(u, v);
    return Point3D::normalize(n);
}

