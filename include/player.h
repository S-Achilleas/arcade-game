#pragma once
#include "gameobject.h"
#include <vector>
#include <string>
#include "ObjectWithMovement.h"

class Player:public ObjectWithMovement
{
    graphics::Brush player_brush_debug;
    void checkCollision();
    int idleCount=1;
    int jumpCount = 15;
    int neg = 1;
    float initial_y;

    std::vector<std::string>jump_array_right;
    std::vector<std::string>jump_array_left;
    std::vector<std::string>idle_array;

public:
    Player(std::string name) : GameObject(name) {}

    void update(float dt) override;
    void init() override;
    void draw() override;
    float getPlayerX() {return m_pos_x;}
    float getPlayerY() { return m_pos_y; }
};
