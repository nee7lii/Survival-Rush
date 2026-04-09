#include "../include/Menu.h"

#include "../include/AssetLoader.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

Menu::Menu() : font(), fontLoaded(AssetLoader::loadFont(font)) {}

void Menu::draw(sf::RenderWindow &window, Screen screen, int score) const {
  sf::RectangleShape overlay(
      {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
  overlay.setFillColor(sf::Color(10, 10, 10, screen == Screen::Start ? 170 : 205));
  window.draw(overlay);

  if (!fontLoaded) {
    return;
  }

  const std::string heading =
      screen == Screen::Start ? "SURVIVAL RUSH"
                              : screen == Screen::Win ? "MISSION COMPLETE"
                                                      : "GAME OVER";
  const sf::Color headingColor =
      screen == Screen::Win ? sf::Color(100, 219, 129)
                            : screen == Screen::GameOver ? sf::Color(236, 93, 80)
                                                         : sf::Color(247, 216, 143);

  drawCenteredText(window, heading, 56, 140.f, headingColor);

  if (screen == Screen::Start) {
    drawCenteredText(window, "Desert runner: jump over barbed wire, crouch under drones.",
                     24, 250.f, sf::Color::White);
    drawCenteredText(window, "Up Arrow / Space = jump   |   Down Arrow = crouch", 24,
                     300.f, sf::Color::White);
    drawCenteredText(window, "Avoid barbed wire and landmines, collect supplies, then reach the bunker in 60 seconds.",
                     24, 350.f, sf::Color::White);
    drawCenteredText(window, "Press Enter to start", 28, 450.f,
                     sf::Color(255, 232, 179));
    return;
  }

  drawCenteredText(window, "Score: " + std::to_string(score), 28, 260.f,
                   sf::Color::White);
  drawCenteredText(window, "Press Enter to play again", 28, 340.f,
                   sf::Color(255, 232, 179));
  drawCenteredText(window, "Press Escape to quit", 24, 390.f,
                   sf::Color(225, 225, 225));
}

void Menu::drawCenteredText(sf::RenderWindow &window, const std::string &text,
                            unsigned int size, float y,
                            sf::Color color) const {
  sf::Text drawable(font, text, size);
  drawable.setFillColor(color);
  drawable.setStyle(sf::Text::Bold);
  const auto bounds = drawable.getLocalBounds();
  drawable.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                      bounds.position.y + bounds.size.y / 2.f});
  drawable.setPosition({static_cast<float>(window.getSize().x) / 2.f, y});
  window.draw(drawable);
}
