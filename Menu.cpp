#include "Menu.h"
#include "Constants.h"
#include "Utils.h"

// Helper pour récupérer la texture statique avant l'initialisation du Sprite
static sf::Texture& getMenuTexture() {
    static sf::Texture texture = loadTexture("assets/background_menu.jpg");
    return texture;
}

Menu::Menu(const float width, const float height) : menuSprite(getMenuTexture()) {
    // Adapter l'image de fond à la taille de la fenêtre
    sf::Vector2u textureSize = getMenuTexture().getSize();
    menuSprite.setScale({width / static_cast<float>(textureSize.x), height / static_cast<float>(textureSize.y)});

    font = loadFont("assets/GROBOLD.ttf");

    std::vector<std::string> labels = {"Jouer", "A propos", "Quitter"};
    selectedIndex = 0;

    for (size_t i = 0; i < labels.size(); i++) {
        sf::Text text(font, labels[i], 40);
        text.setFillColor(i == 0 ? sf::Color::Black : sf::Color::Blue);
        float x = width / 2.0f - 100.0f;
        float y = (height / static_cast<float>(labels.size() + 1)) * static_cast<float>(i + 1);
        text.setPosition({x, y});
        options.push_back(text);
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(menuSprite);
    for (auto& option : options) {
        window.draw(option);
    }
}

void Menu::moveUp() {
    if (selectedIndex - 1 >= 0) {
        options[selectedIndex].setFillColor(sf::Color::Blue);
        selectedIndex--;
        options[selectedIndex].setFillColor(sf::Color::Black);
    }
}

void Menu::moveDown() {
    if (selectedIndex + 1 < options.size()) {
        options[selectedIndex].setFillColor(sf::Color::Blue);
        selectedIndex++;
        options[selectedIndex].setFillColor(sf::Color::Black);
    }
}

int Menu::getSelectedIndex() {
    return selectedIndex;
}
