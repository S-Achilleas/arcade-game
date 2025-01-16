#pragma once
#include "enemy.h"
class Skeleton: public Enemy {
public:
    //Assets are public static so level can edit them
    static std::vector<std::string> right_assets;
    static std::vector<std::string> left_assets;
    Skeleton(bool r);
    static void initt();
    void update(float dt) override;
    void draw() override;
    ~Skeleton();
};