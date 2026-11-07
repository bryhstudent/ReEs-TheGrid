#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "gameobject.h"

using namespace std;

class MovableObject : public GameObject {
protected:
    float velocity;

public:
    MovableObject(float posx = 0.0f, float posy = 0.0f, float velocity = 1.0f);

    float getVelocity() const;
    void setVelocity(float newVelocity);
    virtual void move(float dx, float dy);
};

#endif // MOVABLEOBJECT_H
