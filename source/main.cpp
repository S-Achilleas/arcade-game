#include <cstdio>
#include <string>
#include "sgg/graphics.h"
#include "gamestate.h"


void init() { // αρχικοποιει τις τιμες των βουρτσων
    GameState::getInstance()->init();
}


void update(float dt){
    GameState::getInstance()->update(dt);
}


void draw() {
    GameState::getInstance()->draw();
}

int main() {
    graphics::createWindow(800,800,"Boing Stage1");

    init();
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(),
        GameState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    graphics::startMessageLoop();
    return 0;
}
