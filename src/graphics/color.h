#ifndef COLOR_H
#define COLOR_H

struct Color {
    float r, g, b;

    Color() : r(0), g(0), b(0) {}
    Color(float r, float g, float b) : r(r), g(g), b(b) {}

    Color operator+(const Color& other) const {
        return Color(r + other.r, g + other.g, b + other.b);
    }

    Color operator*(float scalar) const {
        return Color(r * scalar, g * scalar, b * scalar);
    }

    Color operator*(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b);
    }

    void clamp() {
        if (r > 1.0f) r = 1.0f;
        if (g > 1.0f) g = 1.0f;
        if (b > 1.0f) b = 1.0f;
        if (r < 0.0f) r = 0.0f;
        if (g < 0.0f) g = 0.0f;
        if (b < 0.0f) b = 0.0f;
    }

    int toRGB() const {
        int rr = (int)(r * 255);
        int gg = (int)(g * 255);
        int bb = (int)(b * 255);
        if (rr > 255) rr = 255;
        if (gg > 255) gg = 255;
        if (bb > 255) bb = 255;
        return (rr << 16) | (gg << 8) | bb;
    }
};

#endif // COLOR_H

