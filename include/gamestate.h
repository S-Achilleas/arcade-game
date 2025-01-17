#pragma once
#include <string>
#include "sgg/graphics.h"
#include "timer.h"

class GameState {
    std::string asset_path = "assets/";
    float canvas_width = 12.0f;
    float canvas_height = 10.0f;
    bool menu_skipped = false;
    bool playerDead = false;

    Timer pauseTimer = Timer(0.5f);
    graphics::Brush pause_brush;
    bool game_paused = false;

    static GameState* unique_instance;
    GameState();

    class Player* player = nullptr;
    class Level* current_level = nullptr;

public:
    void skipped_menu(bool value) { menu_skipped = value; }
    bool debugging = false;

    void init();
    void draw();
    void update(float dt);

    static GameState *getInstance();
    ~GameState() = default;

    float getCanvasWidth(){return canvas_width;}
    float getCanvasHeight(){return canvas_height;}
    std::string getAssetDir();
    std::string getFullAssetPath(const std::string& asset_name);

    class Player* getPlayer(){return player;}
    class Level* getLevel() { return current_level; }
};

