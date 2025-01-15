#include "platform.h"
#include "gamestate.h"
#include "my_stdio.h"
#include <iostream>

std::vector<Platform> Platform::platforms;
graphics::Brush Platform::platform_brush;
graphics::Brush Platform::platform_brush_debug;

void Platform::platformInitHandler(Platform platform) {
	Platform::platforms.push_back(platform);
}

void Platform::platformBrushInit()
{
	Platform::platform_brush.outline_opacity = 1.0f;
	Platform::platform_brush.fill_opacity = 1.0f;
	SETCOLOR(Platform::platform_brush.outline_color, 0.0f, 0.0f, 1.0f);

	Platform::platform_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(Platform::platform_brush_debug.fill_color, 0.2f, 1.0f, 0.2f);
	SETCOLOR(Platform::platform_brush_debug.outline_color, 0.3f, 1.0f, 0.3f);
}

void Platform::drawPlatform(int i) {
	Platform& current = Platform::platforms[i];
	float x = current.m_pos_x - current.offset_x;
	float y = current.m_pos_y - current.offset_y;
	float w = current.m_width - current.width_offset;
	float h = current.m_height - current.height_offset;
	Platform::platform_brush.texture = current.state->getFullAssetPath(current.image_name);

	graphics::drawRect(x, y, w, h, Platform::platform_brush);
	if (current.state->debugging) {
		graphics::drawRect(current.m_pos_x, current.m_pos_y,
			current.m_width, current.m_height, Platform::platform_brush_debug);
	}
}

Platform::Platform(float dpos_x, float dpos_y, float dwidth, 
	float dheight, std::string imageName, float offsetX, 
	float offsetY, float offset_width, float offset_height)
{
	offset_x = offsetX; offset_y = offsetY;
	width_offset = offset_width; height_offset = offset_height;

	m_pos_x = dpos_x + offsetX; m_pos_y = dpos_y + offsetY;
	m_width = dwidth + offset_width; m_height = dheight + offset_height;
}

void Platform::platformDisplayHandler() {
	for (int i = 0; i < platforms.size(); i++)
	{
		drawPlatform(i);
	}
}

std::vector<Platform> Platform::getPlatforms() {
	return platforms;
}