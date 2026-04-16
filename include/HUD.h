#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class HUD {
private:
    sf::Font font;
    bool fontLoaded;
    sf::Texture heartFullTexture;
    sf::Texture heartEmptyTexture;
    bool heartFullTextureLoaded;
    bool heartEmptyTextureLoaded;

public:
    HUD();
    void draw(sf::RenderWindow& window, int hearts, int score, float timeLeft, float progress) const;
};

#endif
