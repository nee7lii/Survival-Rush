#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <string>

class Menu {
public:
  enum class Screen { Start, Win, GameOver };

  Menu();

  void draw(sf::RenderWindow &window, Screen screen, int score) const;

private:
  sf::Font font;
  bool fontLoaded;

  void drawCenteredText(sf::RenderWindow &window, const std::string &text,
                        unsigned int size, float y,
                        sf::Color color) const;
};

#endif
