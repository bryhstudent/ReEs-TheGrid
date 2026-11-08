#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
protected:
    float posx;
    float posy;
    float width;
    float height;

public:
    GameObject(float posx, float posy, float width = 1.0f, float height = 1.0f);
    virtual ~GameObject() = default;

    float getPosX() const;
    float getPosY() const;
    void setPosX(float newPosX);
    void setPosY(float newPosY);
    float getWidth() const;
    float getHeight() const;
    void setWidth(float newWidth);
    void setHeight(float newHeight);
    bool intersects(const GameObject& other) const;
    bool touches(const GameObject& other) const;
};

#endif // GAMEOBJECT_H
