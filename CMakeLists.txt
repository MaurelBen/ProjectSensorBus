cmake_minimum_required(VERSION 3.20)
project(ProjectSensorBus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

# Tout sauf main.cpp : la logique du programme
add_library(sensor_lib STATIC
    src/ISensor.cpp
    src/TemperatureSensor.cpp
    src/WindSensor.cpp
    src/SensorManager.cpp
    src/SensorReader.cpp 
    src/UserInterface.cpp
)
target_include_directories(sensor_lib PUBLIC include)
target_link_libraries(sensor_lib PUBLIC Threads::Threads)

# L'exécutable
add_executable(sensor_sim src/main.cpp)
target_link_libraries(sensor_sim PRIVATE sensor_lib)

# Options du compilateur
if(MSVC)
    target_compile_options(sensor_lib PUBLIC /W4 /utf-8)
else()
    target_compile_options(sensor_lib PUBLIC -Wall -Wextra -Wpedantic)
endif()