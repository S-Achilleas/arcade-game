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

    //hitbox width & height
    hb_adj(1.0f, 2.0f); //player width & height
    playerfeet->hb_adj(0.4f, 0.1f); //feet width & height
    //hitbox width & height end

    text.fill_opacity = 1.0f;
    graphics::setFont(state->getFullAssetPath("DefaultSans-Regular.ttf"));

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

    if(m_pos_x > 0.4 && m_vx<0 || 
        m_pos_x < state->getCanvasWidth() - 0.4 && m_vx >0)
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

    //hitbox offsets
    hbp_adj(d_pos_x, d_pos_y, 0, 1.0f); //numbers are player hitbox x, y offsets
    playerfeet->hbp_adj(d_pos_x, d_pos_y, -0.12f, 1.5f); //feet x,y offsets
    //hitbox offsets end

    checkPlatformCollision();

    if (graphics::getKeyState(graphics::SCANCODE_SPACE))
    {
        printf("8");
        
    }
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

    if (state->debugging) { //draw player hit and feet hit (debug)
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, player_brush_debug);
        graphics::drawRect(playerfeet->m_pos_x, playerfeet->m_pos_y,
            playerfeet->m_width, playerfeet->m_height, playerfeet->returnbrush());
        graphics::drawText(m_pos_x-0.3f, m_pos_y-1.2f, 0.4f, "X: " + std::to_string(m_pos_x)
            + " Y:" + std::to_string(m_pos_y) + " ID : " + std::to_string(id), text);

    }
}

void Player::checkPlatformCollision() {
    for (auto& box : state->getLevel()->platform_loader->getPlatforms())
    {
        float offset = playerfeet->intersectDown(box); //platform to feet offset
        if (offset && m_vy>0)
        {
            isOnPlatform = true;
            //if (offset - d_pos_y >= 0.001) <<< FALLING PLATFORMS
            d_pos_y += offset;
            break;
        }
        else
        {
            isOnPlatform = false;
        }

    }
}