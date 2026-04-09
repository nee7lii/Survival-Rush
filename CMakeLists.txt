cmake_minimum_required(VERSION 3.16)
project(SurvivalRush LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_PREFIX_PATH "/usr/local" "/opt/homebrew")

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

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

target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(game PRIVATE cxx_std_17)

target_link_libraries(game PRIVATE SFML::Graphics SFML::Window SFML::System)

if(APPLE)
    set_target_properties(game PROPERTIES
        BUILD_RPATH "/usr/local/lib;/opt/homebrew/lib"
    )
endif()
