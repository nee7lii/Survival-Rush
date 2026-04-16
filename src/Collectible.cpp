#include "../include/Collectible.h"
#include "../include/AssetLoader.h"

sf::Texture Coin::texture;
bool Coin::textureLoaded = false;
sf::Texture FirstAidKit::texture;
bool FirstAidKit::textureLoaded = false;

Collectible::Collectible(const sf::Texture& sharedTexture, const sf::Vector2f& position, const sf::Vector2f& size, float collectibleSpeed)
    : sprite(), speed(collectibleSpeed) {
    sprite.setTexture(sharedTexture, true);

    sf::Vector2u textureSize = sharedTexture.getSize();
    if (textureSize.x > 0 && textureSize.y > 0) {
        sprite.setScale(size.x / textureSize.x, size.y / textureSize.y);
    }

    sprite.setPosition(position);
}

Collectible::~Collectible() {
}

void Collectible::update(float deltaTime) {
    sprite.move(-speed * deltaTime, 0.f);
}

void Collectible::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Collectible::isOffscreen() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return bounds.left + bounds.width < -20.f;
}

sf::FloatRect Collectible::getBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    bounds.left += bounds.width * 0.15f;
    bounds.top += bounds.height * 0.15f;
    bounds.width *= 0.70f;
    bounds.height *= 0.70f;
    return bounds;
}

void Coin::loadSharedTexture() {
    if (!textureLoaded) {
        textureLoaded = AssetLoader::loadTexture(texture, "assets/images/coin.png", "../assets/images/coin.png");
    }
}

Coin::Coin(const sf::Vector2f& position, float collectibleSpeed)
    : Collectible((loadSharedTexture(), texture), position, sf::Vector2f(84.f, 84.f), collectibleSpeed) {
}

void Coin::onCollect(int& score, int& hearts, int maxHearts) const {
    (void)hearts;
    (void)maxHearts;
    score += 10;
}

void FirstAidKit::loadSharedTexture() {
    if (!textureLoaded) {
        textureLoaded = AssetLoader::loadTexture(texture, "assets/images/first_aid.png", "../assets/images/first_aid.png");
    }
}

FirstAidKit::FirstAidKit(const sf::Vector2f& position, float collectibleSpeed)
    : Collectible((loadSharedTexture(), texture), position, sf::Vector2f(96.f, 96.f), collectibleSpeed) {
}

void FirstAidKit::onCollect(int& score, int& hearts, int maxHearts) const {
    (void)score;
    if (hearts < maxHearts) {
        hearts++;
    }
}
