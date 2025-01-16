#include "goblin.h"
#include "gamestate.h"
#include "animation.h"

//Class static definitions
std::vector<std::string> Goblin::right_assets = {};
std::vector<std::string> Goblin::left_assets = {};
//Static definitions end

Goblin::Goblin(bool r) : Enemy(r) {
    my_animation = new Animation(false, right_assets, left_assets);
    Enemy::init();
}

void Goblin::init() {
    Goblin::my_brush.fill_opacity = 1.0f;
    Goblin::my_brush.outline_opacity = 0.0f;
}

void Goblin::update(float dt) {
    Enemy::update(dt);
}

void Goblin::draw() {
    Enemy::draw();
    my_animation -> Animate(d_pos_x, d_pos_y, Goblin::d_width,
        Goblin::d_height, Goblin::my_brush,facing_left,walking);
}
