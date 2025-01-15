#include "healthbar.h"
#include "gamestate.h"


HealthBar::HealthBar(int health, float pos_x, float pos_y, std::string path,float h,float w)
: health_points(health), h_pos_x(pos_x), h_pos_y(pos_y + 0.5f),full_path(state->getFullAssetPath(path)),height(h),width(w) {}


void HealthBar::init() {
    display_health_bar = graphics::preloadBitmaps(full_path);
    healthBarBrush.outline_opacity = 0.0f;
}

void HealthBar::update(float dt) {

}

void HealthBar::draw() {
    healthBarBrush.texture = display_health_bar[health_points];
    graphics::drawRect(h_pos_x, h_pos_y, width, height, healthBarBrush);
}

void HealthBar::hit(int damage) {
    health_points = std::max(0, health_points - damage); // Prevent negative health
}


int HealthBar::getHealth() {
    return health_points;
}

HealthBar::~HealthBar() {
}
