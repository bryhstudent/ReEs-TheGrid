#ifndef FRAG_H
#define FRAG_H

#include "collectableitems.h"

using namespace std;

class Frag : public CollectableItems {
private:
    int value;

public:
    Frag(float posx = 0.0f, float posy = 0.0f);
    void collectItem(IScorable& target) override;
};

#endif // FRAG_H
