#include "pem.h"

using namespace std;

PEM::PEM(float posx, float posy)
    : CollectableItems(posx, posy) {}

void PEM::collectItem(IScorable& target) {
    target.addScore(20);
    this->isCollected = true;
}
