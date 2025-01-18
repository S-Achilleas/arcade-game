#pragma once
#include "sgg/graphics.h"
#include "gameobject.h"
#include <vector>
#include "box.h"
#include "platform.h"
#include "timer.h"

class Level : public GameObject {
    graphics::Brush brush_background;

    float m_center_x = 5.0f;
    float m_center_y = 5.0f;

    std::vector<class Enemy*> enemies;
    class Enemy* enemy_pointer;
    bool hasSpawnedThisCycle = false;
    const float m_block_size = 1.0f;
    int enemyType;
    graphics::Brush m_block_brush;
    graphics::Brush timeText;
    graphics::Brush lowHealthText;
    Timer spawn_timer = Timer(3.0f, Timer::TIMER_LOOPING);
    Timer enemy_attacking_timer = Timer(3.0f, Timer::TIMER_LOOPING);
    Timer playerHitTimer = Timer(1.5f);

    int startTime = graphics::getGlobalTime();
    int secondsPlayed = 0;
    int minutesPlayed = 0;
    std::string minadded0 = "";
    std::string secadded0 = "";

    void enemyInit();
public:
    Level(const std::string& name = "Level 0");
    //platform loader is public so player can access platforms
    class Platform* platform_loader = nullptr;
    void update(float dt) override;
    void init() override;
    void draw() override;
    void checkEnemiesCollisions();
    void checkCollisionProjectiles();
    void updateEnemies(float dt);
    void pauseTimeOffset(int inputtime) { startTime += inputtime; };
    ~Level();
};