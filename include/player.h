#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include <vector>
#include <string>

class Player:public GameObject,public Box
{
    graphics::Brush brush_player;
    int health = 10;
    int walkCount;
    bool walking = false;
    std::vector<std::string>run_array ;
public:
    Player(std::string name): GameObject(name){}

    void update(float dt) override;
    void init() override;
    void draw() override;
};