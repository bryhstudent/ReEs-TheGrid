#include "gameobject.h"

using namespace std;

GameObject::GameObject(float posx, float posy) {
    this->posx = posx;
    this->posy = posy;
}

float GameObject::getPosX() const {
    return posx;
}

float GameObject::getPosY() const {
    return posy;
}

void GameObject::setPosX(float newPosX) {
    this->posx = newPosX;
}

void GameObject::setPosY(float newPosY) {
    this->posy = newPosY;
}
