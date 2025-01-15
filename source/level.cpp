#include "level.h"
#include "player.h"
#include "gamestate.h"
#include "platform.h"
#include "enemy.h"
#include "skeleton.h"
#include "flyingenemy.h"
#include "goblin.h"
#include "iostream"
#include <random>
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

#include <random> // For random number generation

void Level::update(float dt) {
    // Update player
    if (state->getPlayer()->isActive()) {
        state->getPlayer()->update(dt);
    }

    float timerProgress = spawn_timer;

    // Check if it's time to spawn an enemy
    if (timerProgress >= 0.9f && !hasSpawnedThisCycle) {
        // Randomly choose an enemy type (0 = Skeleton, 1 = Goblin, 2 = FlyingEnemy)
        static std::random_device rd;  // Seed for randomness
        static std::mt19937 gen(rd()); // Random number generator
        static std::uniform_int_distribution<> dis(0, 2); // Range: 0 to 2

        int enemyType = dis(gen);
        Enemy* enemy_pointer = nullptr;

        switch (enemyType) {
            case 0:
                enemy_pointer = new Skeleton(rand() % 2 == 0); // Spawn Skeleton
                std::cout << "Spawned Skeleton" << std::endl;
                break;
            case 1:
                //enemy_pointer = new Goblin(rand() % 2 == 0); // Spawn Goblin
                std::cout << "Spawned Goblin" << std::endl;
                break;
            case 2:
                //enemy_pointer = new FlyingEnemy(rand() % 2 == 0); // Spawn FlyingEnemy
                std::cout << "Spawned FlyingEnemy" << std::endl;
                break;
        }

        // Add the spawned enemy to the list
        if (enemy_pointer) {
            enemies.push_back(enemy_pointer);
            hasSpawnedThisCycle = true; // Prevent another spawn in the current cycle
            std::cout << "Total enemies: " << enemies.size() << std::endl;
        }
    }

    // Reset the spawn flag when the timer loops back
    if (timerProgress < 0.1f) {
        hasSpawnedThisCycle = false;
    }

    // Update all enemies
    for (auto& enemy : enemies) {
        enemy->update(dt);
    }
}
