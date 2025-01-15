#pragma once
#include "enemy.h"
class Goblin : public Enemy {
public:
    Goblin(bool r);
    void init() override;
    void update(float dt) override;
    void draw() override;
};
