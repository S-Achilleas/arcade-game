#include "level.h"
#include "player.h"
#include "gamestate.h"
#include "platform.h"
#include "enemy.h"
#include "skeleton.h"
#include "flyingenemy.h"
#include "goblin.h"
#include <random>
#include "healthbar.h"

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

    Platform::platformInitHandler(Platform(5.5f, 3.5f, 2.0f, 0.4f, "tile.png")); // platform object
    Platform::platformInitHandler(Platform(8.5f, 5.0f, 2.0f, 0.4f, "tile.png"));
    Platform::platformInitHandler(Platform(2.5f, 5.0f, 2.0f, 0.4f, "tile.png"));
    Platform::platformInitHandler(Platform(6.0f, 6.5f, 2.0f, 0.4f, "tile.png"));
    Platform::platformInitHandler(Platform(2.0f, 8.0f, 2.0f, 0.4f, "tile.png"));
    Platform::platformInitHandler(Platform(10.0f, 8.0f, 2.0f, 0.4f, "tile.png"));

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

void Level::checkEnemiesCollisions() {
    for (auto& enemy :  enemies) {
        if (state->getPlayer() -> intersect(*(enemy))) {
            if (enemy -> canAttack()) {
                enemy -> setAttacking(true);
                enemy -> playSound();
                state -> getPlayer() -> getHealthBar() -> hit(1);
            }
        }
        else {
            enemy->setAttacking(false);
        }
    }
}


void Level::update(float dt) {
    // Update player
    if (state->getPlayer()->isActive()) {
        state->getPlayer()->update(dt);
    }
    checkEnemiesCollisions();

    updateEnemies(dt);

    checkCollisionProjectiles();
}

void Level::enemyInit()
{
    //Skeleton init
    Skeleton::right_assets = graphics::preloadBitmaps(state->getFullAssetPath("skeleton/walk/right"));
    Skeleton::left_assets = graphics::preloadBitmaps(state->getFullAssetPath("skeleton/walk/left"));
    Skeleton::right_attack_assets = graphics::preloadBitmaps(state->getFullAssetPath("skeleton/attack/right"));
    Skeleton::left_attack_assets = graphics::preloadBitmaps(state->getFullAssetPath("skeleton/attack/left"));
    Skeleton::sproj_assets = graphics::preloadBitmaps(state->getFullAssetPath("skeleton/proj"));
    Skeleton::initt();

    //goblin init
    Goblin::right_assets = graphics::preloadBitmaps(state->getFullAssetPath("goblin/run/right"));
    Goblin::left_assets = graphics::preloadBitmaps(state->getFullAssetPath("goblin/run/left"));
    Goblin::right_attack_assets = graphics::preloadBitmaps(state->getFullAssetPath("goblin/attack/right"));
    Goblin:: left_attack_assets = graphics::preloadBitmaps(state->getFullAssetPath("goblin/attack/left"));
    Goblin::initt();

    //flyingenemy init
    FlyingEnemy::right_assets = graphics::preloadBitmaps(state->getFullAssetPath("flyingEye/Flight/right"));
    FlyingEnemy::left_assets = graphics::preloadBitmaps(state->getFullAssetPath("flyingEye/Flight/left"));
    FlyingEnemy::right_attack_assets = graphics::preloadBitmaps(state->getFullAssetPath("flyingEye/attack/Right"));
    FlyingEnemy:: left_attack_assets = graphics::preloadBitmaps(state->getFullAssetPath("flyingEye/attack/Left"));
    FlyingEnemy::initt();
}

void Level::checkCollisionProjectiles()
{
    std::vector<Projectile>* playerProjectiles = state->getPlayer()->getProjectiles();

    //if no projectiles dont loop
    if (playerProjectiles->empty()) {
        return;
    }

    // loop through all enemies
    for (auto& enemy : enemies) {
        std::vector<Projectile> remainingProjectiles;
        // loop through all projectiles
        for (auto& projectile : *playerProjectiles) {
            if (enemy->intersect(projectile)) { 
                // if there is collision reduce enemy's health
                enemy->getHealthBar()->hit(1);
                graphics::playSound("assets/music/enemy_hit.wav",0.3);
                // dont add this projectile to the remaining list
            }
            else {
                //keep projectiles that did not collide
                remainingProjectiles.push_back(projectile);
            }
        }
        //update projectiles list to only include the remaining ones
        *playerProjectiles = remainingProjectiles;
    }
}

void Level::updateEnemies(float dt) {
    float timerProgress = spawn_timer;

    if (timerProgress >= 0.9f && !hasSpawnedThisCycle && enemies.size() < 7) {
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
        [this](Enemy* enemy) {
            if (enemy->isDead()) {
                delete enemy;
                state->getPlayer()->setScoreUp();
                return true;
            }
            return false;
        }),
        enemies.end());
}