#pragma once

#include "ObjectWithMovement.h"

class Enemy : public ObjectWithMovement{
protected:
    bool right;
    float height;
    float width;
public:
    void init() override;
    void update(float dt) override;
    void draw(){}
    Enemy();
    ~Enemy();

};
