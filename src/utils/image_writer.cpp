#include "image_writer.h"
#include <fstream>
#include <iostream>

bool ImageWriter::writePPM(const std::string& filename, 
                           const std::vector<std::vector<Color>>& pixels,
                           int width, int height) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }

    // Записываем заголовок PPM
    file << "P6\n" << width << " " << height << "\n255\n";

    // Записываем пиксели
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Color c = pixels[y][x];
            c.clamp();
            unsigned char r = (unsigned char)(c.r * 255);
            unsigned char g = (unsigned char)(c.g * 255);
            unsigned char b = (unsigned char)(c.b * 255);
            file << r << g << b;
        }
    }

    file.close();
    return true;
}

