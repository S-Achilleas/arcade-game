#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "sgg/graphics.h"

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
    current_level = new Level();
    current_level->init ();

    player = new  Player("Player");
    player->init();

    graphics::preloadBitmaps(getAssetDir());

}

void GameState::update(float dt) {
    if (dt>500)
        return;
    if (!current_level) return;
    current_level->update(dt);
}

void GameState::draw() {
    if (!player)
        return;
    current_level->draw();
}
