#ifndef APPLICATION_H
#define APPLICATION_H

#include "scene.h"
#include "ray_tracer.h"
#include "graphics/camera.h"
#include "graphics/color.h"
#include "utils/image_writer.h"
#include <vector>
#include <string>

class Application {
public:
    Application();
    void run();
    void render();
    void setSettings(const SceneSettings& settings);
    void setLight2Position(float x, float y, float z);

private:
    Scene scene;
    std::vector<std::vector<Color>> pixels;
    
    void get_pixels();
    Point3D get_pixel_position(int x, int y);
};

#endif // APPLICATION_H

