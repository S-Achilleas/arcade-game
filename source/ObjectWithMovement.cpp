#include "ObjectWithMovement.h"
#include "gamestate.h"
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
}

void ObjectWithMovement::drawDebug(graphics::Brush brush, graphics::Brush text) {
    {
        if (state->debugging) {
            //draw hitbox
            graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, brush);

            //draw text: position
            graphics::drawText(m_pos_x - 0.3f, m_pos_y - 1.2f, 0.4f, "X " + std::to_string(m_pos_x)
                + "  Y " + std::to_string(m_pos_y) + "  ID " + std::to_string(id) + ")", text);
        }
    }
}