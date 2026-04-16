#!/bin/bash

set -e

PROJECT_DIR="/Users/nee7lii/Desktop/survival-rush4"

cd "$PROJECT_DIR"

if [ ! -x "./build/game" ]; then
    cmake -S . -B build
    cmake --build build
fi

exec ./build/game
