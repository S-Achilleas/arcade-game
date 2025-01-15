#pragma once
#include <vector>
#include <string>
#include "gameobject.h"
#include "sgg/graphics.h"
class Animation : public GameObject {
    int walkCount=0;
    int idleCount =0;
    bool player;
    std::vector<std::string> run_right;
    std::vector<std::string> run_left;
    std::vector<std::string> attack_right;
    std::vector<std::string> attack_left;
    std::vector<std::string> idle;
public:
    Animation(bool p,std::vector<std::string> rr = {},
              std::vector<std::string> rl = {},
              std::vector<std::string> id = {},
              std::vector<std::string> ar = {},
              std::vector<std::string> al = {});

    void Animate(float x , float y,float w,float h,graphics::Brush b,bool facing,bool walking =false);
};
