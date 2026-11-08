#ifndef ELITEHUNTER_H
#define ELITEHUNTER_H

#include "hunter.h"

class EliteHunter : public Hunter {
private:
    float visionRadius;

public:
    EliteHunter(float posx = 0.0f, float posy = 0.0f, float velocity = 1.2f);

    float getVisionRadius() const;
    void setVisionRadius(float newRadius);
    bool drawRadius(float targetX, float targetY) const;
};

#endif // ELITEHUNTER_H
