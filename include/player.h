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
    bool isOnGround;
    bool skeletonShootProj = false;
    bool collideWithPlatforms = true;
    bool godToggleInProgress = false;
    Timer projCooldown = Timer(3.0f);
    Timer timeNotOnGround = Timer(5.0f);
    Timer resetPlatformCollision;
    int jumpCount = 15;
    int neg = 1;
    float initial_y;
    int score = 0;

    graphics::Brush text;
    graphics::Brush pause_text;
    graphics::Brush player_brush_debug;
    std::vector<Projectile> projectiles;
    Timer projectileCooldownTimer;  // Timer for attack cooldown
    Timer godTimer = Timer(1.5f); //Godmode cooldown
    float projectileCooldownPeriod = 0.5f; // Cooldown duration in seconds (default:)

    void playerMovement(float dt);
    void projectileHandler(float dt);
    void skeletonProjectilePlayer(float dt);
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
    bool god = false;

    void update(float dt) override;
    void init() override;
    void draw() override;
    float getPlayerX() { return m_pos_x; }
    float getPlayerY() { return m_pos_y; }
    std::vector<Projectile>* getProjectiles() { return &projectiles; }
    void setScoreUp() { score += 100; }
    int getScore() { return score; }
    bool shouldShootProj() { return skeletonShootProj; }
    void platformColToggle(bool input) { collideWithPlatforms = input; }
    ~Player();
};
