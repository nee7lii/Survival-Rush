cmake_minimum_required(VERSION 3.10)
project(SurvivalRush)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)

add_executable(game
    src/main.cpp
    src/AssetLoader.cpp
    src/Collectible.cpp
    src/Game.cpp
    src/Goal.cpp
    src/HUD.cpp
    src/Menu.cpp
    src/Obstacle.cpp
    src/Player.cpp
)

target_link_libraries(game sfml-graphics sfml-window sfml-system)
