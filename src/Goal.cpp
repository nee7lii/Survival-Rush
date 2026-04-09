#include "../include/Goal.h"

#include "../include/AssetLoader.h"

Goal::Goal() : sprite(texture), speed(0.f), active(false) {
  AssetLoader::loadTexture(texture, {"assets/images/Goal.png",
                                     "../assets/images/Goal.png"});
  sprite.setTexture(texture, true);
}

void Goal::activate(float spawnX, float groundY, float newSpeed) {
  speed = newSpeed;
  active = true;

  const auto textureSize = texture.getSize();
  constexpr sf::Vector2f goalSize{180.f, 210.f};
  if (textureSize.x > 0 && textureSize.y > 0) {
    sprite.setScale({goalSize.x / static_cast<float>(textureSize.x),
                     goalSize.y / static_cast<float>(textureSize.y)});
  }

  sprite.setPosition({spawnX, groundY - goalSize.y + 12.f});
}

void Goal::reset() {
  active = false;
  speed = 0.f;
  sprite.setPosition({2000.f, 2000.f});
}

void Goal::update(float deltaTime) {
  if (!active) {
    return;
  }

  sprite.move({-speed * deltaTime, 0.f});
}

void Goal::draw(sf::RenderWindow &window) const {
  if (active) {
    window.draw(sprite);
  }
}

bool Goal::isActive() const {
  return active;
}

sf::FloatRect Goal::getBounds() const {
  auto bounds = sprite.getGlobalBounds();
  bounds.position.x += bounds.size.x * 0.2f;
  bounds.position.y += bounds.size.y * 0.15f;
  bounds.size.x *= 0.6f;
  bounds.size.y *= 0.75f;
  return bounds;
}
