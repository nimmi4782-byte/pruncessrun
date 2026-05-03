#include "Player.h"
#include "Constants.h"
#include "Utils.h"
#include <iostream>

static sf::Texture& getRunTex()  { static sf::Texture t = loadTexture("assets/princess_run.png");  return t; }
static sf::Texture& getJumpTex() { static sf::Texture t = loadTexture("assets/princess_jump.png"); return t; }
static sf::Texture& getDuckTex() { static sf::Texture t = loadTexture("assets/princess_duck.png"); return t; }

Player::Player() : sprite(getRunTex()), health(3), invulnerable(false) {
    sprite.setScale({0.2f, 0.2f});
    sprite.setPosition(sf::Vector2f(100.f, static_cast<float>(WINDOW_HEIGHT) - 200.f));

    groundY = static_cast<float>(WINDOW_HEIGHT) - 200.f;
    verticalVelocity = 0.f;
    isJumping = false;
    isDucking = false;

    healthBarBackground.setSize(sf::Vector2f(150.f, 20.f));
    healthBarBackground.setFillColor(sf::Color(100, 100, 100));
    healthBarBackground.setPosition(sf::Vector2f(20.f, 20.f));

    healthBar.setSize(sf::Vector2f(150.f, 20.f));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(sf::Vector2f(20.f, 20.f));
}

void Player::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !isJumping) {
        verticalVelocity = -20.f;
        isJumping = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !isJumping) {
        isDucking = true;
    } else {
        isDucking = false;
    }
}

void Player::update() {
    if (isJumping) {
        sprite.setTexture(getJumpTex());
    } else {
        sprite.setTexture(getRunTex());
    }

    if (isDucking && !isJumping) {
        sprite.setTexture(getDuckTex());
        float currentX = sprite.getPosition().x;
        sprite.setPosition({currentX, groundY + 60.f}); // ← تنزل للأسفل
    }
    else if (!isJumping) {
        float currentX = sprite.getPosition().x;
        sprite.setPosition({currentX, groundY});
        sprite.setScale({0.2f, 0.2f});
    }

    sprite.move({static_cast<float>(PLAYER_SPEED) * 0.5f, 0.f});

    if (isJumping) {
        verticalVelocity += 1.f;
        sprite.move({0.f, verticalVelocity});

        if (sprite.getPosition().y >= groundY) {
            sprite.setPosition({sprite.getPosition().x, groundY});
            isJumping = false;
            verticalVelocity = 0.f;
        }
    }
    else if (sprite.getPosition().y != groundY && !isDucking) { // ← زدنا !isDucking
        sprite.setPosition({sprite.getPosition().x, groundY});
    }

    if (invulnerable) {
        if (invulnClock.getElapsedTime().asSeconds() > 1.5f) {
            invulnerable = false;
            sprite.setColor(sf::Color::White);
        } else {
            sprite.setColor((invulnClock.getElapsedTime().asMilliseconds() / 100) % 2 == 0 ? sf::Color::Transparent : sf::Color::White);
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::drawUI(sf::RenderWindow& window) {
    window.draw(healthBarBackground);
    window.draw(healthBar);
}

sf::FloatRect Player::getBounds() {
    return sprite.getGlobalBounds();
}

void Player::takeDamage() {
    if (health > 0 && !invulnerable) {
        health--;
        float ratio = health / 3.0f;
        healthBar.setSize(sf::Vector2f(150.f * ratio, 20.f));
        sprite.setColor(sf::Color(255, 0, 0, 128));
        invulnerable = true;
        invulnClock.restart();
    }
}

bool Player::isAlive() {
    return health > 0;
}

void Player::resetHealth() {
    health = 3;
    healthBar.setSize(sf::Vector2f(150.f, 20.f));
    sprite.setColor(sf::Color::White);
}

// ← الفونكسيون الجديدة
void Player::resetPosition() {
    sprite.setPosition(sf::Vector2f(100.f, static_cast<float>(WINDOW_HEIGHT) - 200.f));
    verticalVelocity = 0.f;
    isJumping = false;
    isDucking = false;
    sprite.setScale({0.2f, 0.2f});
    sprite.setTexture(getRunTex());
}