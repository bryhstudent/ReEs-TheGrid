#ifndef COMMONHUNTER_H
#define COMMONHUNTER_H

#include "hunter.h"

using namespace std;

class CommonHunter : public Hunter {
public:
    CommonHunter(float posx = 0.0f, float posy = 0.0f, float velocity = 1.0f);
};

#endif // COMMONHUNTER_H
