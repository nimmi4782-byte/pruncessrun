#include "Utils.h"
#include <iostream>

sf::Texture loadTexture(const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Erreur: impossible de charger l'image " << filename << std::endl;
    }
    return texture;
}

sf::Font loadFont(const std::string& filename) {
    sf::Font font;
    if (!font.openFromFile(filename)) {
        std::cerr << "Erreur: impossible de charger la police " << filename << std::endl;
    }
    return font;
}




