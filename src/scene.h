#ifndef SCENE_H
#define SCENE_H

#include "geometry/figure.h"
#include "geometry/sphere.h"
#include "graphics/light.h"
#include "graphics/camera.h"
#include "graphics/material.h"
#include <vector>
#include <memory>

// Структура для управления параметрами сцены
struct SceneSettings {
    // Зеркальность объектов
    bool cube_specular = false;
    bool sphere_specular = false;
    
    // Прозрачность объектов
    bool cube_refraction = false;
    bool sphere_refraction = false;
    
    // Зеркальность стен
    bool front_wall_specular = false;
    bool back_wall_specular = false;
    bool left_wall_specular = false;
    bool right_wall_specular = false;
    bool up_wall_specular = false;
    bool down_wall_specular = false;
    
    // Второй источник света
    bool two_lights = false;
    Point3D light2_position = Point3D(0.0f, 4.0f, 4.9f);
};

class Scene {
public:
    std::vector<std::unique_ptr<Figure>> figures;
    std::vector<Light> lights;
    Camera camera;
    SceneSettings settings;

    Scene();
    void build_scene();
    void clear();
};

#endif // SCENE_H

