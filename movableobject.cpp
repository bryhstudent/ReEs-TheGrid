#include "movableobject.h"

using namespace std;

MovableObject::MovableObject(float posx, float posy, float velocity)
    : GameObject(posx, posy) {
    this->velocity = velocity;
}

float MovableObject::getVelocity() const {
    return velocity;
}

void MovableObject::setVelocity(float newVelocity) {
    if (newVelocity >= 0.0f) {
        this->velocity = newVelocity;
    }
}

void MovableObject::move(float dx, float dy) {
    this->posx += dx * velocity;
    this->posy += dy * velocity;
}
