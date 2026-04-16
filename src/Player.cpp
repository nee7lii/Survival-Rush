#include "../include/Player.h"
#include "../include/AssetLoader.h"

#include <algorithm>

const float Player::kJumpVelocity = -760.f;
const float Player::kGravity = 2100.f;
const float Player::kWidth = 96.f;
const float Player::kStandHeight = 112.f;
const float Player::kCrouchHeight = 72.f;
const float Player::kHitDuration = 0.28f;

Player::Player()
    : runTexture(), jumpTexture(), crouchTexture(), hitTexture(), sprite(), velocity(0.f, 0.f), onGround(true), crouching(false), hitTimer(0.f) {
    AssetLoader::loadTexture(runTexture, "assets/images/player_run.png", "../assets/images/player_run.png");
    AssetLoader::loadTexture(jumpTexture, "assets/images/player_jump.png", "../assets/images/player_jump.png");
    crouchTexture = runTexture;
    AssetLoader::loadTexture(hitTexture, "assets/images/player_hit.png", "../assets/images/player_hit.png");
    applyCurrentTexture();
}

void Player::reset(const sf::Vector2f& feetPosition) {
    velocity.x = 0.f;
    velocity.y = 0.f;
    onGround = true;
    crouching = false;
    hitTimer = 0.f;
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

    crouching = active;
    applyCurrentTexture();
}

void Player::jump() {
    if (!onGround) {
        return;
    }

    velocity.y = kJumpVelocity;
    onGround = false;
    applyCurrentTexture();
}

void Player::triggerHit() {
    hitTimer = kHitDuration;
    applyCurrentTexture();
}

void Player::update(float deltaTime, float groundY) {
    bool wasOnGround = onGround;
    bool wasHit = hitTimer > 0.f;

    hitTimer = std::max(0.f, hitTimer - deltaTime);
    velocity.y += kGravity * deltaTime;
    sprite.move(0.f, velocity.y * deltaTime);

    sf::Vector2f position = sprite.getPosition();
    float height = sprite.getGlobalBounds().height;

    if (position.y + height >= groundY) {
        position.y = groundY - height;
        velocity.y = 0.f;
        onGround = true;
    } else {
        onGround = false;
    }

    sprite.setPosition(position);

    if (wasOnGround != onGround || wasHit != (hitTimer > 0.f)) {
        applyCurrentTexture();
    }
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();

    bounds.left += bounds.width * 0.22f;
    if (crouching) {
        bounds.top += bounds.height * 0.15f;
        bounds.height *= 0.72f;
    } else {
        bounds.top += bounds.height * 0.10f;
        bounds.height *= 0.82f;
    }
    bounds.width *= 0.52f;

    return bounds;
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

bool Player::isOnGround() const {
    return onGround;
}

void Player::applyCurrentTexture() {
    sf::FloatRect oldBounds = sprite.getGlobalBounds();
    bool hadBounds = oldBounds.width > 0.f && oldBounds.height > 0.f;
    sf::Vector2f feetPosition(oldBounds.left + oldBounds.width / 2.f, oldBounds.top + oldBounds.height);

    if (hitTimer > 0.f && hitTexture.getSize().x > 0) {
        sprite.setTexture(hitTexture, true);
    } else if (!onGround && jumpTexture.getSize().x > 0) {
        sprite.setTexture(jumpTexture, true);
    } else if (crouching && crouchTexture.getSize().x > 0) {
        sprite.setTexture(crouchTexture, true);
    } else {
        sprite.setTexture(runTexture, true);
    }

    const sf::Texture* currentTexture = sprite.getTexture();
    if (currentTexture == NULL) {
        return;
    }

    sf::Vector2u textureSize = currentTexture->getSize();
    if (textureSize.x == 0 || textureSize.y == 0) {
        return;
    }

    float height = (crouching && onGround) ? kCrouchHeight : kStandHeight;
    sprite.setScale(kWidth / textureSize.x, height / textureSize.y);

    if (hadBounds) {
        placeFeet(feetPosition);
    }
}

void Player::placeFeet(const sf::Vector2f& feetPosition) {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sprite.setPosition(feetPosition.x - bounds.width / 2.f, feetPosition.y - bounds.height);
}
