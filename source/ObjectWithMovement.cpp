#include "ObjectWithMovement.h"

#include "animation.h"
#include "healthbar.h"
#include "sgg/graphics.h"

void ObjectWithMovement::hbp_adj(float d_pos_x, float d_pos_y, float offset_x, float offset_y) {
    m_pos_x = d_pos_x + offset_x;
    m_pos_y = d_pos_y + offset_y;
}

void ObjectWithMovement::hb_adj(float width, float height) {
    m_height = height;
    m_width = width;
}

bool ObjectWithMovement::isDead() {
    return my_health->getHealth()== 0;
}

ObjectWithMovement::~ObjectWithMovement() {
    if (my_health) {
        delete my_health;
    }
    if (my_animation) {
        delete my_animation;
    }
}
