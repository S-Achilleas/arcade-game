#include "orge.h"

Orge::Orge(bool r): Enemy(r) {
}

void Orge::init() {
    Enemy::init();
    //my_animation
}

void Orge::update(float dt) {
    Enemy::update(dt);
}

void Orge::draw() {
    Enemy::draw();
}
