#include "scene.h"
#include <cmath>
#include <memory>

Scene::Scene() {
    camera.width = 800;
    camera.height = 600;
}

void Scene::clear() {
    figures.clear();
    lights.clear();
}

void Scene::build_scene() {
    clear();

    // Создаем комнату (большой куб)
    Figure room = Figure::GetHexahedron(10.0f);
    room.isRoom = true;

    // Устанавливаем камеру
    room.sides[0].color = Color(1.0f, 1.0f, 1.0f);  // Белая задняя стена
    camera.up_left = room.sides[0].get_point(0);
    camera.up_right = room.sides[0].get_point(1);
    camera.down_right = room.sides[0].get_point(2);
    camera.down_left = room.sides[0].get_point(3);

    Point3D normal = Side::normal(room.sides[0]);
    Point3D center = (camera.up_left + camera.up_right + camera.down_left + camera.down_right) * 0.25f;
    camera.focus = center + normal * 10.0f;

    // Материалы для стен
    float refl, refr, amb, dif, env;

    // Задняя стена (белая)
    if (settings.back_wall_specular) {
        refl = 0.8f; refr = 0.0f; amb = 0.0f; dif = 0.0f; env = 1.0f;
    } else {
        refl = 0.0f; refr = 0.0f; amb = 0.1f; dif = 0.8f; env = 1.0f;
    }
    room.back_wall_material = Material(refl, refr, amb, dif, env);

    // Передняя стена (желтая)
    room.sides[1].color = Color(0.98f, 0.98f, 0.82f);  // LightGoldenrodYellow
    if (settings.front_wall_specular) {
        refl = 0.8f; refr = 0.0f; amb = 0.0f; dif = 0.0f; env = 1.0f;
    } else {
        refl = 0.0f; refr = 0.0f; amb = 0.1f; dif = 0.8f; env = 1.0f;
    }
    room.front_wall_material = Material(refl, refr, amb, dif, env);

    // Правая стена (бирюзовая)
    room.sides[2].color = Color(0.13f, 0.7f, 0.67f);  // LightSeaGreen
    if (settings.right_wall_specular) {
        refl = 0.8f; refr = 0.0f; amb = 0.0f; dif = 0.0f; env = 1.0f;
    } else {
        refl = 0.0f; refr = 0.0f; amb = 0.1f; dif = 0.8f; env = 1.0f;
    }
    room.right_wall_material = Material(refl, refr, amb, dif, env);

    // Левая стена (розовая)
    room.sides[3].color = Color(1.0f, 0.41f, 0.71f);  // HotPink
    if (settings.left_wall_specular) {
        refl = 0.8f; refr = 0.0f; amb = 0.0f; dif = 0.0f; env = 1.0f;
    } else {
        refl = 0.0f; refr = 0.0f; amb = 0.1f; dif = 0.8f; env = 1.0f;
    }
    room.left_wall_material = Material(refl, refr, amb, dif, env);

    // Верхняя стена (белая)
    room.sides[4].color = Color(1.0f, 1.0f, 1.0f);
    if (settings.up_wall_specular) {
        refl = 0.8f; refr = 0.0f; amb = 0.0f; dif = 0.0f; env = 1.0f;
    } else {
        refl = 0.0f; refr = 0.0f; amb = 0.1f; dif = 0.8f; env = 1.0f;
    }
    room.up_wall_material = Material(refl, refr, amb, dif, env);

    // Нижняя стена (белая)
    room.sides[5].color = Color(1.0f, 1.0f, 1.0f);
    if (settings.down_wall_specular) {
        refl = 0.8f; refr = 0.0f; amb = 0.0f; dif = 0.0f; env = 1.0f;
    } else {
        refl = 0.0f; refr = 0.0f; amb = 0.1f; dif = 0.8f; env = 1.0f;
    }
    room.down_wall_material = Material(refl, refr, amb, dif, env);

    figures.push_back(std::make_unique<Figure>(room));

    // Источники света
    Light l1(Point3D(0.0f, 1.0f, 4.9f), Color(1.0f, 1.0f, 1.0f));
    lights.push_back(l1);

    if (settings.two_lights) {
        Light l2(settings.light2_position, Color(1.0f, 1.0f, 1.0f));
        lights.push_back(l2);
    }

    // Первый куб (салатовый) - непрозрачный, неотражающий по умолчанию
    Figure cube1 = Figure::GetHexahedron(3.2f);
    cube1.offset(-0.5f, -1.0f, -3.5f);
    cube1.rotate_around(55.0f, "CZ");
    cube1.set_color(Color(0.6f, 0.8f, 0.2f));  // YellowGreen
    
    if (settings.cube_refraction) {
        refl = 0.0f; refr = 0.8f; amb = 0.0f; dif = 0.0f; env = 1.03f;
    } else {
        refl = 0.0f; refr = 0.0f; amb = 0.1f; dif = 0.7f; env = 1.0f;
    }
    cube1.figure_material = Material(refl, refr, amb, dif, env);
    figures.push_back(std::make_unique<Figure>(cube1));

    // Второй куб (нежно-синий)
    Figure cube2 = Figure::GetHexahedron(2.6f);
    cube2.offset(-2.4f, 2.0f, -3.8f);
    cube2.rotate_around(30.0f, "CZ");
    cube2.set_color(Color(0.39f, 0.58f, 0.93f));  // CornflowerBlue
    
    if (settings.cube_specular) {
        refl = 0.8f; refr = 0.0f; amb = 0.05f; dif = 0.0f; env = 1.0f;
    } else {
        refl = 0.0f; refr = 0.0f; amb = 0.1f; dif = 0.8f; env = 1.0f;
    }
    cube2.figure_material = Material(refl, refr, amb, dif, env);
    figures.push_back(std::make_unique<Figure>(cube2));

    // Первый шар (коралловый)
    Sphere s1(Point3D(2.5f, 2.0f, -3.4f), 1.7f);
    s1.set_color(Color(1.0f, 0.5f, 0.31f));  // Coral
    
    if (settings.sphere_refraction) {
        refl = 0.0f; refr = 0.9f; amb = 0.0f; dif = 0.0f; env = 1.03f;
    } else {
        refl = 0.0f; refr = 0.0f; amb = 0.1f; dif = 0.9f; env = 1.0f;
    }
    s1.figure_material = Material(refl, refr, amb, dif, env);
    figures.push_back(std::make_unique<Sphere>(s1));

    // Второй шар (желтый)
    Sphere s2(Point3D(-2.2f, 1.6f, -1.4f), 1.2f);
    s2.set_color(Color(1.0f, 1.0f, 0.0f));  // Yellow
    
    if (settings.sphere_specular) {
        refl = 0.8f; refr = 0.0f; amb = 0.05f; dif = 0.0f; env = 1.0f;
    } else {
        refl = 0.0f; refr = 0.0f; amb = 0.1f; dif = 0.9f; env = 1.0f;
    }
    s2.figure_material = Material(refl, refr, amb, dif, env);
    figures.push_back(std::make_unique<Sphere>(s2));
}

