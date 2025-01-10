#include "level.h"
#include "player.h"
#include "gamestate.h"

Level::Level(const std::string &name) {
}

Level::~Level() {
}

void Level::init() {
    brush_background.outline_opacity = 0.0f;
    brush_background.texture = state->getFullAssetPath("Environments/parallax_forest/v1/previewpng.png");
};

void Level::draw() {

    graphics::drawRect(state->getCanvasWidth()/2.0f, state-> getCanvasHeight()/2.0f, state->getCanvasWidth(), state-> getCanvasHeight(), brush_background);

    if (state ->getPlayer()->isActive())
        state ->getPlayer() ->draw();
}

void Level::update(float dt) {
    if (state ->getPlayer()->isActive())
        state ->getPlayer() ->update(dt);

    GameObject::update(dt);
}