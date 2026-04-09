#include "../include/Collectible.h"

#include "../include/AssetLoader.h"

#include <algorithm>

namespace {

const sf::Texture &getCoinTexture() {
  static const sf::Texture texture = [] {
    sf::Texture loaded;
    AssetLoader::loadTexture(loaded, {"assets/images/coin.png",
                                      "../assets/images/coin.png"});
    return loaded;
  }();
  return texture;
}

const sf::Texture &getFirstAidTexture() {
  static const sf::Texture texture = [] {
    sf::Texture loaded;
    AssetLoader::loadTexture(loaded, {"assets/images/first-aid kit.png",
                                      "../assets/images/first-aid kit.png"});
    return loaded;
  }();
  return texture;
}

} // namespace

Collectible::Collectible(const sf::Texture &sharedTexture, sf::Vector2f position,
                         sf::Vector2f size, float speed)
    : sprite(sharedTexture), speed(speed) {
  sprite.setTexture(sharedTexture, true);

  const auto textureSize = sharedTexture.getSize();
  if (textureSize.x > 0 && textureSize.y > 0) {
    sprite.setScale({size.x / static_cast<float>(textureSize.x),
                     size.y / static_cast<float>(textureSize.y)});
  }

  sprite.setPosition(position);
}

void Collectible::update(float deltaTime) {
  sprite.move({-speed * deltaTime, 0.f});
}

void Collectible::draw(sf::RenderWindow &window) const {
  window.draw(sprite);
}

bool Collectible::isOffscreen() const {
  const auto bounds = sprite.getGlobalBounds();
  return bounds.position.x + bounds.size.x < -20.f;
}

sf::FloatRect Collectible::getBounds() const {
  auto bounds = sprite.getGlobalBounds();
  bounds.position.x += bounds.size.x * 0.15f;
  bounds.position.y += bounds.size.y * 0.15f;
  bounds.size.x *= 0.7f;
  bounds.size.y *= 0.7f;
  return bounds;
}

Coin::Coin(sf::Vector2f position, float speed)
    : Collectible(getCoinTexture(), position, {84.f, 84.f}, speed) {}

void Coin::onCollect(int &score, int &hearts, int maxHearts) const {
  static_cast<void>(hearts);
  static_cast<void>(maxHearts);
  score += 10;
}

FirstAidKit::FirstAidKit(sf::Vector2f position, float speed)
    : Collectible(getFirstAidTexture(), position, {96.f, 96.f},
                  speed) {}

void FirstAidKit::onCollect(int &score, int &hearts, int maxHearts) const {
  static_cast<void>(score);
  hearts = std::min(maxHearts, hearts + 1);
}
