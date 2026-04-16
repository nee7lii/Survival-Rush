#ifndef GAME_H
#define GAME_H

#include "Collectible.h"
#include "Goal.h"
#include "HUD.h"
#include "Menu.h"
#include "Obstacle.h"
#include "Player.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

class Game {
public:
    enum State {
        StartMenu,
        AboutMenu,
        Running,
        GameOver,
        Victory
    };

private:
    static const unsigned int kWindowWidth = 1280;
    static const unsigned int kWindowHeight = 720;
    static const int kMaxHearts = 3;
    static constexpr float kGroundY = 620.f;
    static constexpr float kRunDuration = 60.f;
    static constexpr float kWorldSpeed = 560.f;
    static constexpr float kGoalRevealTime = 54.f;

    sf::RenderWindow window;
    sf::Clock frameClock;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Sprite backgroundSprite2;
    sf::Sprite groundSprite;

    Player player;
    HUD hud;
    Menu menu;
    Goal goal;

    /*
        CM4 : utilisation de vector comme tableau dynamique.
        Projet : polymorphisme via des pointeurs sur la classe de base.
    */
    std::vector<Obstacle*> obstacles;
    std::vector<Collectible*> collectibles;

    State state;
    float elapsedTime;
    float obstacleSpawnTimer;
    float collectibleSpawnTimer;
    float nextObstacleSpawn;
    float nextCollectibleSpawn;
    float backgroundOffset;
    float backgroundX1;
    float backgroundX2;
    int hearts;
    int score;
    bool goalSpawned;
    bool crouchHeld;

    void processEvents();
    void update(float deltaTime);
    void render();
    void resetRun();
    void startRun();
    void spawnObstacle();
    void spawnCollectible();
    void updateGameplay(float deltaTime);
    void handleCollisions();
    void drawBackground();
    void drawGround();
    void pruneEntities();
    void clearObstacles();
    void clearCollectibles();
    float randomRange(float minValue, float maxValue) const;
    bool isCrouchKey(sf::Keyboard::Key key) const;

public:
    Game();
    ~Game();
    void start();
};

#endif
