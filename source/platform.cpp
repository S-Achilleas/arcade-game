#include "platform.h"
#include "gamestate.h"
#include "my_stdio.h"
#include <iostream>

void Platform::platformInitHandler() {
	platforms.push_back(Box(pos_x, pos_y, width, height));

	platform_names.push_back(image_name);

	platform_brush.outline_opacity = 1.0f;
	platform_brush.fill_opacity = 1.0f;
	SETCOLOR(platform_brush.outline_color, 0.0f, 0.0f, 1.0f);

	platform_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(platform_brush_debug.fill_color, 0.2f, 1.0f, 0.2f);
	SETCOLOR(platform_brush_debug.outline_color, 0.3f, 1.0f, 0.3f);
}

void Platform::drawPlatform(int i) {
	Box& box = platforms[i];
	float x = box.m_pos_x;
	float y = box.m_pos_y;
	float w = box.m_width;
	float h = box.m_height;
	platform_brush.texture = state->getFullAssetPath(platform_names[i]);

	graphics::drawRect(x, y, w, h, platform_brush);
	if (state->debugging) {
		graphics::drawRect(x, y, w, h, platform_brush_debug);
	}
}

void Platform::platformDisplayHandler() {
	for (int i = 0; i < platforms.size(); i++)
	{
		drawPlatform(i);
	}
}

void Platform::addPlatform(float x, float y, float w, float h, std::string IN) {
	pos_x = x; pos_y = y; width = w; height = h; image_name = IN;
	Platform::platformInitHandler();
}

std::vector<Box> Platform::getPlatforms() {
	return platforms;
}