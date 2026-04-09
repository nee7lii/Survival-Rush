#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class HUD {
public:
  HUD();

  void draw(sf::RenderWindow &window, int hearts, int score, float timeLeft,
            float progress) const;

private:
  sf::Font font;
  bool fontLoaded;

  void drawHeart(sf::RenderWindow &window, sf::Vector2f position,
                 bool filled) const;
};

#endif
