#ifndef UI_H
#define UI_H

#include "scene.h"
#include <iostream>
#include <string>

class UI {
public:
    static void showMenu();
    static void configureSettings(SceneSettings& settings);
    static void showCurrentSettings(const SceneSettings& settings);
    static int getChoice(int min, int max);
    static float getFloat(const std::string& prompt);
    static bool getYesNo(const std::string& prompt);
};

#endif // UI_H

