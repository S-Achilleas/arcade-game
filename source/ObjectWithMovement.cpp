#include "ObjectWithMovement.h"
#include "sgg/graphics.h"

void ObjectWithMovement::draw() {
    if (walkCount > 90) {
        walkCount = 0;
    }
    if(facing_left) {
        my_brush.texture = run_array_left[walkCount/10];
        graphics::drawRect(d_pos_x, d_pos_y, d_width, d_height, my_brush);
        walkCount++;
        walking = false;
    }else {
        my_brush.texture = run_array_right[walkCount/10];
        graphics::drawRect(d_pos_x, d_pos_y, d_width, d_height, my_brush);
        walkCount++;
        walking = false;
    }
}

void ObjectWithMovement::hbp_adj(float d_pos_x, float d_pos_y, float offset_x, float offset_y) {
    m_pos_x = d_pos_x + offset_x;
    m_pos_y = d_pos_y + offset_y;
}

void ObjectWithMovement::hb_adj(float width, float height) {
    m_height = height;
    m_width = width;
}