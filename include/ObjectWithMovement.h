#pragma once
#include <vector>
#include <string>
#include "box.h"
#include "gamestate.h"
#include "gameobject.h"
#include "sgg/graphics.h"

class ObjectWithMovement:virtual public GameObject,virtual public Box{
protected:
    class HealthBar my_healthbar();
    int frames;
    bool walking = false;
    bool facing_left = false;
    bool attacking = false;
    bool coll_left = false;
    bool coll_right = false;

    //draw width & draw height
    float d_pos_x;
    float d_pos_y;
    float d_width;
    float d_height;

    const float gravity = 15.0f;
    const float accel_vertical = 8.0f;
    const float accel_horizontal = 20.0f;
    const float max_velocity = 10.0f;

    int walkCount = 1;
    graphics::Brush my_brush;
    std::vector<std::string>run_array_right;
    std::vector<std::string>run_array_left;
    std::vector<std::string>attack_array_right;
    std::vector<std::string>attack_array_left;

public:
    float m_vx = 0.0f;
    float m_vy = 0.0f;
    bool isOnPlatform;

    void update(float dt){}
    void init(){}
    void draw() override;
    void hbp_adj(float d_pos_x, float d_pos_y, float offset_x=0, float offset_y=0); //hitbox position adjustment
    void hb_adj(float width, float height); //hitbox width & height
    bool getLeft(){return facing_left;}
};
