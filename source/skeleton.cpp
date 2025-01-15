#include "skeleton.h"
#include "gameobject.h"
#include "gamestate.h"
#include "animation.h"

Skeleton::Skeleton(bool r){
    side = r;
    init();
}

void Skeleton::init() {
    d_width = 2.0f;
    d_height = 2.0f;
    Enemy::init();
    my_animation =new Animation(false,graphics::preloadBitmaps(state->getFullAssetPath("skeleton/walk/right")),
        graphics::preloadBitmaps(state->getFullAssetPath("skeleton/walk/left")));
}

void Skeleton::update(float dt) {
    Enemy::update(dt);
}

void Skeleton::draw() {
    my_animation -> Animate(d_pos_x, d_pos_y, d_width, d_height, my_brush,facing_left,walking);
}
