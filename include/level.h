#pragma once
#include "sgg/graphics.h"
#include "gameobject.h"
#include "list"
#include "box.h"
#include "platform.h"

class Level : public GameObject {
    graphics::Brush brush_background;

    float m_center_x = 5.0f;
    float m_center_y = 5.0f;

    std::vector<GameObject*> m_static_objects;
    std::list<GameObject*> m_dynamic_objects;
    std::vector<Box> m_blocks;
    std::vector<std::string> m_block_names;
    const float m_block_size = 1.0f;
    graphics::Brush m_block_brush;

    class Platform* platform_loader = nullptr;

    void checkCollision();

public:
    Level(const std::string& name = "Level 0");
    void update(float dt) override;
    void init() override;
    void draw() override;
    ~Level();
};