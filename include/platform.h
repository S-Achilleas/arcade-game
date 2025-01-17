#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include <vector>

class Platform : public GameObject, public Box
{
	static std::vector<Platform> platforms;
	std::string image_name;

	float offset_x;
	float offset_y;
	float height_offset;
	float width_offset;

	static void drawPlatform(int i);

	
	static graphics::Brush platform_brush_debug;

public:
	/*
	To make a platform use:
	Platform::platformInitHandler(Platform(float image_pos_x, float image_pos_y, 
		float image_width, float image_height, string png, float image_x_offset, 
		float image_y_offset, float image_width_offset, float image_height_offset));
	*/
	Platform(float mpos_x, float mpos_y, float mwidth,
		float mheight, std::string IN, float offset_x = 0.0f,
		float offset_y = 0.0f, float offset_width = 0.0f, float offset_height = 0.0f);
	virtual ~Platform() = default; // destructor
	static void platformInitHandler(Platform platform);
	static void platformBrushInit();
	static graphics::Brush platform_brush;

	void static platformDisplayHandler();
	std::vector<Platform> getPlatforms();
};
