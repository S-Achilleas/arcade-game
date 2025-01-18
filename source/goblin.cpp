#include "goblin.h"
#include "gamestate.h"
#include "animation.h"

//Class static definitions
std::vector<std::string> Goblin::right_assets = {};
std::vector<std::string> Goblin::left_assets = {};
std::vector<std::string> Goblin::right_attack_assets = {};
std::vector<std::string> Goblin::left_attack_assets = {};
//Static definitions end

Goblin::Goblin(bool r) : Enemy(r) {
    my_animation = new Animation(false, right_assets, left_assets,idr,idl,right_attack_assets,left_attack_assets);
    m_height = 0.8f;
    m_width = 1.3f;
    this->velocity = 2.0f;
    Enemy::init();
}

void Goblin::initt() {
    Goblin::my_brush.fill_opacity = 1.0f;
    Goblin::my_brush.outline_opacity = 0.0f;
}

void Goblin::update(float dt) {
    Enemy::update(dt);
    m_pos_y += 0.2f; //offset
}

void Goblin::draw() {
    Enemy::draw();
    my_animation -> Animate(d_pos_x, d_pos_y, Goblin::d_width,
        Goblin::d_height, Goblin::my_brush,facing_left,walking,attacking);
}

void Goblin::playSound() {
    graphics::playSound("assets/music/goblin_s.wav",0.3f);
}

Goblin::~Goblin() {
    if (my_animation)
        delete my_animation;
}
