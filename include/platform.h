#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include <vector>

class Platform : public GameObject, public Box
{
	static std::vector<Platform> platforms;
	std::string image_name;
	float pos_x = 0.0f;
	float pos_y = 0.0f;
	float height = 0.0f;
	float width = 0.0f;

	float offset_x;
	float offset_y;
	float height_offset;
	float width_offset;

	static void drawPlatform(int i);

	static graphics::Brush platform_brush;
	static graphics::Brush platform_brush_debug;

public:
	Platform(float mpos_x, float mpos_y, float mwidth,
		float mheight, std::string IN, float offset_x = 0.0f,
		float offset_y = 0.0f, float offset_width = 0.0f, float offset_height = 0.0f);
	virtual ~Platform() = default; // destructor
	static void platformInitHandler(Platform platform);
	static void platformBrushInit();

	void static platformDisplayHandler();
	std::vector<Platform> getPlatforms();
};
