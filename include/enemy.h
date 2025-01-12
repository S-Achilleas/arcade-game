#pragma once
#include "gameobject.h"
#include "box.h"
#include "ObjectWithMovement.h"
#include "vector"

class Enemy : public ObjectWithMovement{
    bool right = true;
    float height;
    float width;
public:
    void init() override;
    void update(float dt) override;
    void draw() override;
    Enemy(bool r);
    ~Enemy();

};
