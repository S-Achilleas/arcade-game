#pragma once
#include "sgg/graphics.h"
#include "level.h"
#include "gamestate.h"
#include "timer.h"

class main_menu : public Level 
{

    graphics::Brush brush_background;
    graphics::Brush text;

    Timer killTime = Timer(1.0f);
    float m_center_x = 5.0f;
    float m_center_y = 5.0f;
public:
    main_menu(const std::string& name = "Menu") {};
    void update(float dt) override;
    void init() override;
    void draw() override;
    ~main_menu() = default;
};