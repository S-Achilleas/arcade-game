#include "level.h"
#include "player.h"
#include "gamestate.h"
#include "platform.h"
#include "enemy.h"
#include "skeleton.h"
#include "flyingenemy.h"
#include "goblin.h"
#include <random>

Level::Level(const std::string &name) {
}

Level::~Level() {
    if (platform_loader) {
        delete platform_loader;
    }
    for (auto* enemy : enemies) {
        delete enemy;
    }
}


void Level::init() {
    graphics::playMusic(state->getFullAssetPath("samurai.mp3"), 0.4f); //music

    brush_background.outline_opacity = 0.0f;
    brush_background.texture = state->getFullAssetPath("background.png");
    spawn_timer.start();



    Platform::platformBrushInit();
    Platform::platformInitHandler(Platform(7.0f, 7.8f, 2.0f, 0.4f, "tile.png")); // platform object

    enemyInit();

};

void Level::draw() {

    graphics::drawRect(state->getCanvasWidth()/2.0f, state-> getCanvasHeight()/2.0f, 
        state->getCanvasWidth(), state-> getCanvasHeight(), brush_background);

   Platform::platformDisplayHandler();

    if (state ->getPlayer()->isActive())
        state ->getPlayer() ->draw();

    for (auto& enemy  : enemies) {
        enemy->draw();
    }
}


void Level::update(float dt) {
    // Update player
    if (state->getPlayer()->isActive()) {
        state->getPlayer()->update(dt);
    }

    float timerProgress = spawn_timer;

    if (timerProgress >= 0.9f && !hasSpawnedThisCycle && enemies.size() < 6) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 2);

        int enemyType = dis(gen);
        Enemy* enemy_pointer = nullptr;

        switch (enemyType) {
            case 0:
                enemy_pointer = new Skeleton(rand() % 2 == 0);
                break;
            case 1:
                enemy_pointer = new Goblin(rand() % 2 == 0);
                break;
            case 2:
                enemy_pointer = new FlyingEnemy(rand() % 2 == 0);
                break;
        }

        if (enemy_pointer) {
            enemies.push_back(enemy_pointer);
            hasSpawnedThisCycle = true;
        }
    }

    if (timerProgress < 0.1f) {
        hasSpawnedThisCycle = false;
    }

    for (auto& enemy : enemies) {
        enemy->update(dt);
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
              [](Enemy* enemy) {
                  if (enemy->isDead()) {
                      delete enemy;
                      return true;
                  }
                  return false;
              }),
              enemies.end());
}

void Level::enemyInit()
{
    //Skeleton init
    Skeleton::right_assets = graphics::preloadBitmaps(state->getFullAssetPath("skeleton/walk/right"));
    Skeleton::left_assets = graphics::preloadBitmaps(state->getFullAssetPath("skeleton/walk/left"));
    Skeleton::init();

    //goblin init
    Goblin::right_assets = graphics::preloadBitmaps(state->getFullAssetPath("goblin/run/right"));
    Goblin::left_assets = graphics::preloadBitmaps(state->getFullAssetPath("goblin/run/left"));
    Goblin::init();

    //flyingenemy init
    FlyingEnemy::right_assets = graphics::preloadBitmaps(state->getFullAssetPath("flyingEye/Flight/right"));
    FlyingEnemy::left_assets = graphics::preloadBitmaps(state->getFullAssetPath("flyingEye/Flight/left"));
    FlyingEnemy::init();
}
