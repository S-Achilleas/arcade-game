#include "goblin.h"
#include "gamestate.h"
#include "animation.h"

Goblin::Goblin(bool r) : Enemy(r) {
    init();
}

void Goblin::init() {
    my_brush.fill_opacity = 1.0f;
    my_brush.outline_opacity = 0.0f;
    d_width = 3.5f;
    d_height = 3.5f;
    Enemy::init();
    my_animation =new Animation(false,graphics::preloadBitmaps(state->getFullAssetPath("goblin/run/right")),
        graphics::preloadBitmaps(state->getFullAssetPath("goblin/run/left")));
}

void Goblin::update(float dt) {
    Enemy::update(dt);
}

void Goblin::draw() {
    my_animation -> Animate(d_pos_x, d_pos_y, d_width, d_height, my_brush,facing_left,walking);
}
