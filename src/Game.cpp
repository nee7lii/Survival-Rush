#include "../include/Game.h"
#include "../include/AssetLoader.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <algorithm>
#include <cstdlib>
#include <ctime>

Game::Game()
    : window(sf::VideoMode(kWindowWidth, kWindowHeight), "Survival Rush"),
      frameClock(),
      backgroundTexture(),
      backgroundSprite(),
      backgroundSprite2(),
      groundSprite(),
      player(),
      hud(),
      menu(),
      goal(),
      obstacles(),
      collectibles(),
      state(StartMenu),
      elapsedTime(0.f),
      obstacleSpawnTimer(0.f),
      collectibleSpawnTimer(0.f),
      nextObstacleSpawn(1.4f),
      nextCollectibleSpawn(1.1f),
      backgroundOffset(0.f),
      backgroundX1(0.f),
      backgroundX2(0.f),
      hearts(kMaxHearts),
      score(0),
      goalSpawned(false),
      crouchHeld(false) {
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    window.setFramerateLimit(60);
    AssetLoader::loadTexture(backgroundTexture, "assets/images/road.png", "../assets/images/road.png");
    backgroundSprite.setTexture(backgroundTexture, true);
    backgroundSprite2.setTexture(backgroundTexture, true);
    groundSprite.setTexture(backgroundTexture, true);
    resetRun();
}

Game::~Game() {
    clearObstacles();
    clearCollectibles();
}

void Game::start() {
    while (window.isOpen()) {
        processEvents();

        float deltaTime = frameClock.restart().asSeconds();
        if (deltaTime > 0.033f) {
            deltaTime = 0.033f;
        }

        if (state == Running) {
            update(deltaTime);
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event;

    /*
        CM1/TP SFML : boucle d'événements avec sf::Event.
        Ici on ajoute aussi la gestion des clics souris pour le menu.
    */
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            if (state == StartMenu) {
                if (menu.isPlayClicked(window, mousePosition)) {
                    startRun();
                } else if (menu.isAboutClicked(window, mousePosition)) {
                    state = AboutMenu;
                } else if (menu.isExitClicked(window, mousePosition)) {
                    window.close();
                }
            } else if (state == AboutMenu) {
                if (menu.isBackClicked(window, mousePosition)) {
                    state = StartMenu;
                }
            } else if (state == GameOver || state == Victory) {
                if (menu.isEndRestartClicked(window, mousePosition)) {
                    startRun();
                } else if (menu.isEndMenuClicked(window, mousePosition)) {
                    window.close();
                }
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (state == AboutMenu) {
                    state = StartMenu;
                } else {
                    window.close();
                }
            } else if (event.key.code == sf::Keyboard::Enter) {
                /*
                    Enter est conservée pour rejouer après victoire/défaite.
                    Le lancement depuis le menu principal se fait désormais au clic.
                */
                if (state == Victory || state == GameOver) {
                    startRun();
                }
            } else if ((event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up) && state == Running) {
                player.jump();
            } else if (state == Running && isCrouchKey(event.key.code)) {
                crouchHeld = true;
                player.setCrouching(true);
            }
        }

        if (event.type == sf::Event::KeyReleased) {
            if (isCrouchKey(event.key.code)) {
                crouchHeld = false;
                player.setCrouching(false);
            }
        }
    }
}

void Game::update(float deltaTime) {
    player.setCrouching(crouchHeld);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    if (textureSize.x > 0 && textureSize.y > 0) {
        float scaleX = static_cast<float>(kWindowWidth) / textureSize.x;
        float scaleY = static_cast<float>(kWindowHeight) / textureSize.y;
        float scale = std::max(scaleX, scaleY);
        float tileWidth = textureSize.x * scale;

        if (backgroundX1 == 0.f && backgroundX2 == 0.f) {
            backgroundX1 = 0.f;
            backgroundX2 = tileWidth;
        }

        backgroundX1 -= kWorldSpeed * deltaTime;
        backgroundX2 -= kWorldSpeed * deltaTime;

        if (backgroundX1 + tileWidth <= 0.f) {
            backgroundX1 = backgroundX2 + tileWidth;
        }
        if (backgroundX2 + tileWidth <= 0.f) {
            backgroundX2 = backgroundX1 + tileWidth;
        }

        backgroundOffset += kWorldSpeed * deltaTime;
        if (backgroundOffset >= tileWidth) {
            backgroundOffset -= tileWidth;
        }
    }

    updateGameplay(deltaTime);
}

bool Game::isCrouchKey(sf::Keyboard::Key key) const {
    return key == sf::Keyboard::Down ||
           key == sf::Keyboard::S ||
           key == sf::Keyboard::LShift ||
           key == sf::Keyboard::RShift;
}

void Game::render() {
    if (state == StartMenu) {
        window.clear(sf::Color::Black);
        menu.drawMainMenu(window);
        window.display();
        return;
    }

    if (state == AboutMenu) {
        window.clear(sf::Color::Black);
        menu.drawAboutScreen(window);
        window.display();
        return;
    }

    if (state == Victory) {
        window.clear(sf::Color::Black);
        menu.drawEndScreen(window, Menu::Win, score);
        window.display();
        return;
    }

    if (state == GameOver) {
        window.clear(sf::Color::Black);
        menu.drawEndScreen(window, Menu::GameOver, score);
        window.display();
        return;
    }

    window.clear(sf::Color(225, 206, 162));

    drawBackground();
    drawGround();
    goal.draw(window);

    for (unsigned int i = 0; i < collectibles.size(); i++) {
        collectibles[i]->draw(window);
    }

    for (unsigned int i = 0; i < obstacles.size(); i++) {
        obstacles[i]->draw(window);
    }

    player.draw(window);

    float timeLeft = kRunDuration - elapsedTime;
    if (timeLeft < 0.f) {
        timeLeft = 0.f;
    }

    hud.draw(window, hearts, score, timeLeft, elapsedTime / kRunDuration);

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
    backgroundX1 = 0.f;
    backgroundX2 = 0.f;
    goalSpawned = false;

    clearObstacles();
    clearCollectibles();

    goal.reset();
    player.reset(sf::Vector2f(190.f, kGroundY));
    frameClock.restart();
}

void Game::startRun() {
    resetRun();
    state = Running;
}

void Game::spawnObstacle() {
    float roll = randomRange(0.f, 1.f);
    float x = kWindowWidth + randomRange(0.f, 120.f);

    if (roll < 0.4f) {
        obstacles.push_back(new BarbedWire(x, kGroundY, kWorldSpeed));
    } else if (roll < 0.75f) {
        obstacles.push_back(new Landmine(x, kGroundY, kWorldSpeed));
    } else {
        obstacles.push_back(new Quadcopter(x, kWorldSpeed));
    }
}

void Game::spawnCollectible() {
    bool spawnAidKit = randomRange(0.f, 1.f) < 0.18f;
    float x = kWindowWidth + randomRange(0.f, 120.f);

    if (spawnAidKit) {
        collectibles.push_back(new FirstAidKit(sf::Vector2f(x, kGroundY - 68.f), kWorldSpeed));
        return;
    }

    bool airCoin = randomRange(0.f, 1.f) < 0.45f;
    float y;
    if (airCoin) {
        y = 355.f;
    } else {
        y = kGroundY - 48.f;
    }

    collectibles.push_back(new Coin(sf::Vector2f(x, y), kWorldSpeed));
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

    for (unsigned int i = 0; i < obstacles.size(); i++) {
        obstacles[i]->update(deltaTime);
    }

    for (unsigned int i = 0; i < collectibles.size(); i++) {
        collectibles[i]->update(deltaTime);
    }

    goal.update(deltaTime);
    handleCollisions();
    pruneEntities();

    if (state == Running && elapsedTime >= kRunDuration) {
        state = GameOver;
    }
}

void Game::handleCollisions() {
    sf::FloatRect playerBounds = player.getBounds();

    for (int i = static_cast<int>(obstacles.size()) - 1; i >= 0; i--) {
        if (playerBounds.intersects(obstacles[i]->getBounds())) {
            delete obstacles[i];
            obstacles.erase(obstacles.begin() + i);

            player.triggerHit();
            hearts--;
            if (hearts <= 0) {
                hearts = 0;
                state = GameOver;
            }
        }
    }

    for (int i = static_cast<int>(collectibles.size()) - 1; i >= 0; i--) {
        if (playerBounds.intersects(collectibles[i]->getBounds())) {
            collectibles[i]->onCollect(score, hearts, kMaxHearts);
            delete collectibles[i];
            collectibles.erase(collectibles.begin() + i);
        }
    }

    if (goal.isActive() && playerBounds.intersects(goal.getBounds())) {
        state = Victory;
    }
}

void Game::drawBackground() {
    sf::Vector2u textureSize = backgroundTexture.getSize();
    if (textureSize.x == 0 || textureSize.y == 0) {
        sf::RectangleShape fallback(sf::Vector2f(kWindowWidth, kWindowHeight));
        fallback.setFillColor(sf::Color(215, 187, 131));
        window.draw(fallback);
        return;
    }

    float scaleX = static_cast<float>(kWindowWidth) / textureSize.x;
    float scaleY = static_cast<float>(kWindowHeight) / textureSize.y;
    float scale = std::max(scaleX, scaleY);
    float scaledWidth = textureSize.x * scale;
    float scaledHeight = textureSize.y * scale;
    float y = (kWindowHeight - scaledHeight) * 0.5f;

    backgroundSprite.setScale(scale, scale);
    backgroundSprite2.setScale(scale, scale);

    if (backgroundX1 == 0.f && backgroundX2 == 0.f) {
        backgroundX1 = 0.f;
        backgroundX2 = scaledWidth;
    }

    if (backgroundX1 > backgroundX2) {
        std::swap(backgroundX1, backgroundX2);
    }

    backgroundSprite.setPosition(backgroundX1, y);
    window.draw(backgroundSprite);

    backgroundSprite2.setPosition(backgroundX2, y);
    window.draw(backgroundSprite2);
}

void Game::drawGround() {
    sf::Vector2u textureSize = backgroundTexture.getSize();
    if (textureSize.x == 0 || textureSize.y == 0) {
        sf::RectangleShape fallback(sf::Vector2f(kWindowWidth, kWindowHeight - kGroundY));
        fallback.setPosition(0.f, kGroundY);
        fallback.setFillColor(sf::Color(177, 136, 77));
        window.draw(fallback);
        return;
    }

    const int sliceHeight = std::min<int>(160, static_cast<int>(textureSize.y));
    const float targetHeight = (kWindowHeight - kGroundY) + 24.f;
    const float targetY = kGroundY - 24.f;
    const float scale = targetHeight / static_cast<float>(sliceHeight);
    const float tileWidth = textureSize.x * scale;
    const int sliceTop = static_cast<int>(textureSize.y) - sliceHeight;

    groundSprite.setTextureRect(sf::IntRect(0, sliceTop, static_cast<int>(textureSize.x), sliceHeight));
    groundSprite.setScale(scale, scale);

    if (backgroundX1 == 0.f && backgroundX2 == 0.f) {
        backgroundX1 = 0.f;
        backgroundX2 = tileWidth;
    }

    float groundX1 = backgroundX1;
    float groundX2 = backgroundX2;
    if (groundX1 > groundX2) {
        std::swap(groundX1, groundX2);
    }

    groundSprite.setPosition(groundX1, targetY);
    window.draw(groundSprite);

    groundSprite.setPosition(groundX2, targetY);
    window.draw(groundSprite);
}

void Game::pruneEntities() {
    for (int i = static_cast<int>(obstacles.size()) - 1; i >= 0; i--) {
        if (obstacles[i]->isOffscreen()) {
            delete obstacles[i];
            obstacles.erase(obstacles.begin() + i);
        }
    }

    for (int i = static_cast<int>(collectibles.size()) - 1; i >= 0; i--) {
        if (collectibles[i]->isOffscreen()) {
            delete collectibles[i];
            collectibles.erase(collectibles.begin() + i);
        }
    }
}

void Game::clearObstacles() {
    for (unsigned int i = 0; i < obstacles.size(); i++) {
        delete obstacles[i];
    }
    obstacles.clear();
}

void Game::clearCollectibles() {
    for (unsigned int i = 0; i < collectibles.size(); i++) {
        delete collectibles[i];
    }
    collectibles.clear();
}

float Game::randomRange(float minValue, float maxValue) const {
    float ratio = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    return minValue + ratio * (maxValue - minValue);
}
