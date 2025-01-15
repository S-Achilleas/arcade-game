#include "level.h"
#include "player.h"
#include "gamestate.h"
#include "platform.h"
#include "enemy.h"
#include "skeleton.h"

Level::Level(const std::string &name) {
}

Level::~Level() {
    if (platform_loader) {
        delete platform_loader;
    }
}

void Level::init() {
    graphics::playMusic(state->getFullAssetPath("menu_music.mp3"), 0.4f); //music

    brush_background.outline_opacity = 0.0f;
    brush_background.texture = state->getFullAssetPath("background.png");
    spawn_timer.start();

    Platform::platformBrushInit();
    Platform::platformInitHandler(Platform(7.0f, 8.0f, 2.0f, 2.0f, "tile.png")); // platform object

};

void Level::draw() {

    graphics::drawRect(state->getCanvasWidth()/2.0f, state-> getCanvasHeight()/2.0f, 
        state->getCanvasWidth(), state-> getCanvasHeight(), brush_background);

   Platform::platformDisplayHandler(); // display platforms

    if (state ->getPlayer()->isActive())
        state ->getPlayer() ->draw();

    for (auto& enemy  : enemies) {
        enemy.draw();
    }
}

void Level::update(float dt) {
    if (state->getPlayer()->isActive()) {
        state->getPlayer()->update(dt);
    }

    // Update the timer value
    float timerValue = spawn_timer;

    // Check if the timer has looped back to 0
    if (timerValue < 0.1f && spawn_timer.isRunning()) {
        // Spawn a new enemy
        bool spawnRight = rand() % 2 == 0; // Randomize the spawn direction
        this_enemy = new Skeleton(spawnRight);
        enemies.push_back(this_enemy);
    }

    for (auto& enemy : enemies) {
        enemy.update(dt);
    }
    /*
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (it->isDead()) { // Check if the enemy is killed
            it = enemies.erase(it); // Remove the enemy from the list
        } else {
            ++it; // Move to the next enemy
        }
    }
    */

    GameObject::update(dt);
}