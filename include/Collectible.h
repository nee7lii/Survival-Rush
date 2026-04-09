#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

class Collectible {
public:
  Collectible(const sf::Texture &sharedTexture, sf::Vector2f position,
              sf::Vector2f size, float speed);
  virtual ~Collectible() = default;

  virtual void update(float deltaTime);
  virtual void draw(sf::RenderWindow &window) const;
  virtual void onCollect(int &score, int &hearts, int maxHearts) const = 0;

  bool isOffscreen() const;
  sf::FloatRect getBounds() const;

protected:
  sf::Sprite sprite;
  float speed;
};

class Coin : public Collectible {
public:
  Coin(sf::Vector2f position, float speed);

  void onCollect(int &score, int &hearts, int maxHearts) const override;
};

class FirstAidKit : public Collectible {
public:
  FirstAidKit(sf::Vector2f position, float speed);

  void onCollect(int &score, int &hearts, int maxHearts) const override;
};

#endif
