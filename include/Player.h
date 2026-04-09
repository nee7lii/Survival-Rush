#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Player {
public:
  Player();

  void reset(sf::Vector2f feetPosition);
  void setCrouching(bool active);
  void jump();
  void update(float deltaTime, float groundY);
  void draw(sf::RenderWindow &window) const;

  sf::FloatRect getBounds() const;
  sf::Vector2f getPosition() const;

private:
  sf::Texture runTexture;
  sf::Texture crouchTexture;
  sf::Sprite sprite;
  sf::Vector2f velocity;
  bool onGround;
  bool crouching;

  static constexpr float kJumpVelocity = -760.f;
  static constexpr float kGravity = 2100.f;
  static constexpr float kWidth = 96.f;
  static constexpr float kStandHeight = 112.f;
  static constexpr float kCrouchHeight = 72.f;

  void applyCurrentTexture();
  void placeFeet(sf::Vector2f feetPosition);
};

#endif
