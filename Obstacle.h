#ifndef PRINCESSRUN_OBSTACLE_H
#define PRINCESSRUN_OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "Entity.h"

class Obstacle : public Entity {
private:
    sf::Sprite sprite;

public:
    Obstacle(std::string type, float x, float y);
    void update() override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() override;
};

#endif //PRINCESSRUN_OBSTACLE_H
