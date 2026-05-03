#ifndef PRINCESSRUN_ENTITY_H
#define PRINCESSRUN_ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual ~Entity() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getBounds() = 0;
    // Par défaut les entités sont collidables. Surchargez pour rendre non-collidable (ex: nuage)
    virtual bool isCollidable() const { return true; }
};

#endif // PRINCESSRUN_ENTITY_H
