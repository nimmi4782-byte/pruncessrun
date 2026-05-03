#ifndef PRINCESSRUN_PLAYER_H
#define PRINCESSRUN_PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBar;
    sf::Clock invulnClock;
    bool invulnerable;
    float verticalVelocity;
    bool isJumping;
    bool isDucking;
    float groundY;
    int health;

public:
    Player();
    void handleInput();
    void setTexture(const sf::Texture& texture);
    void update();
    void draw(sf::RenderWindow& window);
    void drawUI(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    void takeDamage();
    bool isAlive();
    void resetHealth();
    void resetPosition(); // ← زيدات
};

#endif //PRINCESSRUN_PLAYER_H