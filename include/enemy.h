#pragma once
#include "ObjectWithMovement.h"

class Enemy : public ObjectWithMovement{
    void brushInit();
protected:
    bool right_side;
    static graphics::Brush my_brush;
    static float d_width;
    static float d_height;
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
    ~Enemy();
    void patrol(float dt);
    void drawDebug();

};

