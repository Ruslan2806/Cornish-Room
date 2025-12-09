#include "application.h"
#include <iostream>
#include <iomanip>

Application::Application() {
    scene.camera.width = 800;
    scene.camera.height = 600;
    pixels.resize(scene.camera.height);
    for (int i = 0; i < scene.camera.height; ++i) {
        pixels[i].resize(scene.camera.width);
    }
}

void Application::setSettings(const SceneSettings& settings) {
    scene.settings = settings;
}

void Application::setLight2Position(float x, float y, float z) {
    scene.settings.light2_position = Point3D(x, y, z);
}

void Application::get_pixels() {
    Point3D step_up = (scene.camera.up_right - scene.camera.up_left) / (scene.camera.width - 1);
    Point3D step_down = (scene.camera.down_right - scene.camera.down_left) / (scene.camera.width - 1);

    Point3D up = scene.camera.up_left;
    Point3D down = scene.camera.down_left;

    for (int x = 0; x < scene.camera.width; ++x) {
        Point3D step_y = (up - down) / (scene.camera.height - 1);
        Point3D d = down;
        
        for (int y = 0; y < scene.camera.height; ++y) {
            pixels[y][x] = Color(0, 0, 0);  // Инициализация
            d = d + step_y;
        }
        up = up + step_up;
        down = down + step_down;
    }
}

Point3D Application::get_pixel_position(int x, int y) {
    Point3D step_up = (scene.camera.up_right - scene.camera.up_left) / (scene.camera.width - 1);
    Point3D step_down = (scene.camera.down_right - scene.camera.down_left) / (scene.camera.width - 1);

    Point3D up = scene.camera.up_left + step_up * x;
    Point3D down = scene.camera.down_left + step_down * x;
    
    Point3D step_y = (up - down) / (scene.camera.height - 1);
    return down + step_y * y;
}

void Application::render() {
    std::cout << "Building scene..." << std::endl;
    scene.build_scene();

    std::cout << "Rendering..." << std::endl;
    
    // Создаем вектор указателей на фигуры для RayTracer
    std::vector<Figure*> scene_figures;
    for (auto& fig : scene.figures) {
        scene_figures.push_back(fig.get());
    }

    int total_pixels = scene.camera.width * scene.camera.height;
    int processed = 0;

    for (int y = 0; y < scene.camera.height; ++y) {
        for (int x = 0; x < scene.camera.width; ++x) {
            Point3D pixel_pos = get_pixel_position(x, y);
            Ray ray(scene.camera.focus, pixel_pos);
            ray.start = pixel_pos;
            
            Color color = RayTracer::trace(ray, scene_figures, scene.lights);
            pixels[y][x] = color;
            
            processed++;
            if (processed % 10000 == 0) {
                std::cout << "Progress: " << std::fixed << std::setprecision(1) 
                         << (100.0 * processed / total_pixels) << "%\r" << std::flush;
            }
        }
    }
    
    std::cout << "\nRendering complete!" << std::endl;
}

void Application::run() {
    render();
    
    std::string filename = "output.ppm";
    std::cout << "Saving image to " << filename << "..." << std::endl;
    
    if (ImageWriter::writePPM(filename, pixels, scene.camera.width, scene.camera.height)) {
        std::cout << "Image saved successfully!" << std::endl;
    } else {
        std::cerr << "Failed to save image!" << std::endl;
    }
}

