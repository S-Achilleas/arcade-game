#include "skeleton.h"
#include "gamestate.h"
#include "animation.h"

//Class static definitions
std::vector<std::string> Skeleton::right_assets = {};
std::vector<std::string> Skeleton::left_assets = {};
//Static definitions end

Skeleton::Skeleton(bool r) : Enemy(r) {
    my_animation = new Animation(false, right_assets, left_assets);
    Enemy::init();
}
void Skeleton::init() {
    Skeleton::my_brush.fill_opacity = 1.0f;
    Skeleton::my_brush.outline_opacity = 0.0f;
}

void Skeleton::update(float dt) {
    Enemy::update(dt);
}

void Skeleton::draw() {
    Enemy::draw();
    my_animation -> Animate(d_pos_x, d_pos_y, Skeleton::d_width, 
        Skeleton::d_height, Skeleton::my_brush, facing_left, walking);
}

Skeleton::~Skeleton() {
    if (my_animation)
        delete my_animation;
    // kai gia healthbar
}
