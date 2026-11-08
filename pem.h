#ifndef PEM_H
#define PEM_H

#include "collectableitems.h"

class PEM : public CollectableItems {
public:
    PEM(float posx = 0.0f, float posy = 0.0f);
    void collectItem(IScorable& target) override;
    int getPointValue() const override;
};

#endif // PEM_H
