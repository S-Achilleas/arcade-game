#include "player.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "gameobject.h"
#include <iostream>
#include "math.h"
#include "level.h"
#include "my_stdio.h"


void Player::init() {
    d_pos_x = 5.5f;
    d_pos_y = 5.5f;
    d_width = 3.0f;
    d_height = 3.0f;

    hb_adj(1.0f, 2.0f);
    hbp_adj(d_pos_x, d_pos_y, 0, 1.0f);

    my_brush.fill_opacity = 1.0f;
    my_brush.outline_opacity = 0.0f;
    run_array_right = graphics::preloadBitmaps(state->getFullAssetPath("knight/run/right"));
    run_array_left = graphics::preloadBitmaps(state->getFullAssetPath("knight/run/left"));
    idle_array = graphics::preloadBitmaps(state->getFullAssetPath("knight/idle"));

    //debug init
    player_brush_debug.fill_opacity = 0.1f;
    SETCOLOR(player_brush_debug.fill_color, 1.0f, 0.1f, 0.1f);
    SETCOLOR(player_brush_debug.outline_color, 1.0f, 0.2f, 0.2f);
    //debug

}

void Player::update(float dt) {
    //const float velocity = 5.0f;
    //std::cout << m_pos_y << std::endl;
    float delta_time = dt / 1000.0f;
    float move = 0.0f;
    if (graphics::getKeyState(graphics::SCANCODE_A)) 
    {
        move -= 1.0f;
        //m_pos_x -= delta_time * velocity;
        walking = true;
        facing_left = true;
    }
        
    if (graphics::getKeyState(graphics::SCANCODE_D))
    {
        move += 1.0f;
        //m_pos_x += delta_time * velocity;
        walking = true;
        facing_left = false;
    }

    // X axis
    m_vx = std::min(max_velocity, m_vx + delta_time * move * accel_horizontal);
    m_vx = std::max(-max_velocity, m_vx);

    m_vx -= 0.2f * m_vx/(0.1f + fabs(m_vx));

    if (fabs(m_vx) < 0.01f) {
        m_vx = 0.0f;
    }

    //if(m_pos_x > 0.4 && m_pos_x < state->getCanvasWidth() - 0.4)
    d_pos_x += delta_time * m_vx;

    // Y axis
    bool isOnGround = (d_pos_y == 8.5);
    if (isOnPlatform || isOnGround) {
        m_vy = 0.0f; // Reset vertical velocity when on the ground.
        if (graphics::getKeyState(graphics::SCANCODE_W)) {
            m_vy = -accel_vertical; // Jump
        }
    }
    else {
        m_vy += delta_time * gravity;
    }
    
    d_pos_y = std::min(d_pos_y + m_vy * delta_time, 8.5f);
   
    hbp_adj(d_pos_x, d_pos_y, 0, 1.0f);

    checkCollision();
}

void Player::draw() {
    if (walking) {
        ObjectWithMovement::draw();
    }
    else {
        if (idleCount > 90)
            idleCount = 0;

        // todo left facing idle

        my_brush.texture = idle_array[idleCount/10];
        graphics::drawRect(d_pos_x, d_pos_y, d_width, d_height, my_brush);
        idleCount++;
    }

    if (state->debugging) { //draw debug
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, player_brush_debug);
    }
}

void Player::checkCollision() {
    for (auto& box : state->getLevel()->platform_loader->getPlatforms())
    {
        float offset = intersectDown(box);
        if (offset < 0.001 && offset != 0)
        {
            isOnPlatform = true;
            d_pos_y += offset;
            break;
        }
        else
        {
            isOnPlatform = false;
        }

    }
}