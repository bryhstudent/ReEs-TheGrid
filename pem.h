#ifndef PEM_H
#define PEM_H

#include "collectableitems.h"

using namespace std;

class PEM : public CollectableItems {
public:
    PEM(float posx = 0.0f, float posy = 0.0f);
    void collectItem(IScorable& target) override;
};

#endif // PEM_H
