#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

class Obstacle {
public:
  Obstacle(const sf::Texture &sharedTexture, sf::Vector2f position,
           sf::Vector2f size, float speed);
  virtual ~Obstacle() = default;

  virtual void update(float deltaTime);
  virtual void draw(sf::RenderWindow &window) const;
  bool isOffscreen() const;
  sf::FloatRect getBounds() const;

protected:
  sf::Sprite sprite;
  float speed;
};

class BarbedWire : public Obstacle {
public:
  BarbedWire(float spawnX, float groundY, float speed);
};

class Landmine : public Obstacle {
public:
  Landmine(float spawnX, float groundY, float speed);
};

class Quadcopter : public Obstacle {
public:
  Quadcopter(float spawnX, float speed);
};

#endif
