#include "elitehunter.h"

using namespace std;

EliteHunter::EliteHunter(float posx, float posy, float velocity)
    : Hunter(posx, posy, velocity) {
    this->visionRadius = 4.0f;
}

float EliteHunter::getVisionRadius() const {
    return visionRadius;
}

void EliteHunter::setVisionRadius(float newRadius) {
    if (newRadius >= 0.0f) {
        this->visionRadius = newRadius;
    }
}

bool EliteHunter::drawRadius(float targetX, float targetY) const {
    float dx = this->getPosX() - targetX;
    float dy = this->getPosY() - targetY;
    float distanceSquared = (dx * dx) + (dy * dy);
    float radiusSquared = visionRadius * visionRadius;
    return distanceSquared <= radiusSquared;
}
