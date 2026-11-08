#ifndef ISCORABLE_H
#define ISCORABLE_H

class IScorable {
public:
    virtual void addScore(int amount) = 0;
    virtual ~IScorable() = default;
};

#endif // ISCORABLE_H
