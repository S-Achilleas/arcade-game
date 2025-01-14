#include "level.h"
#include "player.h"
#include "gamestate.h"
#include "platform.h"
#include <iostream>

Level::Level(const std::string &name) {
}

Level::~Level() {
}

void Level::init() {
    brush_background.outline_opacity = 0.0f;
    brush_background.texture = state->getFullAssetPath("Environments/parallax_forest/v1/previewpng.png");

    platform_loader = new Platform(); // platform object
    platform_loader->addPlatform(7.0f, 9.0f, 2.0f, 0.2f, "SOME.png");
    platform_loader->addPlatform(1.0f, 6.0f, 2.0f, 0.2f, "SOME.png");

};

void Level::draw() {

    graphics::drawRect(state->getCanvasWidth()/2.0f, state-> getCanvasHeight()/2.0f, 
        state->getCanvasWidth(), state-> getCanvasHeight(), brush_background);

    platform_loader->platformDisplayHandler(); // display platforms

    if (state ->getPlayer()->isActive())
        state ->getPlayer() ->draw();
}

void Level::update(float dt) {
    if (state->getPlayer()->isActive()) {
        state->getPlayer()->update(dt);
        
    }

    GameObject::update(dt);
}