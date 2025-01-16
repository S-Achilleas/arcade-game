#include "healthbar.h"
#include "gamestate.h"


HealthBar::HealthBar(int health, float pos_x, float pos_y, std::string path,float h,float w)
: health_points(health), h_pos_x(pos_x), h_pos_y(pos_y),full_path(state->getFullAssetPath(path)),height(h),width(w) {}


void HealthBar::init() {
    display_health_bar = graphics::preloadBitmaps(full_path);
    healthBarBrush.outline_opacity = 0.0f;
}

void HealthBar::update(float dt) {

}

void HealthBar::draw(bool follow,float x,float y) {
    healthBarBrush.texture = full_path + "/" + std::to_string(health_points) + ".png";
    if(follow) {
        graphics::drawRect(x, y-0.8f, width, height, healthBarBrush);
    }else {
        graphics::drawRect(h_pos_x, h_pos_y, width, height, healthBarBrush);
    }
}

void HealthBar::hit(int damage) {
    health_points = std::max(0, health_points - damage); // Prevent negative health
}


int HealthBar::getHealth() {
    return health_points;
}

HealthBar::~HealthBar() {
}
