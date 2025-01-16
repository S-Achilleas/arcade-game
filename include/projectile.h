#include "ObjectWithMovement.h"
#include "timer.h"

class Projectile : public ObjectWithMovement {
	float dir;
	Timer activeTime;
public:

	bool operator==(const Projectile& other) const {
		return id == other.id;
	}
	graphics::Brush projectile_brush;
	Projectile(float x, float y, float w, float h, bool left);
	void update(float dt) override;
	void init() override;
	void draw(bool facing_left);
	Timer getactiveTime() { return activeTime; }
	float getX() { return m_pos_x;}
	~Projectile() = default;
};
