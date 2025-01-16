#include "enemy.h"
#include "gamestate.h"
#include "healthbar.h"
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
    my_health = new HealthBar(10,d_pos_x,d_pos_y,"enemy_health",1.0f,1.0f);
}
void Enemy::update(float dt) {
    float delta_time = dt / 1000.0f;
    float distance = std::abs(d_pos_x - state->getPlayer()->getPlayerX());

    if (distance > 0.5f) {
        // Chase the player
        if (d_pos_x < state->getPlayer()->getPlayerX()) {
            d_pos_x += delta_time * 1.0f;
            facing_left = false;
        } else {
            d_pos_x -= delta_time * 1.0f;
            facing_left = true;
            walking = true;
        }
    } else {
        patrol(delta_time);
    }
}


Enemy::Enemy(bool r) : right_side(r) {
    init();
}


Enemy::~Enemy() {
}

void Enemy::draw() {
    my_health->draw();
}

void Enemy::patrol(float delta_time) {
    float max_distance = 4.0f;
    float max_distance_right = 2.0f;
    float player_x = state->getPlayer()->getPlayerX();
    float distance = std::abs(d_pos_x - player_x);

    if (distance < max_distance && facing_left) {
        d_pos_x -= delta_time * 1.0f;
        facing_left = true;
        if (distance + delta_time*1.0f > max_distance) {
            facing_left = false;
        }
    }else {
        d_pos_x += delta_time * 1.0f;
        facing_left = false;
        if (distance + delta_time*1.0f > max_distance) {
            facing_left = true;
        }
    }

}
