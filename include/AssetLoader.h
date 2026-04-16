#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class AssetLoader {
public:
    /*
        CM1/CM2 : déclaration d'une classe et de fonctions membres statiques.
        Cette classe sert seulement à centraliser le chargement des ressources.
    */
    static bool loadTexture(sf::Texture& texture, const std::string& path1, const std::string& path2 = "");
    static bool loadFont(sf::Font& font, const std::string& path1 = "", const std::string& path2 = "");
};

#endif
