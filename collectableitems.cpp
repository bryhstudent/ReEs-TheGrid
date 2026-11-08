#include "collectableitems.h"

using namespace std;

CollectableItems::CollectableItems(float posx, float posy)
    : GameObject(posx, posy, 0.45f, 0.45f) {
    this->isCollected = false;
}

void CollectableItems::collectItem(IScorable& target) {
    if (isCollected) return;
    target.addScore(getPointValue());
    this->isCollected = true;
}

int CollectableItems::getPointValue() const { return 10; }

bool CollectableItems::getIsCollected() const {
    return isCollected;
}

void CollectableItems::setIsCollected(bool status) {
    this->isCollected = status;
}
