#ifndef SIDE_H
#define SIDE_H

#include "point3d.h"
#include "../graphics/color.h"
#include <vector>

class Figure;

class Side {
public:
    Figure* host;
    std::vector<int> points;
    Color color;

    Side(Figure* h = nullptr);
    Side(const Side& s);

    Point3D get_point(int index) const;
    static Point3D normal(const Side& s);
};

#endif // SIDE_H

