cmake_minimum_required(VERSION 3.10)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/application.cpp
    src/scene.cpp
    src/ray_tracer.cpp
    src/ui.cpp
    src/geometry/figure.cpp
    src/geometry/side.cpp
    src/geometry/sphere.cpp
    src/utils/image_writer.cpp
)

# Заголовочные файлы
set(HEADERS
    src/application.h
    src/scene.h
    src/ray_tracer.h
    src/ui.h
    src/geometry/figure.h
    src/geometry/side.h
    src/geometry/sphere.h
    src/geometry/point3d.h
    src/geometry/vector3d.h
    src/geometry/ray.h
    src/graphics/color.h
    src/graphics/material.h
    src/graphics/light.h
    src/graphics/camera.h
    src/utils/image_writer.h
    src/utils/math_utils.h
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Устанавливаем выходной каталог
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
