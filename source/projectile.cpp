#include "projectile.h"
#include <iostream>

#include "gamestate.h"
#include "timer.h"

// Constructor
Projectile::Projectile(float x, float y, float w, float h, bool left) {
    // Initialize member variables if needed
    m_pos_x = x;
    m_pos_y = y;
    m_width = w;
    m_height = h;
    if (left)
        dir = -1.0f;
    else
        dir = 1.0f;
    activeTime = Timer(3.0f, Timer::timer_type_t::TIMER_ONCE);
    activeTime.start();
}

// init function implementation
void Projectile::init() {
    // Initialize or set up anything specific for the Projectile
}

// update function implementation
void Projectile::update(float dt) {
    // Update projectile's position or state
    m_pos_x += dir * 0.2f;
}

// draw function implementation
void Projectile::draw() {
    projectile_brush.texture = state -> getFullAssetPath("katana.png");
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, projectile_brush);
}
