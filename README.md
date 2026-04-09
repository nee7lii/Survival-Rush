# Survival Rush

## Team
- Student 1: [Brahim ENNAHLI]
- Student 2: [Yassine OUBELAID]

## Project Description
Survival Rush is a simple 2D endless runner built in C++ with SFML. The player moves left and right, jumps over obstacles, crouches under pressure, and survives as long as possible while the score increases over time.

## Current Features
- SFML game window
- Real-time player movement
- Jump and crouch actions
- Random obstacle spawning
- Collision detection
- Score and elapsed time tracking
- Restart after game over

## Controls
- Up / Space: jump
- Down: crouch
- Enter: restart after game over
- Escape: quit

## Technologies
- C++
- Object-Oriented Programming
- CMake
- SFML 3

## Build
```bash
cmake -S . -B build
cmake --build build
```

## Run
```bash
./build/game
```

## Project Structure
```text
Survival-Rush/
├── build/
├── docs/
├── include/
│   ├── Game.h
│   ├── Obstacle.h
│   └── Player.h
├── src/
│   ├── Game.cpp
│   ├── Obstacle.cpp
│   ├── Player.cpp
│   └── main.cpp
├── CMakeLists.txt
├── .gitignore
└── README.md
```
