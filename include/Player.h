#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Player {
private:
    sf::Texture runTexture;
    sf::Texture jumpTexture;
    sf::Texture crouchTexture;
    sf::Texture hitTexture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool onGround;
    bool crouching;
    float hitTimer;

    static const float kJumpVelocity;
    static const float kGravity;
    static const float kWidth;
    static const float kStandHeight;
    static const float kCrouchHeight;
    static const float kHitDuration;

    void applyCurrentTexture();
    void placeFeet(const sf::Vector2f& feetPosition);

public:
    /*
        CM6 : constructeur, attributs, méthode d'initialisation.
    */
    Player();

    void reset(const sf::Vector2f& feetPosition);
    void setCrouching(bool active);
    void jump();
    void triggerHit();
    void update(float deltaTime, float groundY);
    void draw(sf::RenderWindow& window) const;

    /*
        CM8 : méthode const, car elle ne modifie pas l'objet.
    */
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    bool isOnGround() const;
};

#endif
