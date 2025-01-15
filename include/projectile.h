
#include "ObjectWithMovement.h"

class Projectile : public ObjectWithMovement {
public:
	graphics::Brush projectile_brush;
	Projectile(float x, float y, float w, float h);
	void update(float dt) override;
	void init() override;
	void draw() override;
};
