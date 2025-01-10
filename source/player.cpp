#include "player.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include <iostream>


void Player::init() {
    m_pos_x = 0.4f;
    m_pos_y = 8.5f;

    brush_player.fill_opacity = 1.0f;
    brush_player.outline_opacity = 0.0f;
    brush_player.texture = state ->getFullAssetPath("Characters/TerribleKnight/Sprites/Idle/frame1.png");
    run_array = graphics::preloadBitmaps(state->getFullAssetPath("Characters/TerribleKnight/Sprites/Run"));
}

void Player::update(float dt) {
    const float velocity = 5.0f;
    float delta_time = dt/1000.0f;
    if (graphics::getKeyState(graphics::SCANCODE_A))
        if (m_pos_x >state -> getCanvasWidth() -11.6) {
            m_pos_x -= delta_time*velocity;
            walking = true;
        }
    if (graphics::getKeyState(graphics::SCANCODE_D))
        if (m_pos_x <state->getCanvasWidth()-0.4) {
            m_pos_x += delta_time*velocity;
            walking = true;
        }
    if (graphics::getKeyState(graphics::SCANCODE_W))

    if (graphics::getKeyState(graphics::SCANCODE_S))

    GameObject::update(dt);
}

void Player::draw() {
    if (walking) {
        if (walkCount > 80) {
            walkCount = 1;
        }
        brush_player.texture = run_array[walkCount/10];
        graphics::drawRect(m_pos_x, m_pos_y, 3.0f, 3.0f, brush_player);
        walkCount++;
        walking = false;
    }else {
        brush_player.texture = state ->getFullAssetPath("Characters/TerribleKnight/Sprites/Idle/frame1.png");
        graphics::drawRect(m_pos_x, m_pos_y, 3.0f, 3.0f, brush_player);
    }
}
