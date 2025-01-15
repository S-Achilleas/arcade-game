#pragma once
#include "enemy.h"
class Skeleton: public Enemy {

public:
    Skeleton(bool r);
    void init() override;
    void update(float dt) override;
    void draw() override;
};