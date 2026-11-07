#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

using namespace std;

class GameObject {
protected:
    float posx;
    float posy;

public:
    GameObject(float posx, float posy);
    virtual ~GameObject() = default;

    float getPosX() const;
    float getPosY() const;
    void setPosX(float newPosX);
    void setPosY(float newPosY);
};

#endif // GAMEOBJECT_H
