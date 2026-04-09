#include "../include/Game.h"

#include "../include/AssetLoader.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <algorithm>

Game::Game()
    : window(sf::VideoMode({kWindowWidth, kWindowHeight}), "Survival Rush"),
      frameClock(),
      backgroundTexture(),
      backgroundSprite(backgroundTexture),
      player(),
      hud(),
      menu(),
      goal(),
      obstacles(),
      collectibles(),
      state(State::StartMenu),
      elapsedTime(0.f),
      obstacleSpawnTimer(0.f),
      collectibleSpawnTimer(0.f),
      nextObstacleSpawn(1.4f),
      nextCollectibleSpawn(1.1f),
      backgroundOffset(0.f),
      hearts(kMaxHearts),
      score(0),
      goalSpawned(false),
      rng(std::random_device{}()) {
  window.setFramerateLimit(60);
  AssetLoader::loadTexture(backgroundTexture, {"assets/images/TheRoad.png",
                                               "../assets/images/TheRoad.png"});
  backgroundSprite.setTexture(backgroundTexture, true);
  resetRun();
}

void Game::start() {
  while (window.isOpen()) {
    processEvents();
    const float deltaTime = std::min(frameClock.restart().asSeconds(), 0.033f);

    if (state == State::Running) {
      update(deltaTime);
    }

    render();
  }
}

void Game::processEvents() {
  while (const auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
      continue;
    }

    if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (keyPressed->code == sf::Keyboard::Key::Escape) {
        window.close();
      } else if (keyPressed->code == sf::Keyboard::Key::Enter) {
        if (state != State::Running) {
          startRun();
        }
      } else if ((keyPressed->code == sf::Keyboard::Key::Space ||
                  keyPressed->code == sf::Keyboard::Key::Up) &&
                 state == State::Running) {
        player.jump();
      }
    }

    if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>()) {
      if (keyReleased->code == sf::Keyboard::Key::Down) {
        player.setCrouching(false);
      }
    }
  }
}

void Game::update(float deltaTime) {
  player.setCrouching(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down));

  const auto textureSize = backgroundTexture.getSize();
  if (textureSize.x > 0 && textureSize.y > 0) {
    const float scale = std::max(
        static_cast<float>(kWindowWidth) / static_cast<float>(textureSize.x),
        static_cast<float>(kWindowHeight) / static_cast<float>(textureSize.y));
    const float tileWidth = static_cast<float>(textureSize.x) * scale;

    backgroundOffset += kWorldSpeed * deltaTime;
    if (backgroundOffset >= tileWidth) {
      backgroundOffset -= tileWidth;
    }
  }

  updateGameplay(deltaTime);
}

void Game::render() {
  window.clear(sf::Color(225, 206, 162));
  drawBackground();
  drawGround();

  goal.draw(window);

  for (const auto &collectible : collectibles) {
    collectible->draw(window);
  }

  for (const auto &obstacle : obstacles) {
    obstacle->draw(window);
  }

  player.draw(window);

  const float timeLeft = std::max(0.f, kRunDuration - elapsedTime);
  hud.draw(window, hearts, score, timeLeft, elapsedTime / kRunDuration);

  if (state == State::StartMenu) {
    menu.draw(window, Menu::Screen::Start, score);
  } else if (state == State::Victory) {
    menu.draw(window, Menu::Screen::Win, score);
  } else if (state == State::GameOver) {
    menu.draw(window, Menu::Screen::GameOver, score);
  }

  window.display();
}

void Game::resetRun() {
  elapsedTime = 0.f;
  obstacleSpawnTimer = 0.f;
  collectibleSpawnTimer = 0.f;
  nextObstacleSpawn = randomRange(1.0f, 1.7f);
  nextCollectibleSpawn = randomRange(0.8f, 1.4f);
  hearts = kMaxHearts;
  score = 0;
  backgroundOffset = 0.f;
  goalSpawned = false;
  obstacles.clear();
  collectibles.clear();
  goal.reset();
  player.reset({190.f, kGroundY});
  frameClock.restart();
}

void Game::startRun() {
  resetRun();
  state = State::Running;
}

void Game::spawnObstacle() {
  const float roll = randomRange(0.f, 1.f);

  if (roll < 0.4f) {
    obstacles.push_back(
        std::make_unique<BarbedWire>(kWindowWidth + randomRange(0.f, 120.f),
                                     kGroundY, kWorldSpeed));
  } else if (roll < 0.75f) {
    obstacles.push_back(
        std::make_unique<Landmine>(kWindowWidth + randomRange(0.f, 120.f),
                                   kGroundY, kWorldSpeed));
  } else {
    obstacles.push_back(
        std::make_unique<Quadcopter>(kWindowWidth + randomRange(0.f, 120.f),
                                     kWorldSpeed));
  }
}

void Game::spawnCollectible() {
  const bool spawnAidKit = randomRange(0.f, 1.f) < 0.18f;
  const float x = kWindowWidth + randomRange(0.f, 120.f);

  if (spawnAidKit) {
    collectibles.push_back(
        std::make_unique<FirstAidKit>(sf::Vector2f{x, kGroundY - 68.f},
                                      kWorldSpeed));
    return;
  }

  const bool airCoin = randomRange(0.f, 1.f) < 0.45f;
  const float y = airCoin ? 355.f : (kGroundY - 48.f);
  collectibles.push_back(
      std::make_unique<Coin>(sf::Vector2f{x, y}, kWorldSpeed));
}

void Game::updateGameplay(float deltaTime) {
  elapsedTime += deltaTime;
  player.update(deltaTime, kGroundY);

  obstacleSpawnTimer += deltaTime;
  collectibleSpawnTimer += deltaTime;

  if (obstacleSpawnTimer >= nextObstacleSpawn) {
    spawnObstacle();
    obstacleSpawnTimer = 0.f;
    nextObstacleSpawn = randomRange(1.0f, 1.9f);
  }

  if (collectibleSpawnTimer >= nextCollectibleSpawn) {
    spawnCollectible();
    collectibleSpawnTimer = 0.f;
    nextCollectibleSpawn = randomRange(0.7f, 1.5f);
  }

  if (!goalSpawned && elapsedTime >= kGoalRevealTime) {
    goal.activate(kWindowWidth + 160.f, kGroundY, kWorldSpeed);
    goalSpawned = true;
  }

  for (auto &obstacle : obstacles) {
    obstacle->update(deltaTime);
  }

  for (auto &collectible : collectibles) {
    collectible->update(deltaTime);
  }

  goal.update(deltaTime);
  handleCollisions();
  pruneEntities();

  if (state == State::Running && elapsedTime >= kRunDuration) {
    state = State::GameOver;
  }
}

void Game::handleCollisions() {
  const auto playerBounds = player.getBounds();

  obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                                 [&](const std::unique_ptr<Obstacle> &obstacle) {
                                   if (playerBounds.findIntersection(
                                           obstacle->getBounds())
                                           .has_value()) {
                                     --hearts;
                                     if (hearts <= 0) {
                                       hearts = 0;
                                       state = State::GameOver;
                                     }
                                     return true;
                                   }
                                   return false;
                                 }),
                  obstacles.end());

  collectibles.erase(
      std::remove_if(collectibles.begin(), collectibles.end(),
                     [&](const std::unique_ptr<Collectible> &collectible) {
                       if (playerBounds.findIntersection(collectible->getBounds())
                               .has_value()) {
                         collectible->onCollect(score, hearts, kMaxHearts);
                         return true;
                       }
                       return false;
                     }),
      collectibles.end());

  if (goal.isActive() &&
      playerBounds.findIntersection(goal.getBounds()).has_value()) {
    state = State::Victory;
  }
}

void Game::drawBackground() {
  const auto textureSize = backgroundTexture.getSize();
  if (textureSize.x == 0 || textureSize.y == 0) {
    sf::RectangleShape fallback(
        {static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight)});
    fallback.setFillColor(sf::Color(215, 187, 131));
    window.draw(fallback);
    return;
  }

  const float scale = std::max(
      static_cast<float>(kWindowWidth) / static_cast<float>(textureSize.x),
      static_cast<float>(kWindowHeight) / static_cast<float>(textureSize.y));
  const float scaledWidth = static_cast<float>(textureSize.x) * scale;
  const float scaledHeight = static_cast<float>(textureSize.y) * scale;
  const float y = (static_cast<float>(kWindowHeight) - scaledHeight) * 0.5f;

  backgroundSprite.setScale({scale, scale});
  backgroundSprite.setPosition({-backgroundOffset, y});
  window.draw(backgroundSprite);

  backgroundSprite.setPosition({-backgroundOffset + scaledWidth, y});
  window.draw(backgroundSprite);
}

void Game::drawGround() {
  sf::RectangleShape sand({static_cast<float>(kWindowWidth),
                           static_cast<float>(kWindowHeight) - kGroundY});
  sand.setPosition({0.f, kGroundY});
  sand.setFillColor(sf::Color(177, 136, 77));
  window.draw(sand);

  sf::RectangleShape road({static_cast<float>(kWindowWidth), 70.f});
  road.setPosition({0.f, kGroundY - 10.f});
  road.setFillColor(sf::Color(95, 82, 70, 180));
  window.draw(road);
}

void Game::pruneEntities() {
  obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                                 [](const std::unique_ptr<Obstacle> &obstacle) {
                                   return obstacle->isOffscreen();
                                 }),
                  obstacles.end());

  collectibles.erase(
      std::remove_if(collectibles.begin(), collectibles.end(),
                     [](const std::unique_ptr<Collectible> &collectible) {
                       return collectible->isOffscreen();
                     }),
      collectibles.end());
}

float Game::randomRange(float minValue, float maxValue) {
  std::uniform_real_distribution<float> distribution(minValue, maxValue);
  return distribution(rng);
}
