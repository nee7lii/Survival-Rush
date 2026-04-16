#include "../include/Menu.h"
#include "../include/AssetLoader.h"

#include <SFML/Graphics/Text.hpp>

Menu::Menu()
    : font(),
      fontLoaded(false),
      menuTexture(),
      aboutTexture(),
      winTexture(),
      loseTexture(),
      menuImageLoaded(false),
      aboutImageLoaded(false),
      winImageLoaded(false),
      loseImageLoaded(false) {
    fontLoaded = AssetLoader::loadFont(font, "assets/fonts/Arial.ttf", "../assets/fonts/Arial.ttf");
    menuImageLoaded = AssetLoader::loadTexture(menuTexture, "assets/images/menu.png", "../assets/images/menu.png");
    aboutImageLoaded = AssetLoader::loadTexture(aboutTexture, "assets/images/about.png", "../assets/images/about.png");
    winImageLoaded = AssetLoader::loadTexture(winTexture, "assets/images/win.png", "../assets/images/win.png");
    loseImageLoaded = AssetLoader::loadTexture(loseTexture, "assets/images/lose.png", "../assets/images/lose.png");
}

void Menu::drawScaledBackground(sf::RenderWindow& window, const sf::Texture& texture) const {
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Vector2u textureSize = texture.getSize();
    if (textureSize.x == 0 || textureSize.y == 0) {
        return;
    }

    float scaleX = static_cast<float>(window.getSize().x) / textureSize.x;
    float scaleY = static_cast<float>(window.getSize().y) / textureSize.y;
    float scale = std::max(scaleX, scaleY);
    float scaledWidth = textureSize.x * scale;
    float scaledHeight = textureSize.y * scale;

    sprite.setScale(scale, scale);
    sprite.setPosition((window.getSize().x - scaledWidth) * 0.5f, (window.getSize().y - scaledHeight) * 0.5f);
    window.draw(sprite);
}

void Menu::drawMainMenu(sf::RenderWindow& window) const {
    if (menuImageLoaded) {
        drawScaledBackground(window, menuTexture);
    } else if (fontLoaded) {
        drawCenteredText(window, "SURVIVAL RUSH", 56, 140.f, sf::Color::White);
        drawCenteredText(window, "PLAY", 36, 320.f, sf::Color::White);
        drawCenteredText(window, "ABOUT", 36, 430.f, sf::Color::White);
        drawCenteredText(window, "EXIT", 36, 540.f, sf::Color::White);
    }
}

void Menu::drawAboutScreen(sf::RenderWindow& window) const {
    if (aboutImageLoaded) {
        drawScaledBackground(window, aboutTexture);
    } else if (fontLoaded) {
        drawCenteredText(window, "ABOUT", 54, 110.f, sf::Color::White);
        drawCenteredText(window, "BACK", 36, 610.f, sf::Color::White);
    }
}

void Menu::drawEndScreen(sf::RenderWindow& window, Screen screen, int score) const {
    (void)score;

    if (screen == Win && winImageLoaded) {
        drawScaledBackground(window, winTexture);
        return;
    }

    if (screen == GameOver && loseImageLoaded) {
        drawScaledBackground(window, loseTexture);
        return;
    }

    if (!fontLoaded) {
        return;
    }

    drawCenteredText(window, "RESTART", 34, 470.f, sf::Color::White);
    drawCenteredText(window, "EXIT", 34, 560.f, sf::Color::White);
}

bool Menu::isPlayClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const {
    return isPointInside(playButtonRect(window), mousePosition);
}

bool Menu::isAboutClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const {
    return isPointInside(aboutButtonRect(window), mousePosition);
}

bool Menu::isExitClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const {
    return isPointInside(exitButtonRect(window), mousePosition);
}

bool Menu::isBackClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const {
    return isPointInside(backButtonRect(window), mousePosition);
}

void Menu::drawCenteredText(sf::RenderWindow& window, const std::string& text, unsigned int size, float y, const sf::Color& color) const {
    sf::Text drawable(text, font, size);
    drawable.setFillColor(color);
    drawable.setStyle(sf::Text::Bold);
    drawable.setOutlineThickness(2.f);
    drawable.setOutlineColor(sf::Color(30, 20, 10));

    sf::FloatRect bounds = drawable.getLocalBounds();
    drawable.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    drawable.setPosition(window.getSize().x / 2.f, y);
    window.draw(drawable);
}

sf::FloatRect Menu::imageRectToWindow(const sf::RenderWindow& window, const sf::FloatRect& imageRect) const {
    const float sourceWidth = 2752.f;
    const float sourceHeight = 1536.f;
    float scaleX = static_cast<float>(window.getSize().x) / sourceWidth;
    float scaleY = static_cast<float>(window.getSize().y) / sourceHeight;
    float scale = std::max(scaleX, scaleY);
    float scaledWidth = sourceWidth * scale;
    float scaledHeight = sourceHeight * scale;
    float offsetX = (window.getSize().x - scaledWidth) * 0.5f;
    float offsetY = (window.getSize().y - scaledHeight) * 0.5f;

    return sf::FloatRect(
        offsetX + imageRect.left * scale,
        offsetY + imageRect.top * scale,
        imageRect.width * scale,
        imageRect.height * scale
    );
}

sf::FloatRect Menu::playButtonRect(const sf::RenderWindow& window) const {
    return imageRectToWindow(window, sf::FloatRect(1045.f, 586.f, 685.f, 167.f));
}

sf::FloatRect Menu::aboutButtonRect(const sf::RenderWindow& window) const {
    return imageRectToWindow(window, sf::FloatRect(1045.f, 855.f, 685.f, 167.f));
}

sf::FloatRect Menu::exitButtonRect(const sf::RenderWindow& window) const {
    return imageRectToWindow(window, sf::FloatRect(1045.f, 1127.f, 685.f, 167.f));
}

sf::FloatRect Menu::backButtonRect(const sf::RenderWindow& window) const {
    return imageRectToWindow(window, sf::FloatRect(1115.f, 1340.f, 585.f, 160.f));
}

sf::FloatRect Menu::restartButtonRect(const sf::RenderWindow& window) const {
    if (winImageLoaded || loseImageLoaded) {
        return imageRectToWindow(window, sf::FloatRect(1035.f, 590.f, 705.f, 168.f));
    }
    return sf::FloatRect(470.f, 430.f, 340.f, 72.f);
}

sf::FloatRect Menu::endExitButtonRect(const sf::RenderWindow& window) const {
    if (winImageLoaded || loseImageLoaded) {
        return imageRectToWindow(window, sf::FloatRect(1070.f, 885.f, 615.f, 168.f));
    }
    return sf::FloatRect(520.f, 520.f, 240.f, 72.f);
}

bool Menu::isPointInside(const sf::FloatRect& area, const sf::Vector2i& mousePosition) const {
    return area.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}

bool Menu::isEndRestartClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const {
    return isPointInside(restartButtonRect(window), mousePosition);
}

bool Menu::isEndMenuClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const {
    return isPointInside(endExitButtonRect(window), mousePosition);
}
