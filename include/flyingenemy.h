#pragma once
#include "enemy.h"
class FlyingEnemy : public Enemy {
public:
    //Assets are public static so level can edit them
    static std::vector<std::string> right_assets;
    static std::vector<std::string> left_assets;
    FlyingEnemy(bool r);
    static void init();
    void update(float dt) override;
    void draw() override;
};