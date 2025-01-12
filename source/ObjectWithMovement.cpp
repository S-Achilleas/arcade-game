#include "ObjectWithMovement.h"
#include "sgg/graphics.h"

void ObjectWithMovement::draw() {
    if (walkCount > 90) {
        walkCount = 0;
    }
    if(facing_left) {
        my_brush.texture = run_array_left[walkCount/10];
        graphics::drawRect(m_pos_x, m_pos_y, width, height, my_brush);
        walkCount++;
        walking = false;
    }else {
        my_brush.texture = run_array_right[walkCount/10];
        graphics::drawRect(m_pos_x, m_pos_y, width, height, my_brush);
        walkCount++;
        walking = false;
    }
}