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

    //draw width & draw height
    float d_pos_x;
    float d_pos_y;
    float d_width;
    float d_height;

    float gravity = 15.0f;
    float accel_vertical = 8.0f;
    float accel_horizontal = 20.0f;
    float max_velocity = 10.0f;

    graphics::Brush my_brush;
    class HealthBar* my_health;
    class Animation* my_animation;

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
    //numbers are hitbox position x, y offsets
    void hbp_adj(float d_pos_x, float d_pos_y, float offset_x=0, float offset_y=0);
    //feet x,y offsets
    void hb_adj(float width, float height);
    bool getLeft(){return facing_left;}
    int getID() { return id; }
    bool isDead();
    class HealthBar* getHealthBar(){return my_health;}
    ~ObjectWithMovement();
};
