#include "skeleton.h"
#include "gamestate.h"
#include "animation.h"
#include "ObjectWithMovement.h";
#include "player.h"
#include <cmath>


//Class static definitions
std::vector<std::string> Skeleton::right_assets = {};
std::vector<std::string> Skeleton::left_assets = {};
std::vector<std::string> Skeleton::right_attack_assets = {};
std::vector<std::string> Skeleton::left_attack_assets = {};
std::vector<std::string> Skeleton::sproj_assets = {};
graphics::Brush Skeleton::sprojBrush = {};
//Static definitions end



Skeleton::Skeleton(bool r) : Enemy(r) {
    my_animation = new Animation(false, right_assets, left_assets,idr,idl,right_attack_assets,left_attack_assets);
    m_height = 1.1f;
    m_width = 1.8f;

    sProjAnimation = new Animation(false, sproj_assets);
    Enemy::init();
}
void Skeleton::initt() {
    Skeleton::my_brush.fill_opacity = 1.0f;
    Skeleton::my_brush.outline_opacity = 0.0f;
    Skeleton::sprojBrush.fill_opacity = 1.0f;
    Skeleton::sprojBrush.outline_opacity = 0.0f;
}

void Skeleton::update(float dt) {
    ProjCollisionHandler();
    Enemy::update(dt);
}

void Skeleton::draw() {
    Enemy::draw();
    my_animation -> Animate(d_pos_x, d_pos_y, Skeleton::d_width, 
        Skeleton::d_height, Skeleton::my_brush, facing_left, walking,attacking);

    //projectile draw
    if (Proj){
        int i = 1;
        Skeleton::sprojBrush.texture = std::move(Skeleton::sproj_assets)[2];
        graphics::drawRect(Proj->m_pos_x, Proj->m_pos_y, Proj->m_width/2, 
                           Proj->m_height/2, Skeleton::sprojBrush);
        Proj->drawDebug(enemy_brush_debug, debug_text);
    }
}

Skeleton::~Skeleton() {
    if (my_animation)
        delete my_animation;
    if (Proj)
        delete Proj;
}

float Skeleton::calculateProjectileVelocityX()
{
    float p_x = state->getPlayer()->getPlayerX();
    float p_y = state->getPlayer()->getPlayerY();
    Proj->m_pos_x = m_pos_x;
    Proj->m_pos_y = m_pos_y;
    float speed = 0.4f;

    float direction_x = p_x - m_pos_x;
    float direction_y = p_y - m_pos_y;

    float magnitude = std::sqrt(direction_x * direction_x + direction_y * direction_y);

    float velocity_x = (direction_x / magnitude);

    return (direction_x / magnitude) * speed;
}

float Skeleton::calculateProjectileVelocityY()
{
    float p_x = state->getPlayer()->getPlayerX();
    float p_y = state->getPlayer()->getPlayerY();
    Proj->m_pos_x = m_pos_x;
    Proj->m_pos_y = m_pos_y;
    float speed = 0.4f;

    float direction_x = p_x - m_pos_x;
    float direction_y = p_y - m_pos_y;

    float magnitude = std::sqrt(direction_x * direction_x + direction_y * direction_y);

    float velocity_y = (direction_y / magnitude);

    return velocity_y * speed;
}

void Skeleton::ProjCollisionHandler()
{
    if (Proj) {
        Proj->m_pos_x += projVelX;
        Proj->m_pos_y += projVelY;
        checkPlayerProjCollision();
        if (Proj->m_pos_y < -12.0f) {
            delete Proj;
            Proj = nullptr;
        }
    }
    if (state->getPlayer()->shouldShootProj()) {
        if (Proj)
            delete Proj;
        Proj = new ObjectWithMovement();
        projVelX = calculateProjectileVelocityX();
        projVelY = calculateProjectileVelocityY();
    }
}

void Skeleton::checkPlayerProjCollision()
{
    Player* player = state->getPlayer();
    if (Proj->intersect(*player)) {
        player->platformColToggle(false);
    }
}

void Skeleton::playSound() {
    graphics::playSound("assets/music/skelton_s.wav",0.3f);
}