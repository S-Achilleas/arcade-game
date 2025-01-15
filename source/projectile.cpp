#include "projectile.h"

// Constructor
Projectile::Projectile(float x, float y, float w, float h) {
    // Initialize member variables if needed
    m_pos_x = x;
    m_pos_y = y;
    m_width = w;
    m_height = h;
}

// init function implementation
void Projectile::init() {
    // Initialize or set up anything specific for the Projectile
}

// update function implementation
void Projectile::update(float dt) {
    // Update projectile's position or state
}

// draw function implementation
void Projectile::draw() {
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, projectile_brush);
}