#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Obstacle {
protected:
    sf::Sprite sprite;
    float speed;

public:
    /*
        Projet + POO : classe de base pour regrouper le comportement commun
        de tous les obstacles.
    */
    Obstacle(const sf::Texture& sharedTexture, const sf::Vector2f& position, const sf::Vector2f& size, float speed);
    virtual ~Obstacle();

    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window) const;
    bool isOffscreen() const;
    sf::FloatRect getBounds() const;
};

class BarbedWire : public Obstacle {
private:
    static sf::Texture texture;
    static bool textureLoaded;
    static void loadSharedTexture();

public:
    BarbedWire(float spawnX, float groundY, float speed);
};

class Landmine : public Obstacle {
private:
    static sf::Texture texture;
    static bool textureLoaded;
    static void loadSharedTexture();

public:
    Landmine(float spawnX, float groundY, float speed);
};

class Quadcopter : public Obstacle {
private:
    static sf::Texture texture;
    static bool textureLoaded;
    static void loadSharedTexture();

public:
    Quadcopter(float spawnX, float speed);
};

#endif
