#include "header/player.hpp"

#include <cmath>
#include <vector>

Player::Player(double x, double y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    onPlatform = false;
}

int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}

void Player::setX(int x) {
    this->x = x;
}

void Player::setY(int y) {
    this->y = y;
}

int Player::getWidth() {
    return width;
}

int Player::getHeight() {
    return height;
}

bool Player::isOnGround() {
    return onPlatform;
}

bool Player::isOnPlatform() {
    return onPlatform;
}

void Player::setOnPlatform(bool result) {
    onPlatform = result;
}

void Player::setVelocity(double x, double y) {
    velocity = (Vector2){x, y};
}

Vector2 Player::getVelocity() {
    return velocity;
}

// Game's base logic #2: Player's movement(the egg affected by gravity moves left and right).
void Player::updatePosition() {
    x += velocity.x;
    y += velocity.y;
    
    if (!isOnGround())
        velocity.y += gravity;
    else
        velocity = (Vector2){0, 0};
    
    if (x < 0)
        velocity.x *= -1;
    
    if (x + width > 800)
        velocity.x *= -1;
} // End of game's base logic #2.

