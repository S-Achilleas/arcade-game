#pragma once
#include <vector>
#include <string>
#include "box.h"
#include "gameobject.h"
#include "sgg/graphics.h"

class ObjectWithMovement:virtual public GameObject,virtual public Box{
protected:
    int frames;
    bool walking = false;
    bool facing_left = false;
    bool attacking = false;
    class Animation* my_animation;
    class HealthBar* my_health;

    //draw width & draw height
    float d_pos_x;
    float d_pos_y;
    float d_width;
    float d_height;

    const float gravity = 15.0f;
    const float accel_vertical = 8.0f;
    const float accel_horizontal = 20.0f;
    const float max_velocity = 10.0f;

    graphics::Brush my_brush;

public:
    float m_vx = 0.0f;
    float m_vy = 0.0f;
    bool isOnPlatform;

    void update(float dt){}
    void init(){}
    void draw(){}
    void setWalking(bool w){walking = w;}
    void setFacingLeft(bool f){facing_left = f;}
    void setAttacking(bool a){attacking = a;}
    void hbp_adj(float d_pos_x, float d_pos_y, float offset_x=0, float offset_y=0); //hitbox position adjustment
    void hb_adj(float width, float height); //hitbox width & height
    bool getLeft(){return facing_left;}
    int getID() { return id; }
};
