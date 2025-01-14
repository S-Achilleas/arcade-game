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
	float pos_x;
	float pos_y;
	float height;
	float width;

	graphics::Brush platform_brush;
	graphics::Brush platform_brush_debug;
public:
	Platform() = default; // default constructor
	virtual ~Platform() = default; // destructor

	void platformInitHandler();
	void drawPlatform(int i);
	void platformDisplayHandler();
	void addPlatform(float x, float y, float w, float h, std::string IN);
	std::vector<Box> getPlatforms();
};
