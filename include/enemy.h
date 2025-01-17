#pragma once
#include "ObjectWithMovement.h"
#include "timer.h"

class Enemy : public ObjectWithMovement{
    void brushInit();
protected:
    bool right_side;
    static graphics::Brush my_brush;
    static float d_width;
    static float d_height;
    std::vector<std::string> idr;
    std::vector<std::string> idl;


    Timer attackCooldownTimer;  // Timer for attack cooldown
    float attackCooldownPeriod = 1.0f; // Cooldown duration in seconds (default:)

public:
    //these brushes are public so enemies can
    //use them if they need to draw any
    //object of theirs
    graphics::Brush debug_text;
    graphics::Brush enemy_brush_debug;
    void init() override;
    void update(float dt) override;
    void draw() override;
    Enemy(bool r);
    virtual ~Enemy();
    void patrol(float dt);
    void drawDebug();
    bool canAttack();
    void resetAttackCooldown();
    virtual void playSound(){}

};

