#pragma once
#include "enemy.h"
class Skeleton: public Enemy {
bool side;
public:
    Skeleton(bool r);
    void init() override;
    void update(float dt) override;
    void draw() override;
};