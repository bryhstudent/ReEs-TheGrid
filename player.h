#ifndef PLAYER_H
#define PLAYER_H

#include "movableobject.h"
#include "idamageable.h"
#include "iscorable.h"

class Player : public MovableObject, public IDamageable, public IScorable {
private:
    int remainingLifes;
    int score;

public:
    Player(float posx = 0.0f, float posy = 0.0f, float velocity = 1.0f);

    int getRemainingLifes() const;
    int getScore() const;

    void takeDamage(int amount) override;
    void addScore(int amount) override;
};

#endif // PLAYER_H
