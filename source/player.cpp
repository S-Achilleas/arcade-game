#include "player.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include <iostream>
#include "math.h"
#include "healthbar.h"
#include "box.h"
#include "my_stdio.h"

void Player::init() {
    m_pos_x = 0.4f;
    m_pos_y = 8.5f;
    width = 3.0f;
    height = 3.0f;
    
    //debug init
    playerhitbox.push_back(Box(m_pos_x, m_pos_y, width, height));
    player_brush_debug.fill_opacity = 0.1f;
    SETCOLOR(player_brush_debug.fill_color, 1.0f, 0.1f, 0.1f);
    SETCOLOR(player_brush_debug.outline_color, 1.0f, 0.2f, 0.2f);
    //debug

    my_brush.fill_opacity = 1.0f;
    my_brush.outline_opacity = 0.0f;
    run_array_right = graphics::preloadBitmaps(state->getFullAssetPath("knight/run/right"));
    run_array_left = graphics::preloadBitmaps(state->getFullAssetPath("knight/run/left"));
    idle_array = graphics::preloadBitmaps(state->getFullAssetPath("knight/idle"));

}

void Player::update(float dt) {
    const float velocity = 5.0f;
    float delta_time = dt / 1000.0f;
    if (graphics::getKeyState(graphics::SCANCODE_A))
        if (m_pos_x > 0.4) {
            m_pos_x -= delta_time * velocity;
            walking = true;
            facing_left = true;

        }
    if (graphics::getKeyState(graphics::SCANCODE_D))
        if (m_pos_x < state->getCanvasWidth() - 0.4) {
            m_pos_x += delta_time * velocity;
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
        if (jumpCount >= -15) {
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
            jumpCount = 15;
        }
    }
    //std::cout << m_pos_x << std::endl << m_pos_y << std::endl;
    //GameObject::update(dt);
}

void Player::draw() {
    if (walking) {
        ObjectWithMovement::draw();
    }
    else {
        if (idleCount > 90)
            idleCount = 0;
        my_brush.texture = idle_array[idleCount / 10];
        graphics::drawRect(m_pos_x, m_pos_y, width, height, my_brush);
        idleCount++;
    }

    if (state->debugging) { //draw debug
        graphics::drawRect(m_pos_x, m_pos_y, width, height, player_brush_debug);
    }
}

float Player::getPlayerX() {
    return m_pos_x;
}
