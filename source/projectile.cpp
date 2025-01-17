#include "projectile.h"
#include <iostream>
#include "my_stdio.h"
#include "gamestate.h"
#include "timer.h"

Projectile::Projectile(float x, float y, float w, float h, bool left) {
    // Initialize member variables if needed
    m_pos_x = x;
    m_pos_y = y;
    m_width = w;
    m_height = h-0.8f; //has offset
    spawnedLeft = left;
    if (left)
        dir = -1.0f;
    else
        dir = 1.0f;
    activeTime = Timer(3.0f, Timer::timer_type_t::TIMER_ONCE);
    activeTime.start();
    init();
}

// init function implementation
void Projectile::init() {
    projectile_brush_left.texture = state->getFullAssetPath("katanal.png");
    projectile_brush_right.texture = state->getFullAssetPath("katanar.png");
    projectile_brush.outline_opacity = 0.0f;
    brush_debug.fill_opacity = 0.1f;
    SETCOLOR(brush_debug.fill_color, 1.0f, 0.1f, 0.1f);
    SETCOLOR(brush_debug.outline_color, 1.0f, 0.2f, 0.2f);
}

// update function implementation
void Projectile::update(float dt) {
    // Update projectile's position or state
    m_pos_x += dir * 0.2f;
}

// draw function implementation
void Projectile::draw() {
    if (spawnedLeft) {
        projectile_brush.texture = projectile_brush_left.texture;
    }else {
        projectile_brush.texture = projectile_brush_right.texture;
    }
    //Has offset added
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height+0.8f, projectile_brush);
    if (state->debugging)
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height , brush_debug);
}
