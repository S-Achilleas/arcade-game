#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include <vector>
#include <string>
#include "ObjectWithMovement.h"

class Player :public ObjectWithMovement
{

    std::vector<Box> playerhitbox;
    graphics::Brush player_brush_debug;

    int idleCount = 1;
    int jumpCount = 15;
    int neg = 1;
    float initial_y;
    bool jumping = false;
    std::vector<std::string>jump_array_right;
    std::vector<std::string>jump_array_left;
    std::vector<std::string>idle_array;

public:
    Player(std::string name) : GameObject(name) {}

    void update(float dt) override;
    void init() override;
    void draw() override;
    float getPlayerX();
};
