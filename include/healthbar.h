#pragma once
#include <vector>
#include <string>
#include "gameobject.h"
#include "sgg/graphics.h"

class HealthBar : virtual public GameObject {
    graphics::Brush healthBarBrush;
    std::string full_path;
    int health_points;
    float h_pos_x;
    float h_pos_y;
    float height;
    float width;
    std::vector<std::string> display_health_bar;

    public:
    HealthBar(int health, float pos_x, float pos_y , std::string path,float h,float w);
    void init() override;
    void update(float dt) override;
    void draw(bool follow=false,float x=0.0f,float y=0.0f);
    void hit(int damage);
    int getHealth();
    ~HealthBar();
};

