#pragma once

#include "ObjectWithMovement.h"

class Enemy : public ObjectWithMovement{
protected:
    bool right_side;
    float height;
    float width;
public:
    void init() override;
    void update(float dt) override;
    void draw(){}
    Enemy(bool r);
    ~Enemy();
    void patrol(float dt);

};
