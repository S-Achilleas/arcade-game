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
    Timer spawn_timer = Timer(3.0f, Timer::TIMER_LOOPING);

public:
    Level(const std::string& name = "Level 0");
    //platform loader is public so player can access platforms
    class Platform* platform_loader = nullptr;
    void update(float dt) override;
    void init() override;
    void draw() override;
    ~Level();
};