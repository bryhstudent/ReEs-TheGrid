#ifndef IDAMAGEABLE_H
#define IDAMAGEABLE_H

class IDamageable {
public:
    virtual void takeDamage(int amount) = 0;
    virtual ~IDamageable() = default;
};

#endif // IDAMAGEABLE_H
