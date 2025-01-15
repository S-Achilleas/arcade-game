#pragma once
#include "sgg/graphics.h"
#include "gameobject.h"
#include "list"
#include "box.h"
#include "platform.h"
#include "timer.h"

class Level : public GameObject {
    graphics::Brush brush_background;
    class Enemy* this_enemy;

    float m_center_x = 5.0f;
    float m_center_y = 5.0f;

    std::list<class Enemy> enemies;
    const float m_block_size = 1.0f;
    graphics::Brush m_block_brush;
    Timer spawn_timer = (3.0f, Timer::TIMER_LOOPING);

public:
    Level(const std::string& name = "Level 0");
    //platform loader is public so player can access platforms
    class Platform* platform_loader = nullptr;
    void update(float dt) override;
    void init() override;
    void draw() override;
    ~Level();
};