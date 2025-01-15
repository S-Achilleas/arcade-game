#pragmae once
#include "enemy.h"
class Goblin : public Enemy {
    bool side;
public:
    Goblin(bool r);
    void init() override;
    void update(float dt) override;
    void draw() override;
};
