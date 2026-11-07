#include "player.h"

using namespace std;

Player::Player(float posx, float posy, float velocity)
    : MovableObject(posx, posy, velocity) {
    this->remainingLifes = 3;
    this->score = 0;
}

int Player::getRemainingLifes() const {
    return remainingLifes;
}

int Player::getScore() const {
    return score;
}

void Player::takeDamage(int amount) {
    if (this->remainingLifes > 0) {
        this->remainingLifes -= amount;
        if (this->remainingLifes < 0) {
            this->remainingLifes = 0;
        }
    }
}

void Player::addScore(int amount) {
    if (amount > 0) {
        this->score += amount;
    }
}
