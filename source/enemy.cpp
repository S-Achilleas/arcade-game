#include "enemy.h"
#include "gamestate.h"
#include "player.h"
#include "sgg/graphics.h"

void Enemy::init() {
    walking = true;
    if (right_side) {
        d_pos_x =12.6f;
    }else {
        d_pos_x = -0.6f;
    }
    d_pos_y = 9.35f;
    width = 3.0f;   // Set a default value for width
    height = 3.0f;
}
void Enemy::update(float dt) {
    float delta_time = dt / 1000.0f;
    float player_x = state->getPlayer()->getPlayerX();
    float distance = std::abs(d_pos_x - player_x);

    const float stop_threshold = 0.5f;

    if (distance > stop_threshold) {
        if (d_pos_x < player_x) {
            d_pos_x += delta_time * 1.0f;
            facing_left = false;
        } else {
            d_pos_x -= delta_time * 1.0f;
            facing_left = true;
        }
    } else {
        //walking = false;
    }
}


Enemy::Enemy(bool r) : right_side(r) {
    init();
}


Enemy::~Enemy() {
}
