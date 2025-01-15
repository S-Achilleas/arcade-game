#include "flyingenemy.h"
#include "animation.h"
#include "gamestate.h"
FlyingEnemy::FlyingEnemy(bool r) {
    side = r;
    init();
}

void FlyingEnemy::init() {
    my_brush.fill_opacity = 1.0f;
    my_brush.outline_opacity = 0.0f;
    d_width = 3.5f;
    d_height = 3.5f;
    Enemy::init();
    my_animation =new Animation(false,graphics::preloadBitmaps(state->getFullAssetPath("flyingEye/Flight/right")),
        graphics::preloadBitmaps(state->getFullAssetPath("flyingEye/Flight/left")));
}

void FlyingEnemy::update(float dt) {
    Enemy::update(dt);
}

void FlyingEnemy::draw() {
    my_animation -> Animate(d_pos_x, d_pos_y, d_width, d_height, my_brush,facing_left,walking);
}
