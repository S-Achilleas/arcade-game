#pragma once
#include "enemy.h"

class Orge: public Enemy {
public:
    Orge(bool r);
    void init() override;
    void update(float dt) override;
    void draw() override;
};