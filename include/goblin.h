#pragma once
#include "enemy.h"
class Goblin : public Enemy {
public:
    //Assets are public static so level can edit them
    static std::vector<std::string> right_assets;
    static std::vector<std::string> left_assets;
    Goblin(bool r);
    static void init();
    void update(float dt) override;
    void draw() override;
    ~Goblin();
};
