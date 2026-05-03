#include "Game.h"
#include "Menu.h"
#include "Constants.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
    Menu menu(WINDOW_WIDTH, WINDOW_HEIGHT);

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Princess Run");

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Up) {
                    menu.moveUp();
                }
                if (keyPressed->code == sf::Keyboard::Key::Down) {
                    menu.moveDown();
                }
                if (keyPressed->code == sf::Keyboard::Key::Enter) {
                    int choice = menu.getSelectedIndex();
                    if (choice == 0) { // Jouer
                        window.close(); // Ferme la fenêtre du menu avant de lancer le jeu
                        Game game;
                        game.run();
                        window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Menu Principal");
                    } else if (choice == 1) { // A propos
                        sf::RenderWindow about(sf::VideoMode({700, 500}), "A propos");
                        
                        sf::Texture aboutTexture = loadTexture("assets/bcg.jpg");
                        sf::Sprite aboutSprite(aboutTexture);
                        sf::Vector2u texSize = aboutTexture.getSize();
                        aboutSprite.setScale({700.f / static_cast<float>(texSize.x), 700.f / static_cast<float>(texSize.y)});

                        sf::Font font = loadFont("assets/GROBOLD.ttf");
                        sf::Text text(font,"                                     PrincessRun\n\n\n"
                            "Princess Run est un jeu de cachette 2D developpe en C++\n\n"
                            "Developpe par : \n\n"
                            "                         NAJWA IMMI\n\n"
                            "                         GHIZLANE HMAMA\n\n"
                            "Objectif : atteindre le palais en evitant des obstacles.\n\n"
                            "I y a 4 niveaux progressifs et 3 vies disponibles\n\n"
                            "Sauter : Fleche haut \n\n"
                            "Se baisser : Fleche bas ", 23);
                        text.setPosition({30, 50});
                        text.setFillColor(sf::Color::Black);

                        while (about.isOpen()) {
                            while (const std::optional e = about.pollEvent()) {
                                if (e->is<sf::Event::Closed>())
                                    about.close();
                            }
                            about.clear();
                            about.draw(aboutSprite);
                            about.draw(text);
                            about.display();
                        }
                    } else if (choice == 2) { // Quitter
                        window.close();
                    }
                }
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}
