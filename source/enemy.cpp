#include "enemy.h"
#include "gamestate.h"
#include "healthbar.h"
#include "player.h"
#include "sgg/graphics.h"
#include "my_stdio.h"
#include "iostream"

//Class static definitions
graphics::Brush Enemy::my_brush = {};
float Enemy::d_width = 3.5f;
float Enemy::d_height = 3.5f;
//Static definitions end


void Enemy::init() {
    walking = true;
    if (right_side) {
        d_pos_x =12.6f;
    }else {
        d_pos_x = -0.6f;
    }
    d_pos_y = 9.35f;
    my_health = new HealthBar(9,d_pos_x,d_pos_y,"healthbars/red_health",0.2f,0.8f);
    attackCooldownTimer = Timer(0.5f, Timer::TIMER_ONCE);
    attackCooldownTimer.start();
    brushInit();
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
    m_pos_x = d_pos_x;
    m_pos_y = d_pos_y;
}


Enemy::Enemy(bool r) : right_side(r) {
    init();
}


Enemy::~Enemy() {
    if (my_health) {
        delete my_health;
    }
}

void Enemy::draw() {
    my_health->draw(true,m_pos_x,m_pos_y);
    ObjectWithMovement::drawDebug(enemy_brush_debug, debug_text);
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

void Enemy::brushInit() {
    debug_text.fill_opacity = 1.0f;
    my_brush.fill_opacity = 1.0f;
    my_brush.outline_opacity = 0.0f;

    enemy_brush_debug.fill_opacity = 0.1f;
    SETCOLOR(enemy_brush_debug.fill_color, 1.0f, 0.1f, 0.1f);
    SETCOLOR(enemy_brush_debug.outline_color, 1.0f, 0.2f, 0.2f);

    if (state->debugging) {
        //draw player hitbox
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, enemy_brush_debug);

        //draw text: player position
        graphics::drawText(m_pos_x , m_pos_y , 0.4f, "X: " + std::to_string(m_pos_x)
            + " Y:" + std::to_string(m_pos_y) + " ID : " + std::to_string(id), debug_text);

    }
}
bool Enemy::canAttack() {
    float cooldowntime = attackCooldownTimer;
    if (!attackCooldownTimer.isRunning()){
        attackCooldownTimer = Timer(attackCooldownPeriod, Timer::TIMER_ONCE);
        attackCooldownTimer.start();
        return true;
    }
    return false;
}


