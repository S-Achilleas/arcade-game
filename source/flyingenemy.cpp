#include "flyingenemy.h"
#include "animation.h"
#include "gamestate.h"

//Class static definitions
std::vector<std::string> FlyingEnemy::right_assets = {};
std::vector<std::string> FlyingEnemy::left_assets = {};
//Static definitions end

FlyingEnemy::FlyingEnemy(bool r) : Enemy(r) {
    my_animation = new Animation(false, right_assets, left_assets);
    Enemy::init();
}

void FlyingEnemy::init() {
    FlyingEnemy::my_brush.fill_opacity = 1.0f;
    FlyingEnemy::my_brush.outline_opacity = 0.0f;
}

void FlyingEnemy::update(float dt) {
    Enemy::update(dt);
}

void FlyingEnemy::draw() {
    Enemy::draw();
    my_animation->Animate(d_pos_x, d_pos_y, FlyingEnemy::d_width,
        FlyingEnemy::d_height, FlyingEnemy::my_brush, facing_left, walking);
}
