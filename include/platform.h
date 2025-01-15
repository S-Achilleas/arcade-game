#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include <vector>

class Platform : public GameObject
{
	std::vector<std::string> platform_names;
	std::vector<Box> platforms;
	std::string image_name;
	float pos_x = 0.0f;
	float pos_y = 0.0f;
	float height = 0.0f;
	float width = 0.0f;
	void platformInitHandler();
	void drawPlatform(int i);

	graphics::Brush platform_brush;
	graphics::Brush platform_brush_debug;
public:
	Platform() = default; // default constructor
	virtual ~Platform() = default; // destructor

	void platformDisplayHandler();
	void addPlatform(float x, float y, float w, float h, std::string IN);
	std::vector<Box> getPlatforms();
};
