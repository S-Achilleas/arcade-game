#include "animation.h"
#include "sgg/graphics.h"
#include "gameobject.h"
#include "gamestate.h"
#include "player.h"

Animation::Animation(std::vector<std::string> rr,
                     std::vector<std::string> rl,
                     std::vector<std::string> id,
                     std::vector<std::string> ar,
                     std::vector<std::string> al)
    : run_right(std::move(rr)),
      run_left(std::move(rl)),
      idle(std::move(id)),
      attack_right(std::move(ar)),
      attack_left(std::move(al)){}

void Animation::Animate(float x , float y,float w,float h,graphics:: Brush b,bool facing , bool walking) {
    if(walking) {
        if (walkCount > run_left.size() *5 -1) {
            walkCount = 0;
        }
        if(facing) {
            b.texture = run_left[walkCount/5];
            graphics::drawRect(x, y, w, h, b);
            walkCount++;
            state -> getPlayer() -> setWalking(false);
        }else {
            b.texture = run_right[walkCount/5];
            graphics::drawRect(x, y, w ,h, b);
            walkCount++;
            state -> getPlayer() -> setWalking(false);
        }
    }else{if (idleCount > idle.size()*5 -1)
        idleCount = 0;

        // todo left facing idle

        b.texture = idle[idleCount/5];
        graphics::drawRect(x, y, w, h, b);
        idleCount++;
    }
}

