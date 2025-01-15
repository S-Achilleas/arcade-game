#include "level.h"
#include "player.h"
#include "gamestate.h"
#include "platform.h"
#include "enemy.h"
#include "skeleton.h"
#include "iostream"
Level::Level(const std::string &name) {
}

Level::~Level() {
    for (auto enemy : enemies) {
        delete enemy;
    }
    if (platform_loader) {
        delete platform_loader;
    }
}


void Level::init() {
    graphics::playMusic(state->getFullAssetPath("menu_music.mp3"), 0.4f); //music

    brush_background.outline_opacity = 0.0f;
    brush_background.texture = state->getFullAssetPath("background.png");
    spawn_timer.start();
    std::cout << "Spawn timer started." << std::endl;



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
        enemy->draw();
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
        bool spawnRight = rand() % 2 == 0; // Randomize the spawn direction
        enemies.push_back(new Skeleton(spawnRight));
        std::cout << "Spawned new enemy. Total enemies: " << enemies.size() << std::endl;
    }


    for (auto& enemy : enemies) {
        enemy->update(dt);
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