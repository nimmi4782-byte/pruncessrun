#ifndef PRINCESSRUN_UTILS_H
#define PRINCESSRUN_UTILS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

// Fonction pour charger une texture avec gestion d'erreur
sf::Texture loadTexture(const std::string& filename);

// Fonction pour charger une police avec gestion d'erreur
sf::Font loadFont(const std::string& filename);


#endif //PRINCESSRUN_UTILS_H

