#include "Game.h"
#include "Constants.h"
#include "Utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>

static sf::Texture& getBgTex() {
    static sf::Texture t = loadTexture("assets/background.jpg");
    t.setRepeated(true);
    return t;
}
static sf::Texture& getPalTex() { static sf::Texture t = loadTexture("assets/palace.png"); return t; }
static sf::Texture& getVicTex() { static sf::Texture t = loadTexture("assets/victory_background.jpg"); return t; }
static sf::Texture& getDefTex() { static sf::Texture t = loadTexture("assets/defeat_background.jpg"); return t; }

Game::Game() : window(
                   sf::VideoMode({static_cast<unsigned int>(WINDOW_WIDTH), static_cast<unsigned int>(WINDOW_HEIGHT)}),
                   "Mini Jeu SFML"),
               camera(sf::FloatRect({0.f, 0.f}, {static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)})),
               backgroundSprite(getBgTex()),
               palaceSprite(getPalTex()),
               font(loadFont("assets/GROBOLD.ttf")),
               timerText(font, ""),
               distance(font),
               distanceText(font, ""),
               endMessage(font, ""),
               victorySprite(getVicTex()),
               defeatSprite(getDefTex()),
               gameOver(false),
               wonLevel(false),
               currentLevel(1),
               maxLevel(4),
               menuIndex(0),
               obstacleSpawnRate(2),
               playerSpeed(PLAYER_SPEED),
               levelTimeLimit(GAME_TIME_LIMIT),
                timeRemaining(GAME_TIME_LIMIT),
                distanceRemaining(BASE_PALACE_DISTANCE), lastObstacleSpawnX(0.f), OBSTACLE_SPACING(300.f) {
    srand(time(0));

    window.setFramerateLimit(90);

    sf::Vector2u bgSize = getBgTex().getSize();
    backgroundSprite.setTextureRect(
        sf::IntRect({0, 0}, {static_cast<int>(bgSize.x * 1000), static_cast<int>(bgSize.y)}));
    float bgScale = static_cast<float>(WINDOW_HEIGHT) / static_cast<float>(bgSize.y != 0 ? bgSize.y : 1);
    backgroundSprite.setScale({bgScale, bgScale});

    palaceSprite.setScale({0.5f, 0.5f});
    palaceSprite.setPosition({100.f + BASE_PALACE_DISTANCE, static_cast<float>(WINDOW_HEIGHT) - 400.f});

    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition({20.f, 50.f});
    timerText.setString("Temps : " + std::to_string(timeRemaining) + "s");

    distanceText.setCharacterSize(20);
    distanceText.setFillColor(sf::Color::White);
    distanceText.setPosition({static_cast<float>(WINDOW_WIDTH) - 220.f, 50.f});
    distanceText.setString("Distance: 0m");

    endMessage.setCharacterSize(36);
    endMessage.setFillColor(sf::Color::Yellow);
    endMessage.setPosition({
        static_cast<float>(WINDOW_WIDTH) / 2.f - 235.f,
        static_cast<float>(WINDOW_HEIGHT) / 2.f - 245.f
    });

    sf::Vector2u vicSize = getVicTex().getSize();
    victorySprite.setScale({
        static_cast<float>(WINDOW_WIDTH) / static_cast<float>(vicSize.x),
        static_cast<float>(WINDOW_HEIGHT) / static_cast<float>(vicSize.y)
    });

    sf::Vector2u defSize = getDefTex().getSize();
    defeatSprite.setScale({
        static_cast<float>(WINDOW_WIDTH) / static_cast<float>(defSize.x),
        static_cast<float>(WINDOW_HEIGHT) / static_cast<float>(defSize.y)
    });

    initialDistance = BASE_PALACE_DISTANCE;

    initEndMenu();
}

void Game::initEndMenu() {
    menuOptions.clear();
    std::vector<std::string> labels;
    if (wonLevel) {
        labels = {"Rejouer", "Niveau Suivant", "Quitter"};
    } else {
        labels = {"Rejouer", "Quitter"};
    }

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text text(font, labels[i], 30);
        text.setPosition({
            static_cast<float>(WINDOW_WIDTH) / 2.f - 100.f,
            static_cast<float>(WINDOW_HEIGHT) / 2.f + 20.f + (i * 45.f)
        });
        text.setFillColor(i == static_cast<size_t>(menuIndex) ? sf::Color::Yellow : sf::Color::White);
        menuOptions.push_back(text);
    }
}

void Game::resetLevel() {
    gameOver = false;
    wonLevel = false;
    timeRemaining = GAME_TIME_LIMIT;
    initialDistance = BASE_PALACE_DISTANCE + (currentLevel * 1000.0f);
    distanceRemaining = initialDistance;
    obstacleSpawnRate = 2.0f + (currentLevel * 0.5f);
    palaceSprite.setPosition({100.f + initialDistance,static_cast<float>(WINDOW_HEIGHT) - 400.f});

    player.resetPosition();
    player.resetHealth();
    obstacles.clear();
    lastObstacleSpawnX = 0.f;
    clock.restart();
    menuIndex = 0;
    camera.setCenter({300.f, static_cast<float>(WINDOW_HEIGHT) / 2.f});
    backgroundSprite.setPosition({0.f, 0.f});

    timerText.setString("Temps : " + std::to_string(timeRemaining) + "s");
    distanceText.setString("Distance: " + std::to_string(static_cast<int>(distanceRemaining)) + "m");
}

void Game::run() {
    clock.restart();
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    while (auto eventOpt = window.pollEvent()) {
        if (eventOpt->is<sf::Event::Closed>()) {
            window.close();
        }

        if (gameOver) {
            if (const auto* keyPressed = eventOpt->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Up) {
                    menuOptions[menuIndex].setFillColor(sf::Color::White);
                    menuIndex = (menuIndex - 1 + menuOptions.size()) % menuOptions.size();
                    menuOptions[menuIndex].setFillColor(sf::Color::Yellow);
                } else if (keyPressed->code == sf::Keyboard::Key::Down) {
                    menuOptions[menuIndex].setFillColor(sf::Color::White);
                    menuIndex = (menuIndex + 1) % menuOptions.size();
                    menuOptions[menuIndex].setFillColor(sf::Color::Yellow);
                } else if (keyPressed->code == sf::Keyboard::Key::Enter) {
                    if (wonLevel) {
                        if (menuIndex == 0) resetLevel();
                        else if (menuIndex == 1 && currentLevel < maxLevel) { currentLevel++; resetLevel(); }
                        else window.close();
                    } else {
                        if (menuIndex == 0) resetLevel();
                        else window.close();
                    }
                }
            }
        }
    }

    if (!gameOver) {
        player.handleInput();
    }
}

void Game::update() {
    if (gameOver) return;
    player.update();

    if (clock.getElapsedTime().asSeconds() >= 1.0f) {
        if (timeRemaining > 0) timeRemaining--;
        clock.restart();
        timerText.setString("Temps : " + std::to_string(timeRemaining) + "s");
    }

    if (player.getBounds().position.x - lastObstacleSpawnX > OBSTACLE_SPACING) {
        spawnObstacle();
        lastObstacleSpawnX = player.getBounds().position.x;
    }

    for (auto it = obstacles.begin(); it != obstacles.end(); ) {
        (*it)->update();

        if (auto intersection = player.getBounds().findIntersection((*it)->getBounds())) {
            player.takeDamage();
            it = obstacles.erase(it);
            continue;
        }

        if ((*it)->getBounds().position.x + (*it)->getBounds().size.x < 0) {
            it = obstacles.erase(it);
        } else {
            ++it;
        }
    }

    // (No separate entities vector any more — clouds/trees removed; obstacles are polymorphic Entities)

    camera.setCenter({player.getBounds().position.x + 200.f, static_cast<float>(WINDOW_HEIGHT) / 2.f});
    backgroundSprite.setPosition({player.getBounds().position.x * 0.1f, 0.f});

    distanceRemaining = palaceSprite.getPosition().x - player.getBounds().position.x;
    distanceText.setString("Distance: " + std::to_string(static_cast<int>(std::max(0.f, distanceRemaining))) + "m");

    if (distanceRemaining <= 0 || timeRemaining <= 0 || !player.isAlive()) {
        gameOver = true;
        wonLevel = (distanceRemaining <= 0 && player.isAlive());
        if (wonLevel) {
            endMessage.setString("FELICITATIONS PRINCESSE!\nVous avez conquis le niveau " + std::to_string(currentLevel));
        } else {
            endMessage.setString("DESOLE PRINCESS ...\nVotre aventure s'arrete ici.");
        }
        initEndMenu();
    }
}

void Game::spawnObstacle() {
    // Petite chance de spawn d'une entité "arbre" ou "nuage" en plus des obstacles existants
    int roll = rand() % 10; // 0..9
    float xPos = player.getBounds().position.x + WINDOW_WIDTH + MIN_OBSTACLE_SPACING;

    // No tree/cloud entities: spawn only real obstacles (but keep polymorphic storage)

    // Sinon, obstacle existant (ne pas toucher aux autres types)
    std::string types[] = {"butterfly", "bird", "stone", "log"};
    std::string type = types[rand() % 4];
    float yPos;

    if (type == "stone" || type == "log") {
        yPos = static_cast<float>(WINDOW_HEIGHT) - 100.f;
    } else {
        yPos = static_cast<float>((WINDOW_HEIGHT / 2 - 50)) + 80.f;
    }

    // create a polymorphic Obstacle instance
    obstacles.emplace_back(std::make_unique<Obstacle>(type, xPos, yPos));
}

void Game::render() {
    window.clear();
    if (gameOver) {
        window.setView(window.getDefaultView());
        if (!player.isAlive() || timeRemaining <= 0) {
            window.draw(defeatSprite);
        } else {
            window.draw(victorySprite);
        }
        window.draw(endMessage);
        for (auto& opt : menuOptions) window.draw(opt);
    } else {
        window.setView(camera);
        window.draw(backgroundSprite);
        window.draw(palaceSprite);
        player.draw(window);
        for (auto& obs : obstacles) obs->draw(window);

        window.setView(window.getDefaultView());
        window.draw(timerText);
        window.draw(distanceText);
        player.drawUI(window);
    }
    window.display();
}