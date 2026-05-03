cmake_minimum_required(VERSION 3.16)

# Nom du projet
project(PrincessRun LANGUAGES CXX)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fichiers sources
set(SOURCES
        main.cpp
        Menu.cpp
        Game.cpp
        Player.cpp
        Obstacle.cpp
        Utils.cpp
        
)

set(HEADERS
        Menu.h
        Game.h
        Player.h
        Obstacle.h
        Constants.h
        Utils.h
        Entity.h
)

# Créer l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Trouver SFML 3
find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System Audio)


# Lier SFML
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)

# Inclure les headers
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
