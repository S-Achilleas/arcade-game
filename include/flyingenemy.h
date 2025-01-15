#pragmae once
#include "enemy.h"
class FlyingEnemy : public Enemy {
public:
    FlyingEnemy(bool r);
    void init() override;
    void update(float dt) override;
    void draw() override;
};