#include "ObjectWithMovement.h"
#include "timer.h"

class Projectile : public ObjectWithMovement {
	float dir;
	Timer activeTime;
public:
	graphics::Brush projectile_brush;
	Projectile(float x, float y, float w, float h, bool left);
	void update(float dt) override;
	void init() override;
	void draw() override;
	Timer getactiveTime() { return activeTime; }
	~Projectile() = default;
};
