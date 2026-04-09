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

#include <memory>
#include <random>
#include <vector>

class Game {
public:
  Game();

  void start();

private:
  enum class State { StartMenu, Running, GameOver, Victory };

  static constexpr unsigned int kWindowWidth = 1280;
  static constexpr unsigned int kWindowHeight = 720;
  static constexpr float kGroundY = 620.f;
  static constexpr float kRunDuration = 60.f;
  static constexpr int kMaxHearts = 3;
  static constexpr float kWorldSpeed = 560.f;
  static constexpr float kGoalRevealTime = 54.f;

  sf::RenderWindow window;
  sf::Clock frameClock;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;

  Player player;
  HUD hud;
  Menu menu;
  Goal goal;
  std::vector<std::unique_ptr<Obstacle>> obstacles;
  std::vector<std::unique_ptr<Collectible>> collectibles;

  State state;
  float elapsedTime;
  float obstacleSpawnTimer;
  float collectibleSpawnTimer;
  float nextObstacleSpawn;
  float nextCollectibleSpawn;
  float backgroundOffset;
  int hearts;
  int score;
  bool goalSpawned;
  std::mt19937 rng;

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
  float randomRange(float minValue, float maxValue);
};

#endif
