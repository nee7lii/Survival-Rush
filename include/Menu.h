#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>

class Menu {
public:
    enum Screen {
        Win,
        GameOver
    };

private:
    sf::Font font;
    bool fontLoaded;

    sf::Texture menuTexture;
    sf::Texture aboutTexture;
    sf::Texture winTexture;
    sf::Texture loseTexture;
    bool menuImageLoaded;
    bool aboutImageLoaded;
    bool winImageLoaded;
    bool loseImageLoaded;

    void drawScaledBackground(sf::RenderWindow& window, const sf::Texture& texture) const;
    void drawCenteredText(sf::RenderWindow& window, const std::string& text, unsigned int size, float y, const sf::Color& color) const;
    sf::FloatRect imageRectToWindow(const sf::RenderWindow& window, const sf::FloatRect& imageRect) const;
    sf::FloatRect playButtonRect(const sf::RenderWindow& window) const;
    sf::FloatRect aboutButtonRect(const sf::RenderWindow& window) const;
    sf::FloatRect exitButtonRect(const sf::RenderWindow& window) const;
    sf::FloatRect backButtonRect(const sf::RenderWindow& window) const;
    sf::FloatRect restartButtonRect(const sf::RenderWindow& window) const;
    sf::FloatRect endExitButtonRect(const sf::RenderWindow& window) const;
    bool isPointInside(const sf::FloatRect& area, const sf::Vector2i& mousePosition) const;

public:
    Menu();

    /*
        Dessin des deux écrans principaux demandés :
        - menu principal avec PLAY / ABOUT / EXIT
        - écran ABOUT avec le bouton BACK
    */
    void drawMainMenu(sf::RenderWindow& window) const;
    void drawAboutScreen(sf::RenderWindow& window) const;

    /*
        Ecrans de fin de partie.
        On garde le fond du gameplay puis on affiche un overlay.
        Pour la défaite, on ajoute un vrai bouton cliquable.
    */
    void drawEndScreen(sf::RenderWindow& window, Screen screen, int score) const;

    /*
        Détection des clics sur les boutons dessinés dans les images.
        Les coordonnées sont définies dans le repère des images puis
        converties automatiquement à la taille de la fenêtre.
    */
    bool isPlayClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const;
    bool isAboutClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const;
    bool isExitClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const;
    bool isBackClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const;

    bool isEndRestartClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const;
    bool isEndMenuClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePosition) const;
};

#endif
