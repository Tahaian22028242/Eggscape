#include "header/player.hpp"

Player::Player(double x, double y) {
    this->x = x;
    this->y = y;
    this->width = playerWidth;
    this->height = playerHeight;
    this->onPlatform = false;
    this->velocity = (Vector2){0, 0};
    this->life = playerMaxLife;
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

unsigned int Player::getLife() {
    return life;
}

void Player::setLife(unsigned int value) {
    life = value;
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

void Player::setBorderAvailable(bool value) {
    borderAvailable = value;
}

bool Player::getBorderAvailable() {
    return borderAvailable;
}

// Game's base logic #2: Player's movement(the egg affected by gravity moves left and right).
void Player::updatePosition() {
    if (getLife() == 0) return;

    x += velocity.x; 
    y += velocity.y;
    
    if (!isOnPlatform()) 
    // If the egg is not on the platform, it will be affected by gravity.
        velocity.y += gravity;
    else 
    // If the egg is on the platform, it will stand still.
        velocity = (Vector2){0, 0};

    if (getBorderAvailable()) { 
        // If the egg hits the left or right border of the screen, it will bounce back.
        if (x < 0) {
            x = 0;          
            velocity.x *= -1;
        } 
        if (x + width > screenWidth) {
            x = screenWidth - width;
            velocity.x *= -1;
        }
    } else {
        // If the egg hits the left or right border of the screen, it will wrap around.
        if (x < 0)
            x = screenWidth - width; 
        if (x + width > screenWidth) 
            x = 0; 
    }
} // End of game's base logic #2.