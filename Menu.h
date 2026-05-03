#ifndef PRINCESSRUN_MENU_H
#define PRINCESSRUN_MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <string>

class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> options;
    int selectedIndex;

    sf::Sprite menuSprite;

public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex();
};

#endif //PRINCESSRUN_MENU_H
