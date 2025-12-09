#ifndef MATERIAL_H
#define MATERIAL_H

#include "../geometry/point3d.h"
#include "color.h"

struct Material {
    float reflection;    // коэффициент отражения
    float refraction;    // коэффициент преломления
    float environment;   // коэффициент преломления среды
    float ambient;       // коэффициент принятия фонового освещения
    float diffuse;       // коэффициент принятия диффузного освещения
    Color color;         // цвет материала

    Material() 
        : reflection(0.0f), refraction(0.0f), environment(1.0f),
          ambient(0.1f), diffuse(0.8f), color(1.0f, 1.0f, 1.0f) {}

    Material(float refl, float refr, float amb, float dif, float env = 1.0f)
        : reflection(refl), refraction(refr), environment(env),
          ambient(amb), diffuse(dif), color(1.0f, 1.0f, 1.0f) {}
};

#endif // MATERIAL_H

