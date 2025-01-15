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
        graphics::preloadBitmaps(getAssetDir()); //move this somewhere it loads only once
        current_level = new main_menu();
    }
    else
    {
        player = new Player("Player");
        player->init();
        current_level = new Level();
    }

    graphics::setFont(getFullAssetPath("ARCADECLASSIC.ttf")); // default font
    pauseTimer.start();
    current_level->init();
}

void GameState::update(float dt) {
    if (dt > 500) return;

    if (graphics::getKeyState(graphics::SCANCODE_P) 
        && float(pauseTimer)==1 && menu_skipped)
    {
        pauseTimer.start();
        if (game_paused) { game_paused = false; pause_brush.fill_opacity = 0.0f; }
        else { game_paused = true; pause_brush.fill_opacity = 1.0f; }
    }
    if (game_paused) 
    { 
        if (graphics::getKeyState(graphics::SCANCODE_M)) {
            game_paused = false;
            menu_skipped = false;
            GameState::init();
        }
        return; 
    }

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
    if (game_paused) 
    { 
        graphics::drawText(2.0f, getCanvasHeight() / 2.0f - 1.0f, 1.0f,
            "Game is on Pause", pause_brush);
        graphics::drawText(1.0f, getCanvasHeight() / 2.0f + 2.0f, 0.7f,
            "Press M to return to main menu", pause_brush);
        return; //remove this if you want continue drawing on pause
    }
    current_level->draw();
}
