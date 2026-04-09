#include "../include/Player.h"

#include "../include/AssetLoader.h"

Player::Player()
    : runTexture(), crouchTexture(), sprite(runTexture), velocity(0.f, 0.f),
      onGround(true), crouching(false) {
  // "RunPlayer..png" has a double dot in the actual filename - keep both spellings
  AssetLoader::loadTexture(runTexture, {"assets/images/RunPlayer..png",
                                        "../assets/images/RunPlayer..png"});
  AssetLoader::loadTexture(crouchTexture, {"assets/images/down.png",
                                           "../assets/images/down.png"});
  applyCurrentTexture();
}

void Player::reset(sf::Vector2f feetPosition) {
  velocity = {0.f, 0.f};
  onGround = true;
  crouching = false;
  applyCurrentTexture();
  placeFeet(feetPosition);
}

void Player::setCrouching(bool active) {
  if (!onGround) {
    active = false;
  }

  if (crouching == active) {
    return;
  }

  const auto feet = sf::Vector2f{
      sprite.getPosition().x + sprite.getGlobalBounds().size.x / 2.f,
      sprite.getPosition().y + sprite.getGlobalBounds().size.y};

  crouching = active;
  applyCurrentTexture();
  placeFeet(feet);
}

void Player::jump() {
  if (!onGround) {
    return;
  }

  velocity.y = kJumpVelocity;
  onGround = false;
}

void Player::update(float deltaTime, float groundY) {
  velocity.y += kGravity * deltaTime;
  sprite.move({0.f, velocity.y * deltaTime});

  auto position = sprite.getPosition();
  const float height = sprite.getGlobalBounds().size.y;
  if (position.y + height >= groundY) {
    position.y = groundY - height;
    velocity.y = 0.f;
    onGround = true;
  } else {
    onGround = false;
  }

  sprite.setPosition(position);
}

void Player::draw(sf::RenderWindow &window) const {
  window.draw(sprite);
}

sf::FloatRect Player::getBounds() const {
  auto bounds = sprite.getGlobalBounds();
  bounds.position.x += bounds.size.x * 0.22f;
  bounds.position.y += crouching ? bounds.size.y * 0.15f : bounds.size.y * 0.1f;
  bounds.size.x *= 0.52f;
  bounds.size.y *= crouching ? 0.72f : 0.82f;
  return bounds;
}

sf::Vector2f Player::getPosition() const {
  return sprite.getPosition();
}

void Player::applyCurrentTexture() {
  if (crouching && crouchTexture.getSize().x > 0) {
    sprite.setTexture(crouchTexture, true);
  } else {
    sprite.setTexture(runTexture, true);
  }

  const auto textureSize = sprite.getTexture().getSize();
  if (textureSize.x == 0 || textureSize.y == 0) {
    return;
  }

  const float height = crouching ? kCrouchHeight : kStandHeight;
  sprite.setScale({kWidth / static_cast<float>(textureSize.x),
                   height / static_cast<float>(textureSize.y)});
}

void Player::placeFeet(sf::Vector2f feetPosition) {
  const auto bounds = sprite.getGlobalBounds();
  sprite.setPosition(
      {feetPosition.x - bounds.size.x / 2.f, feetPosition.y - bounds.size.y});
}
