#include "application.h"
#include "utils/image_writer.h"
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace {
std::string settingsText(const SceneSettings& s) {
    std::ostringstream ss;
    ss << std::boolalpha;
    ss << "F1  Mirror cube: " << s.cube_specular << "\n";
    ss << "F2  Mirror of the ball: " << s.sphere_specular << "\n";
    ss << "F3  Transparent cube: " << s.cube_refraction << "\n";
    ss << "F4  transparent ball: " << s.sphere_refraction << "\n";
    ss << "1-6 Mirror walls (Front/Back/Left/Right/Top/Bottom): "
       << s.front_wall_specular << "/" << s.back_wall_specular << "/"
       << s.left_wall_specular << "/" << s.right_wall_specular << "/"
       << s.up_wall_specular << "/" << s.down_wall_specular << "\n";
    ss << "L  Second light: " << s.two_lights << "  Pos: ("
       << std::fixed << std::setprecision(2) << s.light2_position.x << ", "
       << s.light2_position.y << ", " << s.light2_position.z << ")\n";
    ss << "Arrows/ PgUp/PgDn - move second light\n";
    ss << "R - recalculate | S - save | Esc - exit\n";
    return ss.str();
}

sf::Color toSF(const Color& c) {
    auto clamp = [](float v) {
        if (v < 0.0f) return 0.0f;
        if (v > 1.0f) return 1.0f;
        return v;
    };
    return sf::Color(
        static_cast<sf::Uint8>(clamp(c.r) * 255.0f),
        static_cast<sf::Uint8>(clamp(c.g) * 255.0f),
        static_cast<sf::Uint8>(clamp(c.b) * 255.0f));
}
} // namespace

int main() {
    setlocale(LC_ALL, "Rus");
    Application app;
    SceneSettings settings;

    sf::RenderWindow window(
        sf::VideoMode(app.getWidth(), app.getHeight() + 170),
        "Cornell Room - SFML");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Не удалось загрузить системный шрифт DejaVuSans. "
                     "Подключите любой ttf по этому пути.\n";
    }

    sf::RectangleShape overlay;
    overlay.setPosition(10.0f, 10.0f);
    overlay.setSize(sf::Vector2f(static_cast<float>(app.getWidth()) - 20.0f,
                                 150.0f));
    overlay.setFillColor(sf::Color(0, 0, 0, 170));

    sf::Text hud;
    hud.setFont(font);
    hud.setCharacterSize(16);
    hud.setFillColor(sf::Color::White);
    hud.setPosition(20.0f, 20.0f);

    sf::Texture texture;
    sf::Sprite sprite;

    auto rerender = [&]() {
        window.setTitle("Cornell Room - SFML (rendering...)");
        app.setSettings(settings);
        app.render();

        const auto& pixels = app.getPixels();
        sf::Image image;
        image.create(app.getWidth(), app.getHeight());
        for (int y = 0; y < app.getHeight(); ++y) {
            for (int x = 0; x < app.getWidth(); ++x) {
                image.setPixel(x, y, toSF(pixels[y][x]));
            }
        }
        texture.loadFromImage(image);
        sprite.setTexture(texture, true);
        sprite.setPosition(0.0f, 170.0f);  // Смещаем изображение под текстовую панель
        window.setTitle("Cornell Room - SFML");
    };

    rerender();
    bool needs_render = false;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                const bool fast = event.key.shift;
                float step = 1.5f;
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::F1:
                    settings.cube_specular = !settings.cube_specular;
                    needs_render = true;
                    break;
                case sf::Keyboard::F2:
                    settings.sphere_specular = !settings.sphere_specular;
                    needs_render = true;
                    break;
                case sf::Keyboard::F3:
                    settings.cube_refraction = !settings.cube_refraction;
                    needs_render = true;
                    break;
                case sf::Keyboard::F4:
                    settings.sphere_refraction = !settings.sphere_refraction;
                    needs_render = true;
                    break;
                case sf::Keyboard::Num1:
                    settings.front_wall_specular = !settings.front_wall_specular;
                    needs_render = true;
                    break;
                case sf::Keyboard::Num2:
                    settings.back_wall_specular = !settings.back_wall_specular;
                    needs_render = true;
                    break;
                case sf::Keyboard::Num3:
                    settings.left_wall_specular = !settings.left_wall_specular;
                    needs_render = true;
                    break;
                case sf::Keyboard::Num4:
                    settings.right_wall_specular =
                        !settings.right_wall_specular;
                    needs_render = true;
                    break;
                case sf::Keyboard::Num5:
                    settings.up_wall_specular = !settings.up_wall_specular;
                    needs_render = true;
                    break;
                case sf::Keyboard::Num6:
                    settings.down_wall_specular = !settings.down_wall_specular;
                    needs_render = true;
                    break;
                case sf::Keyboard::L:
                    settings.two_lights = !settings.two_lights;
                    needs_render = true;
                    break;
                case sf::Keyboard::Up:
                    settings.light2_position.y -= step;
                    needs_render = true;
                    break;
                case sf::Keyboard::Down:
                    settings.light2_position.y += step;
                    needs_render = true;
                    break;
                case sf::Keyboard::Left:
                    settings.light2_position.x += step;
                    needs_render = true;
                    break;
                case sf::Keyboard::Right:
                    settings.light2_position.x -= step;
                    needs_render = true;
                    break;
                case sf::Keyboard::A:
                    settings.light2_position.z += step;
                    needs_render = true;
                    break;
                case sf::Keyboard::Z:
                    settings.light2_position.z -= step;
                    needs_render = true;
                    break;
                case sf::Keyboard::R:
                    needs_render = true;
                    break;
                case sf::Keyboard::S: {
                    const auto& pix = app.getPixels();
                    if (ImageWriter::writePPM("output.ppm", pix,
                                              app.getWidth(), app.getHeight())) {
                        std::cout << "Файл output.ppm сохранен\n";
                    } else {
                        std::cerr << "Не удалось сохранить output.ppm\n";
                    }
                } break;
                default:
                    break;
                }
            }
        }

        if (needs_render) {
            rerender();
            needs_render = false;
        }

        hud.setString(settingsText(settings));
        window.clear(sf::Color::Black);
        // Сначала рисуем изображение (оно будет снизу)
        window.draw(sprite);
        // Затем рисуем текстовую панель поверх (она будет сверху)
        window.draw(overlay);
        window.draw(hud);
        window.display();
    }

    return 0;
}

