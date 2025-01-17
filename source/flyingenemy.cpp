#include "flyingenemy.h"
#include "animation.h"
#include "gamestate.h"
#include "player.h"

//Class static definitions
std::vector<std::string> FlyingEnemy::right_assets = {};
std::vector<std::string> FlyingEnemy::left_assets = {};
//Static definitions end

FlyingEnemy::FlyingEnemy(bool r) : Enemy(r) {
    my_animation = new Animation(false, right_assets, left_assets);
    m_height = 0.7f;
    m_width = 1.1f;
    Enemy::init();
}

void FlyingEnemy::initt() {
    FlyingEnemy::my_brush.fill_opacity = 1.0f;
    FlyingEnemy::my_brush.outline_opacity = 0.0f;
}

void FlyingEnemy::update(float dt) {
    //flying enemy Y updates
    float delta_time = dt / 1000.0f;
    float distanceY = std::abs(d_pos_y - state->getPlayer()->getPlayerY());
    if (distanceY > 0.5f) {
        // Chase the player in Y
        if (d_pos_y < state->getPlayer()->getPlayerY()) {
            d_pos_y += delta_time * 0.5f;
        }
        else {
            d_pos_y -= delta_time * 0.5f;
        }
    }
    //flying enemy X updates
    Enemy::update(dt);
    m_pos_y += 0.05f; //offset
}

void FlyingEnemy::draw() {
    Enemy::draw();
    my_animation->Animate(d_pos_x, d_pos_y, FlyingEnemy::d_width,
        FlyingEnemy::d_height, FlyingEnemy::my_brush, facing_left, walking);
}

FlyingEnemy::~FlyingEnemy() {
    if (my_animation)
        delete my_animation;
    // kai gia healthbar
}
