#ifndef GOAL_H
#define GOAL_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Goal {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    bool active;

public:
    Goal();

    void activate(float spawnX, float groundY, float speed);
    void reset();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    bool isActive() const;
    sf::FloatRect getBounds() const;
};

#endif
