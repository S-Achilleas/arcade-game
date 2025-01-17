#pragma once
#include "enemy.h"
#include "timer.h"

class Skeleton: public Enemy {
    float calculateProjectileVelocityX();
    float calculateProjectileVelocityY();
    static graphics::Brush sprojBrush;
    ObjectWithMovement* Proj = nullptr;
    float projVelX;
    float projVelY;
    void Skeleton::ProjCollisionHandler();
    void Skeleton::checkPlayerProjCollision();
public:
    class Animation* sProjAnimation;
    //Assets are public static so level can edit them
    static std::vector<std::string> right_assets;
    static std::vector<std::string> left_assets;
    static std::vector<std::string> right_attack_assets ;
    static std::vector<std::string> left_attack_assets ;
    static std::vector<std::string> sproj_assets;
    Skeleton(bool r);
    static void initt();
    void update(float dt) override;
    void draw() override;
    ~Skeleton();
};