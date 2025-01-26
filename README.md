# Arcade Game

An arcade game developed in C++ leveraging the SGG library. This project showcases fundamental game development concepts, including graphics rendering, input handling, and basic game mechanics.
# Samurai Showdown: Edge of the Blade  
*A 2D Action Platformer with Physics-Based Combat and AI-Driven Enemies*  

---

### Core Gameplay  
- **Dynamic Combat**:  
  - Throw katanas (`Projectile` class) with cooldown timers.  
  - Engage enemies with unique attack patterns:  
    - **Skeletons**: Homing projectile attacks (`Skeleton::calculateProjectileVelocity`).  
    - **Goblins**: Melee charge attacks with animation blending.  
    - **Flying Enemies**: Vertical pursuit logic (`FlyingEnemy::update`).  

- **Physics System**:  
  - Velocity-based movement (`m_vx`, `m_vy`) with gravity (`15.0f`) and friction.  
  - Platform collision resolution via `Box::intersectDown` and `Box::intersectSideways`.  

- **Health & UI**:  
  - Health bars (`HealthBar` class) track damage via bitmap frames.  
  - Score system updates on enemy kills (`Player::setScoreUp`).  

---

## Technical Design  
### Key Systems  
1. **Collision Detection**  
   - **AABB Hitboxes**: Managed by the `Box` class with methods for overlap checks (`intersect()`) and positional correction.  
   - **Platform Interaction**: Player feet use offset hitboxes (`playerFeetObj`) for ground detection.  

2. **Enemy AI**  
   - **State Management**:  
     - Patrol/chase logic in `Enemy::update`.  
     - Attack cooldowns via `Timer` class (e.g., `attackCooldownPeriod = 1.0f`).  
   - **Spawn System**:  
     - Procedural enemy spawning in `Level::updateEnemies` (max 7 enemies, 3-second intervals).  

3. **Animation & Rendering**  
   - **Sprite Cycling**: `Animation::Animate` controls frame pacing (`walkCount/5` for 5-frame delays).  
   - **Preloaded Assets**: Sprites loaded via `graphics::preloadBitmaps` on level initialization.  

4. **Game State Flow**  
   - Singleton `GameState` handles:  
     - Pausing (freezes timers via `pauseTimeOffset`).  
     - Menu transitions (`main_menu` class).  
     - Player death/respawn logic.  

---

## Controls  
| Key           | Action                              | Code Reference              |  
|---------------|-------------------------------------|-----------------------------|  
| `A/D`         | Move left/right                     | `Player::playerMovement`    |  
| `W`           | Jump (grounded by platform checks)  | `Player::checkPlatformCollision` |  
| `SPACE`       | Throw projectile                    | `Player::projectileHandler` |  
| `P`           | Pause game                          | `GameState::update`         |  
| `0`           | Toggle debug hitboxes               | `GameState::debugging` flag |  
| `O+L`         | God mode (bypass damage/collision)  | `Player::god` boolean       |  

---

## Code Architecture  
### Critical Classes  
- **Player**:  
  - Manages movement, attacks, and health.  
  - Handles projectile spawning (`std::vector<Projectile>`).  

- **Enemy Hierarchy**:  
  - Base `Enemy` class with overrides:  
    - `Skeleton`: Ranged attacks with projectile physics.  
    - `FlyingEnemy`: Vertical interpolation for flight.  
    - `Goblin`: Melee charge behavior.  

- **Level**:  
  - Coordinates enemy spawning, collisions, and platform rendering.  
  - Uses `std::vector<Enemy*>` for active enemy tracking.  

### Physics Logic  
- **Movement**:  
  // Player::playerMovement snippet  
  m_vx = std::min(max_velocity, m_vx + delta_time * move * accel_horizontal);  
  m_vy += delta_time * gravity; // Apply gravity
