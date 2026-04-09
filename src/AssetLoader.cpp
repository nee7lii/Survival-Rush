#include "../include/AssetLoader.h"

#include <array>
#include <filesystem>
#include <string>

namespace {

bool tryTexturePath(sf::Texture &texture, const std::filesystem::path &path) {
  return std::filesystem::exists(path) && texture.loadFromFile(path);
}

bool tryFontPath(sf::Font &font, const std::filesystem::path &path) {
  return std::filesystem::exists(path) && font.openFromFile(path);
}

} // namespace

namespace AssetLoader {

bool loadTexture(sf::Texture &texture,
                 std::initializer_list<std::string_view> relativePaths) {
  for (const auto relativePath : relativePaths) {
    if (tryTexturePath(texture, std::filesystem::path(relativePath))) {
      return true;
    }
  }
  return false;
}

bool loadFont(sf::Font &font,
              std::initializer_list<std::string_view> relativePaths) {
  for (const auto relativePath : relativePaths) {
    if (tryFontPath(font, std::filesystem::path(relativePath))) {
      return true;
    }
  }

  // macOS system fonts
  constexpr std::array macFonts = {
      "/System/Library/Fonts/Supplemental/Arial Unicode.ttf",
      "/System/Library/Fonts/Supplemental/Verdana.ttf",
      "/System/Library/Fonts/Supplemental/Georgia.ttf",
      "/System/Library/Fonts/SFNS.ttf",
  };
  for (const auto *fontPath : macFonts) {
    if (tryFontPath(font, fontPath)) return true;
  }

  // Linux system fonts
  constexpr std::array linuxFonts = {
      "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
      "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
      "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf",
  };
  for (const auto *fontPath : linuxFonts) {
    if (tryFontPath(font, fontPath)) return true;
  }

  // Windows system fonts
  constexpr std::array winFonts = {
      "C:/Windows/Fonts/arial.ttf",
      "C:/Windows/Fonts/verdana.ttf",
  };
  for (const auto *fontPath : winFonts) {
    if (tryFontPath(font, fontPath)) return true;
  }

  return false;
}

} // namespace AssetLoader
