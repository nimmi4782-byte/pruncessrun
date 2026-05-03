#include "Obstacle.h"
#include "Constants.h"
#include "Utils.h"
#include <map>

// Helper pour gérer le cache de textures des obstacles avant l'initialisation du Sprite
static sf::Texture& getObstacleTexture(const std::string& type) {
    static std::map<std::string, sf::Texture> textureCache;
    if (textureCache.find(type) == textureCache.end()) {
        textureCache[type] = loadTexture("assets/" + type + ".png");
    }
    return textureCache[type];
}

Obstacle::Obstacle(std::string type, float x, float y) : sprite(getObstacleTexture(type)) {
    sprite.setScale({0.2f, 0.2f});
    sprite.setPosition(sf::Vector2f(x, y));
}

void Obstacle::update() {
    // Les obstacles sont maintenant fixes dans le monde
    // Ils ne bougent plus vers la gauche
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Obstacle::getBounds() {
    return sprite.getGlobalBounds();
}
