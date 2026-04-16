# Survival Rush

`Survival Rush` is a 2D runner game developed in C++ with SFML. The player must avoid obstacles, collect useful items, survive long enough for the bunker to appear, and reach it before losing all hearts.

## Project Overview

This project includes:

- object-oriented C++ structure with multiple classes
- sprite-based rendering using local assets
- menu, about, win, and lose screens
- collisions, collectibles, obstacles, and a complete playable loop

## Requirements

To build and run the project, the machine should have:

- a C++17 compiler
- CMake 3.10 or newer
- SFML 2.5 or newer

SFML modules used:

- `graphics`
- `window`
- `system`

## Build

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

## Run

After building:

```bash
./build/game
```

The project also includes:

```bash
./Survival\ Rush.command
```

## Controls

- `Left Click`: use menu and end-screen buttons
- `Space` or `Up Arrow`: jump
- `Down Arrow`, `S`, `Left Shift`, or `Right Shift`: crouch
- `Enter`: restart after victory or game over
- `Escape`: quit the game or return from the About screen

## Gameplay

- avoid ground and air obstacles
- collect coins to increase score
- collect first-aid kits to recover hearts
- survive until the bunker appears
- reach the bunker to win

## Main Features

- image-based main menu
- image-based about screen
- horizontally scrolling gameplay background
- player run, jump, and hit states
- multiple obstacle types
- collectible coins and health kits
- HUD with hearts, timer, and score
- image-based win and lose screens

## Project Structure

```text
survival-rush4/
├── CMakeLists.txt
├── README.md
├── Survival Rush.command
├── assets/
│   ├── fonts/
│   └── images/
├── include/
└── src/
```

## Important Folders

- `src/`: implementation files
- `include/`: header files
- `assets/images/`: player, obstacle, collectible, HUD, and screen images
- `assets/fonts/`: font used by the UI text

## Notes

- All game assets required to run the project are included locally.
- The project uses sprite/image rendering for gameplay objects and screens.
- Generated build files are not included in the cleaned submission folder.
