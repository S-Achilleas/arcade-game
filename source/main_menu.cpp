#include "main_menu.h"
#include "my_stdio.h"

void main_menu::update(float dt)
{
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);
	if ((graphics::getKeyState(graphics::SCANCODE_SPACE) && !killTime.isRunning()) || mouse.button_left_pressed) {
		
		killTime.start();
	}
	if (float(killTime) < 1 && float(killTime) != 0) {
		text.fill_opacity -= 0.03f;
		brush_background.fill_opacity += 0.008;
	}
	else if (float(killTime) == 1){
		main_menu::~main_menu();
		state->skipped_menu(true);
		state->init();
	}
}

void main_menu::init()
{
	graphics::playMusic(state->getFullAssetPath("samurai.mp3"), 0.4f);
	graphics::setFont(state->getFullAssetPath("ARCADECLASSIC.ttf"));
	text.fill_opacity = 1.0f;
	brush_background.outline_opacity = 0.0f;
	brush_background.fill_opacity = 0.3f;
	brush_background.texture = state->getFullAssetPath("background.png");
}

void main_menu::draw()
{
    graphics::drawRect(state->getCanvasWidth() / 2.0f, state->getCanvasHeight() / 2.0f,
        state->getCanvasWidth(), state->getCanvasHeight(), brush_background);
	graphics::drawText(3.5f, state->getCanvasHeight() / 2.0f - 1.0f, 1.0f, "Main Menu", text);
	graphics::drawText(1.0f, state->getCanvasHeight() / 2.0f + 1.0f, 1.0f, "Press Space to start", text);

	graphics::drawText(0.5f, state->getCanvasHeight() / 2.0f + 3.0f, 0.5f, "Movement Keys", text);
	graphics::drawText(0.5f, state->getCanvasHeight() / 2.0f + 3.3f, 0.5f, "W A D", text);
	graphics::drawText(0.5f, state->getCanvasHeight() / 2.0f + 4.0f, 0.5f, "Throw Projectile", text);
	graphics::drawText(0.5f, state->getCanvasHeight() / 2.0f + 4.3f, 0.5f, "Space", text);

	graphics::drawText(8.5f, state->getCanvasHeight() / 2.0f + 3.0f, 0.5f, "Kill Enemies", text);
	graphics::drawText(6.15f, state->getCanvasHeight() / 2.0f + 3.3f, 0.5f, "To increase your score", text);

	graphics::drawText(7.8f, state->getCanvasHeight() / 2.0f + 4.0f, 0.5f, "And dont stay in", text);
	graphics::drawText(6.15f, state->getCanvasHeight() / 2.0f + 4.3f, 0.5f, "platforms for too long", text);
}