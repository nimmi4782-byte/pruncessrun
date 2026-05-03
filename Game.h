#ifndef PRINCESSRUN_GAME_H
#define PRINCESSRUN_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Obstacle.h"
#include "Entity.h"
#include <vector>
#include <memory>

class Game {
private:
    sf::RenderWindow window;
    sf::View camera;
    Player player;
    // obstacles are stored polymorphically via Entity (concrete type: Obstacle)
    std::vector<std::unique_ptr<Entity>> obstacles;
    sf::Clock clock;
    int timeRemaining;
    float distanceRemaining;
    float lastObstacleSpawnX;
    float OBSTACLE_SPACING = 400.f;

    // Niveaux
    int currentLevel;
    int maxLevel;
    float obstacleSpawnRate;
    float playerSpeed;
    int levelTimeLimit;

    // Backgrounds
    sf::Sprite backgroundSprite;
    sf::Sprite palaceSprite;

    // Chrono
    sf::Font font;
    sf::Text timerText;
    sf::Text distance;
    sf::Text distanceText;
    float initialDistance;

    // Messages
    sf::Text endMessage;
    std::vector<sf::Text> menuOptions;
    int menuIndex;
    bool gameOver;
    bool wonLevel;

    // Victoire/Défaite backgrounds
    sf::Sprite victorySprite;
    sf::Sprite defeatSprite;

public:
    Game();
    void run();
    void handleEvents();
    void update();
    void render();
    void spawnObstacle();
    void resetLevel();
    void initEndMenu();
};

#endif //PRINCESSRUN_GAME_H

