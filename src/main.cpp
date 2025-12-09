#include "application.h"
#include "ui.h"
#include <iostream>

int main() {
    std::cout << "=== Cornish Room Ray Tracer ===" << std::endl;
    std::cout << std::endl;

    Application app;
    SceneSettings settings;
    
    // Настройки по умолчанию
    settings.cube_specular = false;
    settings.sphere_specular = false;
    settings.cube_refraction = false;
    settings.sphere_refraction = false;
    settings.front_wall_specular = false;
    settings.back_wall_specular = false;
    settings.left_wall_specular = false;
    settings.right_wall_specular = false;
    settings.up_wall_specular = false;
    settings.down_wall_specular = false;
    settings.two_lights = false;
    settings.light2_position = Point3D(0.0f, 4.0f, 4.9f);

    // Показываем меню настройки
    UI::showCurrentSettings(settings);
    UI::configureSettings(settings);

    // Применяем настройки и запускаем рендеринг
    app.setSettings(settings);
    std::cout << "\nЗапуск рендеринга..." << std::endl;
    app.run();

    return 0;
}

