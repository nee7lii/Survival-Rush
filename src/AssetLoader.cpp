#include "../include/AssetLoader.h"

#include <fstream>

namespace {
    bool fileExists(const std::string& path) {
        std::ifstream file(path.c_str());
        return file.good();
    }
}

bool AssetLoader::loadTexture(sf::Texture& texture, const std::string& path1, const std::string& path2) {
    if (!path1.empty() && fileExists(path1) && texture.loadFromFile(path1)) {
        return true;
    }

    if (!path2.empty() && fileExists(path2) && texture.loadFromFile(path2)) {
        return true;
    }

    return false;
}

bool AssetLoader::loadFont(sf::Font& font, const std::string& path1, const std::string& path2) {
    if (!path1.empty() && fileExists(path1) && font.loadFromFile(path1)) {
        return true;
    }

    if (!path2.empty() && fileExists(path2) && font.loadFromFile(path2)) {
        return true;
    }

    /*
        CM3 : utilisation simple de std::string.
        On essaye ensuite quelques polices système selon le système d'exploitation.
    */
    if (fileExists("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") &&
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        return true;
    }
    if (fileExists("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf") &&
        font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf")) {
        return true;
    }
    if (fileExists("C:/Windows/Fonts/arial.ttf") &&
        font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        return true;
    }
    if (fileExists("/System/Library/Fonts/Supplemental/Arial.ttf") &&
        font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        return true;
    }

    return false;
}
