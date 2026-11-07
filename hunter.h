#ifndef HUNTER_H
#define HUNTER_H

#include "movableobject.h"
#include "idamageable.h"

using namespace std;

class Hunter : public MovableObject {
public:
    Hunter(float posx = 0.0f, float posy = 0.0f, float velocity = 1.0f);
    virtual void attack(IDamageable& target);
};

#endif // HUNTER_H
