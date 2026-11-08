#ifndef FRAG_H
#define FRAG_H

#include "collectableitems.h"

class Frag : public CollectableItems {
private:
    int value;

public:
    Frag(float posx = 0.0f, float posy = 0.0f);
    void collectItem(IScorable& target) override;
    int getPointValue() const override;
};

#endif // FRAG_H
