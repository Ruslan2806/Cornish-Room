#include "ui.h"
#include <limits>
#include <iomanip>

void UI::showMenu() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "   Корнуэльская комната - Настройки" << std::endl;
    std::cout << "========================================\n" << std::endl;
    std::cout << "1. Настроить зеркальность объектов" << std::endl;
    std::cout << "2. Настроить прозрачность объектов" << std::endl;
    std::cout << "3. Настроить зеркальность стен" << std::endl;
    std::cout << "4. Настроить источники света" << std::endl;
    std::cout << "5. Показать текущие настройки" << std::endl;
    std::cout << "6. Запустить рендеринг" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "\nВыберите опцию: ";
}

void UI::showCurrentSettings(const SceneSettings& settings) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "   Текущие настройки" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    std::cout << "Зеркальность объектов:" << std::endl;
    std::cout << "  Куб: " << (settings.cube_specular ? "ВКЛ" : "ВЫКЛ") << std::endl;
    std::cout << "  Шар: " << (settings.sphere_specular ? "ВКЛ" : "ВЫКЛ") << std::endl;
    
    std::cout << "\nПрозрачность объектов:" << std::endl;
    std::cout << "  Куб: " << (settings.cube_refraction ? "ВКЛ" : "ВЫКЛ") << std::endl;
    std::cout << "  Шар: " << (settings.sphere_refraction ? "ВКЛ" : "ВЫКЛ") << std::endl;
    
    std::cout << "\nЗеркальность стен:" << std::endl;
    std::cout << "  Передняя: " << (settings.front_wall_specular ? "ВКЛ" : "ВЫКЛ") << std::endl;
    std::cout << "  Задняя: " << (settings.back_wall_specular ? "ВКЛ" : "ВЫКЛ") << std::endl;
    std::cout << "  Левая: " << (settings.left_wall_specular ? "ВКЛ" : "ВЫКЛ") << std::endl;
    std::cout << "  Правая: " << (settings.right_wall_specular ? "ВКЛ" : "ВЫКЛ") << std::endl;
    std::cout << "  Верхняя: " << (settings.up_wall_specular ? "ВКЛ" : "ВЫКЛ") << std::endl;
    std::cout << "  Нижняя: " << (settings.down_wall_specular ? "ВКЛ" : "ВЫКЛ") << std::endl;
    
    std::cout << "\nИсточники света:" << std::endl;
    std::cout << "  Второй источник: " << (settings.two_lights ? "ВКЛ" : "ВЫКЛ") << std::endl;
    if (settings.two_lights) {
        std::cout << "  Позиция второго источника: (" 
                  << std::fixed << std::setprecision(2)
                  << settings.light2_position.x << ", "
                  << settings.light2_position.y << ", "
                  << settings.light2_position.z << ")" << std::endl;
    }
    std::cout << "\n";
}

void UI::configureSettings(SceneSettings& settings) {
    int choice;
    
    while (true) {
        showMenu();
        choice = getChoice(0, 6);
        
        switch (choice) {
            case 0:
                return;
                
            case 1: { // Зеркальность объектов
                std::cout << "\n--- Настройка зеркальности объектов ---\n" << std::endl;
                settings.cube_specular = getYesNo("Включить зеркальность для куба? (y/n): ");
                settings.sphere_specular = getYesNo("Включить зеркальность для шара? (y/n): ");
                std::cout << "Настройки сохранены!\n" << std::endl;
                break;
            }
            
            case 2: { // Прозрачность объектов
                std::cout << "\n--- Настройка прозрачности объектов ---\n" << std::endl;
                settings.cube_refraction = getYesNo("Включить прозрачность для куба? (y/n): ");
                settings.sphere_refraction = getYesNo("Включить прозрачность для шара? (y/n): ");
                std::cout << "Настройки сохранены!\n" << std::endl;
                break;
            }
            
            case 3: { // Зеркальность стен
                std::cout << "\n--- Настройка зеркальности стен ---\n" << std::endl;
                std::cout << "Выберите стену для настройки:" << std::endl;
                std::cout << "1. Передняя" << std::endl;
                std::cout << "2. Задняя" << std::endl;
                std::cout << "3. Левая" << std::endl;
                std::cout << "4. Правая" << std::endl;
                std::cout << "5. Верхняя" << std::endl;
                std::cout << "6. Нижняя" << std::endl;
                std::cout << "7. Все стены" << std::endl;
                std::cout << "0. Назад" << std::endl;
                std::cout << "\nВыберите опцию: ";
                
                int wall_choice = getChoice(0, 7);
                if (wall_choice == 0) break;
                
                bool value = getYesNo("Включить зеркальность? (y/n): ");
                
                if (wall_choice == 1) {
                    settings.front_wall_specular = value;
                } else if (wall_choice == 2) {
                    settings.back_wall_specular = value;
                } else if (wall_choice == 3) {
                    settings.left_wall_specular = value;
                } else if (wall_choice == 4) {
                    settings.right_wall_specular = value;
                } else if (wall_choice == 5) {
                    settings.up_wall_specular = value;
                } else if (wall_choice == 6) {
                    settings.down_wall_specular = value;
                } else if (wall_choice == 7) {
                    settings.front_wall_specular = value;
                    settings.back_wall_specular = value;
                    settings.left_wall_specular = value;
                    settings.right_wall_specular = value;
                    settings.up_wall_specular = value;
                    settings.down_wall_specular = value;
                }
                
                std::cout << "Настройки сохранены!\n" << std::endl;
                break;
            }
            
            case 4: { // Источники света
                std::cout << "\n--- Настройка источников света ---\n" << std::endl;
                settings.two_lights = getYesNo("Включить второй источник света? (y/n): ");
                
                if (settings.two_lights) {
                    std::cout << "\nВведите позицию второго источника света:" << std::endl;
                    settings.light2_position.x = getFloat("X: ");
                    settings.light2_position.y = getFloat("Y: ");
                    settings.light2_position.z = getFloat("Z: ");
                }
                
                std::cout << "Настройки сохранены!\n" << std::endl;
                break;
            }
            
            case 5:
                showCurrentSettings(settings);
                break;
                
            case 6:
                return;
        }
    }
}

int UI::getChoice(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Введите число от " << min << " до " << max << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

float UI::getFloat(const std::string& prompt) {
    float value;
    std::cout << prompt;
    while (true) {
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Введите число: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

bool UI::getYesNo(const std::string& prompt) {
    std::string answer;
    while (true) {
        std::cout << prompt;
        std::cin >> answer;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes" || answer == "YES") {
            return true;
        } else if (answer == "n" || answer == "N" || answer == "no" || answer == "No" || answer == "NO") {
            return false;
        } else {
            std::cout << "Введите 'y' или 'n': ";
        }
    }
}

