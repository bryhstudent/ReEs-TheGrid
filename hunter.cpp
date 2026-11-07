#include "hunter.h"

using namespace std;

Hunter::Hunter(float posx, float posy, float velocity)
    : MovableObject(posx, posy, velocity) {}

void Hunter::attack(IDamageable& target) {
    target.takeDamage(1);
}
