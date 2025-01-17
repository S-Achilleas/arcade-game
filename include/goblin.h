#pragma once
#include "enemy.h"
class Goblin : public Enemy {
public:
    //Assets are public static so level can edit them
    static std::vector<std::string> right_assets;
    static std::vector<std::string> left_assets;
    static std::vector<std::string> right_attack_assets ;
    static std::vector<std::string> left_attack_assets ;
    Goblin(bool r);
    static void initt();
    void update(float dt) override;
    void draw() override;
    void playSound() override;
    ~Goblin();
};
