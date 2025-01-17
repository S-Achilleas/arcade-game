#include "animation.h"
#include "sgg/graphics.h"
#include "gameobject.h"
#include "gamestate.h"
#include "player.h"

Animation::Animation(bool p,std::vector<std::string> rr,
                     std::vector<std::string> rl,
                     std::vector<std::string> idr,
                     std::vector<std::string> idl,
                     std::vector<std::string> ar,
                     std::vector<std::string> al)
    : player(p),run_right(std::move(rr)),
      run_left(std::move(rl)),
      idle_right(std::move(idr)),
      idle_left(std::move(idl)),
      attack_right(std::move(ar)),
      attack_left(std::move(al)){}

void Animation::Animate(float x , float y,float w,float h,graphics:: Brush b,bool facing , bool walking,bool attacking) {
    if(walking && !attacking) {
        if (walkCount > run_left.size() *5 -1) {
            walkCount = 0;
        }
        if(facing) {
            b.texture = run_left[walkCount/5];
            graphics::drawRect(x, y, w, h, b);
            walkCount++;
            if (player)
                state -> getPlayer() -> setWalking(false);
        }else {
            b.texture = run_right[walkCount/5];
            graphics::drawRect(x, y, w ,h, b);
            walkCount++;
            if (player)
                state -> getPlayer() -> setWalking(false);
        }
    }else if (!attacking) {
        if (idleCount > idle_left.size()*5 -1)
            idleCount = 0;

        if(facing) {
            b.texture = idle_left[idleCount/5];
            graphics::drawRect(x, y, w, h, b);
            idleCount++;
        }else {
            b.texture = idle_right[idleCount/5];
            graphics::drawRect(x, y, w, h, b);
            idleCount++;
        }

    }else {
        if (attackCount > attack_left.size()*5 -1)
            attackCount = 0;

        if(facing) {
            b.texture = attack_left[attackCount/5];
            graphics::drawRect(x, y, w, h, b);
            attackCount++;
            if (player)
                state -> getPlayer() -> setWalking(false);
        }else {
            b.texture = attack_right[attackCount/5];
            graphics::drawRect(x, y, w ,h, b);
            attackCount++;
            if (player)
                state -> getPlayer() -> setWalking(false);
        }
    }
}

