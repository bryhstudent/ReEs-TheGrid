#include "collectableitems.h"

using namespace std;

CollectableItems::CollectableItems(float posx, float posy)
    : GameObject(posx, posy) {
    this->isCollected = false;
}

void CollectableItems::collectItem(IScorable& target) {
    target.addScore(10);
    this->isCollected = true;
}

bool CollectableItems::getIsCollected() const {
    return isCollected;
}

void CollectableItems::setIsCollected(bool status) {
    this->isCollected = status;
}
