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
    Timer projCooldown = Timer(3.0f);
    int jumpCount = 15;
    int neg = 1;
    float initial_y;
    
    graphics::Brush text;
    graphics::Brush player_brush_debug;
    std::deque<Projectile> projectiles;

    void playerMovement(float dt);
    void projectileHandler(float dt);
    void brushesInit();
    bool checkPlatformCollision();
    void drawDebug();
public:
    Player(std::string name) : GameObject(name) {}
    //playerfeet class | used only once as *playerfeet
    class playerFeetObj : public ObjectWithMovement
    {
        graphics::Brush pf_brush_debug;
    public:
        graphics::Brush returnbrush() { return pf_brush_debug; }
    };
    playerFeetObj* playerfeet = new playerFeetObj;

    void update(float dt) override;
    void init() override;
    void draw() override;
    float getPlayerX() { return m_pos_x; }
    float getPlayerY() { return m_pos_y; }
    std::deque<Projectile>* getProjectiles() { return &projectiles; }
};
