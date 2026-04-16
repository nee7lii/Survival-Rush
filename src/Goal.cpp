#include "../include/Goal.h"
#include "../include/AssetLoader.h"

Goal::Goal() : sprite(), texture(), speed(0.f), active(false) {
    AssetLoader::loadTexture(texture, "assets/images/Goal.png", "../assets/images/Goal.png");
    sprite.setTexture(texture, true);
    reset();
}

void Goal::activate(float spawnX, float groundY, float newSpeed) {
    speed = newSpeed;
    active = true;

    sf::Vector2u textureSize = texture.getSize();
    const float goalWidth = 180.f;
    const float goalHeight = 210.f;

    if (textureSize.x > 0 && textureSize.y > 0) {
        sprite.setScale(goalWidth / textureSize.x, goalHeight / textureSize.y);
    }

    sprite.setPosition(spawnX, groundY - goalHeight + 12.f);
}

void Goal::reset() {
    active = false;
    speed = 0.f;
    sprite.setPosition(2000.f, 2000.f);
}

void Goal::update(float deltaTime) {
    if (active) {
        sprite.move(-speed * deltaTime, 0.f);
    }
}

void Goal::draw(sf::RenderWindow& window) const {
    if (active) {
        window.draw(sprite);
    }
}

bool Goal::isActive() const {
    return active;
}

sf::FloatRect Goal::getBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    bounds.left += bounds.width * 0.10f;
    bounds.top += bounds.height * 0.08f;
    bounds.width *= 0.80f;
    bounds.height *= 0.84f;
    return bounds;
}
