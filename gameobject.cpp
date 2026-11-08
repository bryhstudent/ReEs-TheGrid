#include "gameobject.h"

using namespace std;

GameObject::GameObject(float posx, float posy, float width, float height) {
    this->posx = posx;
    this->posy = posy;
    this->width = width > 0.0f ? width : 1.0f;
    this->height = height > 0.0f ? height : 1.0f;
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

float GameObject::getWidth() const { return width; }
float GameObject::getHeight() const { return height; }
void GameObject::setWidth(float newWidth) { if (newWidth > 0.0f) width = newWidth; }
void GameObject::setHeight(float newHeight) { if (newHeight > 0.0f) height = newHeight; }

bool GameObject::intersects(const GameObject& other) const {
    return posx < other.posx + other.width && posx + width > other.posx
        && posy < other.posy + other.height && posy + height > other.posy;
}

bool GameObject::touches(const GameObject& other) const {
    return posx <= other.posx + other.width && posx + width >= other.posx
        && posy <= other.posy + other.height && posy + height >= other.posy;
}
