#ifndef COLLECTABLEITEMS_H
#define COLLECTABLEITEMS_H

#include "gameobject.h"
#include "iscorable.h"

class CollectableItems : public GameObject {
protected:
    bool isCollected;

public:
    CollectableItems(float posx = 0.0f, float posy = 0.0f);

    virtual void collectItem(IScorable& target);
    virtual int getPointValue() const;
    bool getIsCollected() const;
    void setIsCollected(bool status);
};

#endif // COLLECTABLEITEMS_H
