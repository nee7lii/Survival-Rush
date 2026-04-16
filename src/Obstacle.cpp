#include "../include/Obstacle.h"
#include "../include/AssetLoader.h"

sf::Texture BarbedWire::texture;
bool BarbedWire::textureLoaded = false;
sf::Texture Landmine::texture;
bool Landmine::textureLoaded = false;
sf::Texture Quadcopter::texture;
bool Quadcopter::textureLoaded = false;

Obstacle::Obstacle(const sf::Texture& sharedTexture, const sf::Vector2f& position, const sf::Vector2f& size, float obstacleSpeed)
    : sprite(), speed(obstacleSpeed) {
    sprite.setTexture(sharedTexture, true);

    sf::Vector2u textureSize = sharedTexture.getSize();
    if (textureSize.x > 0 && textureSize.y > 0) {
        sprite.setScale(size.x / textureSize.x, size.y / textureSize.y);
    }

    sprite.setPosition(position);
}

Obstacle::~Obstacle() {
}

void Obstacle::update(float deltaTime) {
    sprite.move(-speed * deltaTime, 0.f);
}

void Obstacle::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Obstacle::isOffscreen() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return bounds.left + bounds.width < -30.f;
}

sf::FloatRect Obstacle::getBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    bounds.left += bounds.width * 0.12f;
    bounds.top += bounds.height * 0.12f;
    bounds.width *= 0.76f;
    bounds.height *= 0.76f;
    return bounds;
}

void BarbedWire::loadSharedTexture() {
    if (!textureLoaded) {
        textureLoaded = AssetLoader::loadTexture(texture, "assets/images/barbedWire.png", "../assets/images/barbedWire.png");
    }
}

BarbedWire::BarbedWire(float spawnX, float groundY, float obstacleSpeed)
    : Obstacle((loadSharedTexture(), texture), sf::Vector2f(spawnX, groundY - 72.f), sf::Vector2f(156.f, 72.f), obstacleSpeed) {
}

void Landmine::loadSharedTexture() {
    if (!textureLoaded) {
        textureLoaded = AssetLoader::loadTexture(texture, "assets/images/landmine.png", "../assets/images/landmine.png");
    }
}

Landmine::Landmine(float spawnX, float groundY, float obstacleSpeed)
    : Obstacle((loadSharedTexture(), texture), sf::Vector2f(spawnX, groundY - 46.f), sf::Vector2f(78.f, 46.f), obstacleSpeed + 20.f) {
}

void Quadcopter::loadSharedTexture() {
    if (!textureLoaded) {
        textureLoaded = AssetLoader::loadTexture(texture, "assets/images/drone.png", "../assets/images/drone.png");
    }
}

Quadcopter::Quadcopter(float spawnX, float obstacleSpeed)
    : Obstacle((loadSharedTexture(), texture), sf::Vector2f(spawnX, 450.f), sf::Vector2f(182.f, 96.f), obstacleSpeed + 35.f) {
}
