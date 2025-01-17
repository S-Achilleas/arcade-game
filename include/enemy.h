#pragma once
#include "ObjectWithMovement.h"

class Enemy : public ObjectWithMovement{
    void brushInit();
    graphics::Brush debug_text;
    graphics::Brush enemy_brush_debug;
protected:
    bool right_side;
    static graphics::Brush my_brush;
    static float d_width;
    static float d_height;
public:
    void init() override;
    void update(float dt) override;
    void draw() override;
    Enemy(bool r);
    ~Enemy();
    void patrol(float dt);
    void drawDebug();

};

