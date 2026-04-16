#include "../include/HUD.h"
#include "../include/AssetLoader.h"

#include <iomanip>
#include <sstream>
#include <string>

HUD::HUD()
    : font(),
      fontLoaded(false),
      heartFullTexture(),
      heartEmptyTexture(),
      heartFullTextureLoaded(false),
      heartEmptyTextureLoaded(false)
{
    fontLoaded = AssetLoader::loadFont(font, "assets/fonts/Arial.ttf", "../assets/fonts/Arial.ttf");
    heartFullTextureLoaded = AssetLoader::loadTexture(heartFullTexture, "assets/images/heart_full.png", "../assets/images/heart_full.png");
    heartEmptyTextureLoaded = AssetLoader::loadTexture(heartEmptyTexture, "assets/images/heart_empty.png", "../assets/images/heart_empty.png");
}

void HUD::draw(sf::RenderWindow& window, int hearts, int score, float timeLeft, float progress) const
{
    (void)progress;

    if (hearts < 0) {
        hearts = 0;
    }
    if (hearts > 3) {
        hearts = 3;
    }

    const sf::Vector2f heartBase(30.f, 24.f);
    const sf::Vector2f heartSize(54.f, 54.f);
    const float heartSpacing = 64.f;

    for (int i = 0; i < 3; ++i) {
        sf::Sprite heartSprite;
        if (i < hearts && heartFullTextureLoaded) {
            heartSprite.setTexture(heartFullTexture);
        } else if (heartEmptyTextureLoaded) {
            heartSprite.setTexture(heartEmptyTexture);
        } else {
            continue;
        }

        heartSprite.setScale(heartSize.x / heartSprite.getTexture()->getSize().x,
                             heartSize.y / heartSprite.getTexture()->getSize().y);
        heartSprite.setPosition(heartBase.x + i * heartSpacing, heartBase.y);
        window.draw(heartSprite);
    }

    if (!fontLoaded) {
        return;
    }

    if (timeLeft < 0.f) {
        timeLeft = 0.f;
    }

    std::ostringstream timerStream;
    timerStream << std::fixed << std::setprecision(1) << timeLeft;

    sf::Text timerText("Time: " + timerStream.str() + "s", font, 28);
    timerText.setPosition(920.f, 24.f);
    timerText.setFillColor(sf::Color::White);
    timerText.setOutlineThickness(2.f);
    timerText.setOutlineColor(sf::Color(32, 24, 16));
    window.draw(timerText);

    sf::Text scoreText("Score: " + std::to_string(score), font, 28);
    scoreText.setPosition(920.f, 60.f);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineThickness(2.f);
    scoreText.setOutlineColor(sf::Color(32, 24, 16));
    window.draw(scoreText);
}
