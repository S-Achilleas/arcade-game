#include "player.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include <iostream>
#include "math.h"


void Player::init() {
    m_pos_x = 0.4f;
    m_pos_y = 8.5f;

    brush_player.fill_opacity = 1.0f;
    brush_player.outline_opacity = 0.0f;
    run_array_right = graphics::preloadBitmaps(state->getFullAssetPath("knight/run/right"));
    run_array_left = graphics::preloadBitmaps(state->getFullAssetPath("knight/run/left"));
    idle_array = graphics::preloadBitmaps(state->getFullAssetPath("knight/idle"));

}

void Player::update(float dt) {
    const float velocity = 5.0f;
    float delta_time = dt/1000.0f;
    if (graphics::getKeyState(graphics::SCANCODE_A))
        if (m_pos_x >state -> getCanvasWidth() -11.6) {
            m_pos_x -= delta_time*velocity;
            walking = true;
            facing_left = true;

        }
    if (graphics::getKeyState(graphics::SCANCODE_D))
        if (m_pos_x <state->getCanvasWidth()-0.4) {
            m_pos_x += delta_time*velocity;
            walking = true;
            facing_left = false;
        }
    if (graphics::getKeyState(graphics::SCANCODE_W))
    {
        if (!jumping) {
            jumping = true;
            facing_left = false;
            initial_y = m_pos_y; //auto 1
        }
    }
    if (jumping) {
        if (jumpCount >= -10) {
            neg = 1;
            if (jumpCount < 0) {
                neg = -1;
            }
            m_pos_y -= 0.05 * pow(jumpCount, 2) * velocity * neg * delta_time;
            jumpCount -= 1;
        }
        else {
            m_pos_y = initial_y; //auto 2
            jumping = false;
            jumpCount = 10;
        }
    }

    GameObject::update(dt);
}

void Player::draw() {
    if (walking) {
        if (walkCount > 90) {
            walkCount = 0;
        }
        if(facing_left) {
            brush_player.texture = run_array_left[walkCount/10];
            graphics::drawRect(m_pos_x, m_pos_y, 3.0f, 3.0f, brush_player);
            walkCount++;
            walking = false;
        }else {
            brush_player.texture = run_array_right[walkCount/10];
            graphics::drawRect(m_pos_x, m_pos_y, 3.0f, 3.0f, brush_player);
            walkCount++;
            walking = false;
        }
    }else {
        if (idleCount > 90)
            idleCount = 0;
        brush_player.texture = idle_array[idleCount/10];
        graphics::drawRect(m_pos_x, m_pos_y, 3.0f, 3.0f, brush_player);
        idleCount++;
    }
}
