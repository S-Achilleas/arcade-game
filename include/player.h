#pragma once
#include "gameobject.h"
#include <deque>
#include <string>
#include "ObjectWithMovement.h"
#include "projectile.h"
#include "timer.h"
#include "animation.h"

class Player:public ObjectWithMovement
{
    graphics::Brush player_brush_debug;
    void checkPlatformCollision();
    int jumpCount = 15;
    int neg = 1;
    float initial_y;

    Timer projCooldown = Timer(3.0f);

    graphics::Brush text;
    std::deque<Projectile> projectiles;

public:
    class playerFeetObj : public ObjectWithMovement
    {
        graphics::Brush pf_brush_debug;
    public:
        graphics::Brush returnbrush() { return pf_brush_debug; }
    };
    playerFeetObj* playerfeet = new playerFeetObj;

    Player(std::string name) : GameObject(name) {}

    void update(float dt) override;
    void init() override;
    void draw() override;
    float getPlayerX() {return m_pos_x;}
    float getPlayerY() { return m_pos_y; }
};
