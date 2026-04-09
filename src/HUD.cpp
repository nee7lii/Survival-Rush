#include "../include/HUD.h"

#include "../include/AssetLoader.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <algorithm>
#include <iomanip>
#include <sstream>

HUD::HUD() : font(), fontLoaded(AssetLoader::loadFont(font)) {}

void HUD::draw(sf::RenderWindow &window, int hearts, int score, float timeLeft,
               float progress) const {
  // Layout (all Y relative to panel top at 18):
  //   Row 1 (y=30): label text
  //   Row 2 (y=58): hearts (left) | progress bar (right)
  //   Row 3 (y=96): timer text (left) | score text (right)

  sf::RectangleShape panel({440.f, 138.f});
  panel.setPosition({22.f, 18.f});
  panel.setFillColor(sf::Color(16, 24, 31, 185));
  panel.setOutlineThickness(2.f);
  panel.setOutlineColor(sf::Color(245, 221, 171, 180));
  window.draw(panel);

  // Row 1 — label
  if (fontLoaded) {
    sf::Text labelText(font, "Survive to the bunker", 17);
    labelText.setPosition({42.f, 24.f});
    labelText.setFillColor(sf::Color(244, 226, 182));
    window.draw(labelText);
  }

  // Row 2 — hearts on the left
  for (int i = 0; i < 3; ++i) {
    drawHeart(window, {38.f + i * 40.f, 56.f}, i < hearts);
  }

  // Row 2 — progress bar on the right, same vertical centre as hearts
  sf::RectangleShape progressFrame({210.f, 18.f});
  progressFrame.setPosition({220.f, 62.f});
  progressFrame.setFillColor(sf::Color(39, 52, 62, 220));
  progressFrame.setOutlineThickness(2.f);
  progressFrame.setOutlineColor(sf::Color(237, 213, 165, 180));
  window.draw(progressFrame);

  sf::RectangleShape progressFill({206.f * std::clamp(progress, 0.f, 1.f), 12.f});
  progressFill.setPosition({222.f, 65.f});
  progressFill.setFillColor(sf::Color(239, 186, 72));
  window.draw(progressFill);

  // Row 3 — timer and score
  if (!fontLoaded) {
    return;
  }

  std::ostringstream timerStream;
  timerStream << std::fixed << std::setprecision(1) << std::max(0.f, timeLeft);

  sf::Text timerText(font, "Time: " + timerStream.str() + "s", 24);
  timerText.setPosition({36.f, 100.f});
  timerText.setFillColor(sf::Color::White);
  window.draw(timerText);

  sf::Text scoreText(font, "Score: " + std::to_string(score), 24);
  scoreText.setPosition({234.f, 100.f});
  scoreText.setFillColor(sf::Color::White);
  window.draw(scoreText);
}

void HUD::drawHeart(sf::RenderWindow &window, sf::Vector2f position,
                    bool filled) const {
  const sf::Color color = filled ? sf::Color(214, 58, 72) : sf::Color(95, 103, 112);

  sf::CircleShape leftLobe(10.f);
  leftLobe.setFillColor(color);
  leftLobe.setPosition(position);
  window.draw(leftLobe);

  sf::CircleShape rightLobe(10.f);
  rightLobe.setFillColor(color);
  rightLobe.setPosition({position.x + 12.f, position.y});
  window.draw(rightLobe);

  sf::ConvexShape point;
  point.setPointCount(3);
  point.setPoint(0, {position.x - 1.f, position.y + 11.f});
  point.setPoint(1, {position.x + 23.f, position.y + 11.f});
  point.setPoint(2, {position.x + 11.f, position.y + 31.f});
  point.setFillColor(color);
  window.draw(point);
}
