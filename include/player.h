#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include <vector>
#include <string>

class Player :public GameObject, public Box
{
    graphics::Brush brush_player;
    int health = 10;
    int walkCount = 1;
    int idleCount = 1;
    int jumpCount = 15;
    int neg = 1;
    float initial_y;
    bool walking = false;
    bool facing_left = false;
    bool jumping = false;
    std::vector<std::string>run_array_right;
    std::vector<std::string>run_array_left;
    std::vector<std::string>jump_array_right;
    std::vector<std::string>jump_array_left;
    std::vector<std::string>idle_array;

public:
    Player(std::string name) : GameObject(name) {}

    void update(float dt) override;
    void init() override;
    void draw() override;
};