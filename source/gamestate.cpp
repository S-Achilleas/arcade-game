#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "sgg/graphics.h"
#include <thread>
#include <chrono>
#include "main_menu.h"


GameState* GameState::unique_instance = nullptr;

GameState::GameState() {
    if (player)
        delete player;
    if (current_level)
        delete current_level;
}

GameState* GameState::getInstance() {
    if (unique_instance==nullptr)
        unique_instance = new GameState();
    return unique_instance;
}

std::string GameState::getAssetDir() {
    return asset_path;
}

std::string GameState::getFullAssetPath(const std::string &asset_name) {
    return asset_path + asset_name;
}

void GameState::init() {
    if (!menu_skipped)
    {
        graphics::preloadBitmaps(getAssetDir());
        current_level = new main_menu();
    }
    else
    {
        player = new Player("Player");
        player->init();
        current_level = new Level();
    }
    current_level->init();
}

void GameState::update(float dt) {
    if (dt>500)
        return;

    float sleep_time = std::max(0.0f, 17.0f - dt);

    std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));

    if (!current_level) return;
    current_level->update(dt);

    debugging = graphics::getKeyState(graphics::SCANCODE_0); //debug key
}

void GameState::draw() {
    /* //GameState should draw even when
    if (!player) //there is not a player
        return; // eg main menu
        */
    current_level->draw();
}
