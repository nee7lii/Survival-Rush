#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <initializer_list>
#include <string_view>

namespace AssetLoader {

bool loadTexture(sf::Texture &texture,
                 std::initializer_list<std::string_view> relativePaths);
bool loadFont(sf::Font &font,
              std::initializer_list<std::string_view> relativePaths = {});

} // namespace AssetLoader

#endif
