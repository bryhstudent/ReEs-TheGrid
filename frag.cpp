#include "frag.h"

using namespace std;

Frag::Frag(float posx, float posy)
    : CollectableItems(posx, posy) {
    this->value = 10;
}

void Frag::collectItem(IScorable& target) {
    target.addScore(this->value);
    this->isCollected = true;
}
