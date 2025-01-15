#include "enemy.h"
#include "gamestate.h"
#include "player.h"
#include "sgg/graphics.h"

void Enemy::init() {
    walking = true;
    if (right) {
        d_pos_x =12.6f;
    }else {
        d_pos_x = -0.6f;
    }
    d_pos_y = 8.5;
    width = 1.0f;   // Set a default value for width
    height = 1.0f;
}
void Enemy::update(float dt) {
    float delta_time = dt/1000.0f;
    if (d_pos_x < state ->getPlayer()->getPlayerX()) {
        d_pos_x += delta_time*5.0f;
        facing_left = false;
    }else {
        d_pos_x -= delta_time*5.0f;
        facing_left = true;
    }
}

Enemy::Enemy() {
    init();
}

Enemy::~Enemy() {
}
