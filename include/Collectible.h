#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>


class Collectible {
protected:
    sf::Sprite sprite;
    float speed;

public:
    Collectible(const sf::Texture& sharedTexture, const sf::Vector2f& position, const sf::Vector2f& size, float speed);
    virtual ~Collectible();

    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window) const;
    virtual void onCollect(int& score, int& hearts, int maxHearts) const = 0;

    bool isOffscreen() const;
    sf::FloatRect getBounds() const;
};

class Coin : public Collectible {
private:
    static sf::Texture texture;
    static bool textureLoaded;
    static void loadSharedTexture();

public:
    Coin(const sf::Vector2f& position, float speed);
    void onCollect(int& score, int& hearts, int maxHearts) const;
};

class FirstAidKit : public Collectible {
private:
    static sf::Texture texture;
    static bool textureLoaded;
    static void loadSharedTexture();

public:
    FirstAidKit(const sf::Vector2f& position, float speed);
    void onCollect(int& score, int& hearts, int maxHearts) const;
};

#endif
