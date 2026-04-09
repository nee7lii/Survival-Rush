#include "../include/Obstacle.h"

#include "../include/AssetLoader.h"

namespace {

const sf::Texture &getBarbedWireTexture() {
  static const sf::Texture texture = [] {
    sf::Texture loaded;
    AssetLoader::loadTexture(loaded, {"assets/images/barbedWire.png",
                                      "../assets/images/barbedWire.png"});
    return loaded;
  }();
  return texture;
}

const sf::Texture &getQuadcopterTexture() {
  static const sf::Texture texture = [] {
    sf::Texture loaded;
    AssetLoader::loadTexture(loaded, {"assets/images/Quadcopter.png",
                                      "../assets/images/Quadcopter.png"});
    return loaded;
  }();
  return texture;
}

const sf::Texture &getLandmineTexture() {
  static const sf::Texture texture = [] {
    sf::Texture loaded;
    AssetLoader::loadTexture(loaded, {"assets/images/landmine.png",
                                      "../assets/images/landmine.png"});
    return loaded;
  }();
  return texture;
}

} // namespace

Obstacle::Obstacle(const sf::Texture &sharedTexture, sf::Vector2f position,
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

void Obstacle::update(float deltaTime) {
  sprite.move({-speed * deltaTime, 0.f});
}

void Obstacle::draw(sf::RenderWindow &window) const {
  window.draw(sprite);
}

bool Obstacle::isOffscreen() const {
  const auto bounds = sprite.getGlobalBounds();
  return bounds.position.x + bounds.size.x < -30.f;
}

sf::FloatRect Obstacle::getBounds() const {
  auto bounds = sprite.getGlobalBounds();
  bounds.position.x += bounds.size.x * 0.12f;
  bounds.position.y += bounds.size.y * 0.12f;
  bounds.size.x *= 0.76f;
  bounds.size.y *= 0.76f;
  return bounds;
}

BarbedWire::BarbedWire(float spawnX, float groundY, float speed)
    : Obstacle(getBarbedWireTexture(), {spawnX, groundY - 72.f}, {156.f, 72.f},
               speed) {}

Landmine::Landmine(float spawnX, float groundY, float speed)
    : Obstacle(getLandmineTexture(), {spawnX, groundY - 46.f}, {78.f, 46.f},
               speed + 20.f) {}

Quadcopter::Quadcopter(float spawnX, float speed)
    : Obstacle(getQuadcopterTexture(), {spawnX, 450.f}, {182.f, 96.f},
               speed + 35.f) {}
