#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H

#include "../graphics/color.h"
#include <vector>
#include <string>

class ImageWriter {
public:
    static bool writePPM(const std::string& filename, 
                         const std::vector<std::vector<Color>>& pixels,
                         int width, int height);
};

#endif // IMAGE_WRITER_H

