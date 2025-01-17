#include "ObjectWithMovement.h"
#include "timer.h"

class Projectile : public ObjectWithMovement {
	bool spawnedLeft;
	float dir;
	Timer activeTime;
	graphics::Brush brush_debug;
	graphics::Brush projectile_brush_left;
	graphics::Brush projectile_brush_right;
public:

	bool operator==(const Projectile& other) const {
		return id == other.id;
	}
	graphics::Brush projectile_brush;
	Projectile(float x, float y, float w, float h, bool left);
	void update(float dt) override;
	void init() override;
	void draw();
	Timer getactiveTime() { return activeTime; }
	float getX() { return m_pos_x;}
	~Projectile() = default;
};
