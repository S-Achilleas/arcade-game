#include "player.h"

#include <iostream>
#include <ostream>

#include "sgg/graphics.h"
#include "gamestate.h"
#include "gameobject.h"
#include "math.h"
#include "level.h"
#include "my_stdio.h"
#include "healthbar.h"
#include "animation.h"
#include <iostream>


void Player::init() 
{
    //player draw hitbox pos_x, pos_y
    // & its width, height
    d_pos_x = 5.5f; d_pos_y = 8.5f;
    d_width = 3.0f; d_height = 4.3f;

    //player hitbox width & height
    hb_adj(1.0f, 1.8f);
    //feet hitbox width & height
    playerfeet->hb_adj(0.4f, 0.15f);
    projectileCooldownTimer = Timer(0.2f, Timer::TIMER_ONCE);
    projectileCooldownTimer.start();
    
    my_animation = new Animation(true, 
        graphics::preloadBitmaps(state->getFullAssetPath("Samurai/run_right")),
        graphics::preloadBitmaps(state->getFullAssetPath("Samurai/run_left")), 
        graphics::preloadBitmaps(state->getFullAssetPath("Samurai/idle_right")),
        graphics::preloadBitmaps(state->getFullAssetPath("Samurai/idle_left")));

    my_health = new HealthBar(9, 10.0f, 0.5f, "healthbars/green_health", 0.6f, 3.2f);

    brushesInit();
    resetPlatformCollision = Timer(7.0f, Timer::TIMER_ONCE);

}

void Player::update(float dt) 
{
    playerMovement(dt);

    //hitbox offsets
    hbp_adj(d_pos_x, d_pos_y, 0, 0.6f);
    //feet hitbox offsets
    playerfeet->hbp_adj(m_pos_x, m_pos_y, 0.0f, 0.8f);

    projectileHandler(dt);
    skeletonProjectilePlayer(dt);
}

void Player::draw() 
{
    //Draw player
    my_animation -> Animate(d_pos_x, d_pos_y, d_width, d_height, my_brush,facing_left,walking);
    my_health -> draw();
    //Draw projectiles
    for (int i = 0; i < projectiles.size(); i++)
    {
        (projectiles)[i].draw();
    }
    graphics::drawText(0.3f, 0.8f, 1.0f, std::to_string(score), text);
    if (!collideWithPlatforms) {
        graphics::drawText(d_pos_x, m_pos_y - 0.5f, 0.7f, std::to_string(9-(int)(resetPlatformCollision*10)), text);
        graphics::drawText(d_pos_x - 2.0f, m_pos_y - 1.2f, 0.5f, "Cant use platforms!", text);
    }

    drawDebug();
}

void Player::playerMovement(float dt) 
{
    float delta_time = dt / 1000.0f;
    float move = 0.0f;

    //Keyboard input check
    if (graphics::getKeyState(graphics::SCANCODE_A))
    {
        move -= 1.0f;
        walking = true;
        facing_left = true;
    }

    if (graphics::getKeyState(graphics::SCANCODE_D))
    {
        move += 1.0f;
        walking = true;
        facing_left = false;
    }

    // X axis change
    m_vx = std::min(max_velocity, m_vx + delta_time * move * accel_horizontal);
    m_vx = std::max(-max_velocity, m_vx);

    m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));

    if (fabs(m_vx) < 0.01f) {
        m_vx = 0.0f;
    }

    // Prevents hitbox from getting out of canvas
    if (m_pos_x > 0.4 && m_vx < 0 ||
        m_pos_x < state->getCanvasWidth() - 0.4 && m_vx >0)
        // draw pos_x change
        d_pos_x += delta_time * m_vx;


    // Y axis change
    isOnGround = (d_pos_y == 8.5f);
    // Jump only if playerfeet collide with a platform or player is on ground
    if (checkPlatformCollision() || isOnGround) {
        m_vy = 0.0f; // reset vertical velocity when on the ground
        if (graphics::getKeyState(graphics::SCANCODE_W)) {
            m_vy = -accel_vertical; // Jump
        }
    }
    else {
        m_vy += delta_time * gravity;
    }
    // draw pos_y change, where 8.5f is the ground
    d_pos_y = std::min(d_pos_y + m_vy * delta_time, 8.5f);
}

//Returns true if player feet collide with a platform 
bool Player::checkPlatformCollision() 
{
    if (collideWithPlatforms){
        Platform::platform_brush.fill_opacity = 1.0f;
        for (auto& box : state->getLevel()->platform_loader->getPlatforms())
        {
            //platform to feet offset
            float offset = playerfeet->intersectDown(box);
            // if offset (!=0) then there is a collision with offset to feet = offset
            // if m_vy>=0 the player is falling (y accelaration down)
            if (offset && m_vy >= 0)
            {
                d_pos_y += offset + 0.000001f;
                return true;
            }
        }
    }
    else 
    {
        Platform::platform_brush.fill_opacity = 0.4;
    }
    return false;
}

//Spawns, updates and kills spawned projectiles
void Player::projectileHandler(float dt)
{

    if (graphics::getKeyState(graphics::SCANCODE_SPACE))
    {
        float timerValue = projectileCooldownTimer; //random fix
        if (projectiles.size() < 5 && !projectileCooldownTimer.isRunning()) {
            projectiles.push_back(Projectile(m_pos_x, m_pos_y, 1.0f, 1.0f, facing_left));
            graphics::playSound("assets/music/samurai_s.wav",0.3);
            projectileCooldownTimer = Timer(0.2f, Timer::TIMER_ONCE);
            projectileCooldownTimer.start();
        }
    }

    //projectile update
    for (int i = 0; i < projectiles.size(); i++) {
        (projectiles)[i].update(dt);

        //projectile kill when out of canvas
        if (projectiles[i].getX() <= 0.0f || projectiles[i].getX() > 12.0f) {
            projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectiles[i]), projectiles.end());
        }
    }
}

//Initializes player brushes
void Player::brushesInit()
{
    //text brushes and player brush init
    text.fill_opacity = 1.0f;
    my_brush.fill_opacity = 1.0f;
    my_brush.outline_opacity = 0.0f;

    //debug brush init
    player_brush_debug.fill_opacity = 0.1f;
    SETCOLOR(player_brush_debug.fill_color, 1.0f, 0.1f, 0.1f);
    SETCOLOR(player_brush_debug.outline_color, 1.0f, 0.2f, 0.2f);
}

//Draws debug elements
void Player::drawDebug()
{
    if (state->debugging) { 
        ObjectWithMovement::drawDebug(player_brush_debug, text);
        //draw feet hitbox
        graphics::drawRect(playerfeet->m_pos_x, playerfeet->m_pos_y,
            playerfeet->m_width, playerfeet->m_height, playerfeet->returnbrush());

        //print projectiles GameObject::ID (maybe move this to projectile draw)
        for (int i = 0; i < projectiles.size(); i++)
            graphics::drawText(projectiles[i].m_pos_x, projectiles[i].m_pos_y, 0.4f, "ID: " +
                std::to_string(projectiles[i].getID()), text);
    }
}

void Player::skeletonProjectilePlayer(float dt)
{
    if (skeletonShootProj && resetPlatformCollision == 0) {
        skeletonShootProj = false;
        resetPlatformCollision.start();
    }
        skeletonShootProj = false;
    if (float(timeNotOnGround) == 1) {
        skeletonShootProj = true;
        resetPlatformCollision.stop();
    }

    if (!isOnGround && !timeNotOnGround.isRunning())
        timeNotOnGround.start();
    else if (isOnGround && timeNotOnGround.isRunning()) {
        timeNotOnGround.stop();
    }

    float cv = resetPlatformCollision; //random fix
    if (!resetPlatformCollision.isRunning()) //needs fixing
    {
        platformColToggle(true);
        if (resetPlatformCollision!=0)
            resetPlatformCollision = Timer(7.0f, Timer::TIMER_ONCE);
    }
}