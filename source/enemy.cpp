#include "enemy.h"
#include "gamestate.h"
#include "player.h"
#include "sgg/graphics.h"

void Enemy::init() {
    if (right) {
        m_pos_x =12.6f;
    }else {
        m_pos_x = -0.6f;
    }
    m_pos_y = 8.5;
    // arxikopioisis ton array me animation
}

void Enemy::update(float dt) {
    float delta_time = dt/1000.0f;
    if (m_pos_x < state ->getPlayer()->getPlayerX()) {
        m_pos_x += delta_time*5.0f;
        facing_left = false;
    }else {
        m_pos_x -= delta_time*5.0f;
        facing_left = true;
    }
}

void Enemy::draw() {
    if (walking) {
        ObjectWithMovement::draw();
    }else {
    }
}

Enemy::Enemy(bool r) {
    right = r;
    init();
}

Enemy::~Enemy() {
}
