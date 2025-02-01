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
     - Attack cooldowns via `Timer` class 
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
# Class Analysis  
This document provides a detailed breakdown of all classes in the project, their responsibilities, and interactions.  

---

## Core Framework Classes  

### **1. `GameObject`**  
- **Role**: Base class for all entities in the game.  
- **Key Features**:  
  - Tracks `active` state and unique `id` for object management.  
  - Virtual methods (`update()`, `draw()`, `init()`) for polymorphism.  
- **Usage**: Inherited by `Player`, `Enemy`, `Platform`, `Projectile`, etc.  

---

### **2. `GameState` (Singleton)**  
- **Role**: Central hub for game state management.  
- **Key Features**:  
  - Manages `Player`, `Level`, and `main_menu` transitions.  
  - Handles pausing (`pauseTimer`), debugging flags, and score retention.  
  - Coordinates asset paths (e.g., `getFullAssetPath()`).  

---

## Physics & Collision  

### **3. `Box`**  
- **Role**: Axis-aligned bounding box (AABB) for collision detection.  
- **Key Methods**:  
  - `intersect()`: Checks overlap between two boxes.  
  - `intersectDown()`: Resolves vertical collisions (e.g., landing on platforms).  
  - `intersectSideways()`: Resolves horizontal collisions.  
- **Usage**: Inherited by `ObjectWithMovement` and `Platform`.  

---

### **4. `ObjectWithMovement`**  
- **Role**: Combines `GameObject` and `Box` for physics-based entities.  
- **Key Features**:  
  - Manages velocity (`m_vx`, `m_vy`), gravity, acceleration.  
  - Hitbox adjustment methods (`hb_adj()`, `hbp_adj()`).  
  - Debug rendering for hitboxes (`drawDebug()`).  
- **Inherited By**: `Player`, `Enemy`, `Projectile`.  

---

## Player & Combat  

### **5. `Player`**  
- **Role**: Playable character with combat and movement logic.  
- **Key Features**:  
  - **Movement**: WASD controls with acceleration/friction (`playerMovement()`).  
  - **Combat**: Throws `Projectile` objects with cooldowns (`projectileHandler()`).  
  - **Health**: Managed by `HealthBar`; god mode toggles invincibility.  
  - **Collision**: Platform interaction via `checkPlatformCollision()`.  
- **Dependencies**: Uses `Animation` for sprite cycling.  

---

### **6. `Projectile`**  
- **Role**: Player’s thrown weapon.  
- **Key Features**:  
  - Directional movement based on `spawnedLeft` flag.  
  - `Timer` for lifespan management (3-second expiry).  
  - Collision detection with enemies (`Level::checkCollisionProjectiles`).  

---

## Enemy System  

### **7. `Enemy` (Base Class)**  
- **Role**: Base for all enemy types.  
- **Key Features**:  
  - **AI**: Patrol/chase logic (`update()`) and attack cooldowns (`attackCooldownTimer`).  
  - **Health**: Linked to `HealthBar` for UI display.  
  - **Derived Classes**:  
    - `Skeleton`: Shoots homing projectiles (`calculateProjectileVelocity`).  
    - `FlyingEnemy`: Vertical pursuit logic.  
    - `Goblin`: Ground-based melee attacks.  

---

### **8. `Skeleton`, `FlyingEnemy`, `Goblin`**  
- **Role**: Specialized enemy behaviors.  
- **Key Differences**:  
  - **Skeleton**: Ranged attacks with projectile physics.  
  - **FlyingEnemy**: Overrides `update()` for Y-axis interpolation.  
  - **Goblin**: Uses `Animation` for charge attacks.  

---

## Environment & UI  

### **9. `Platform`**  
- **Role**: Static collidable objects.  
- **Key Features**:  
  - Rendered via `platformDisplayHandler()` using preloaded sprites.  
  - Hitbox adjustments for collision resolution.  

---

### **10. `HealthBar`**  
- **Role**: Displays health for players/enemies.  
- **Key Features**:  
  - Preloaded bitmap frames (e.g., `red_health`, `green_health`).  
  - Follows entities with `draw(true, x, y)` or stays fixed.  

---

### **11. `Animation`**  
- **Role**: Manages sprite animations.  
- **Key Features**:  
  - Cycles through frames for idle/run/attack states.  
  - Frame pacing via counters (`walkCount/5` for 5-frame delays).  
  - Used by `Player` and `Enemy` subclasses.  

---

## Utility Classes  

### **12. `Timer`**  
- **Role**: Reusable time-tracking utility.  
- **Key Features**:  
  - Modes: One-shot, looping, ping-pong.  
  - Used for attack cooldowns (`Enemy`), spawn intervals (`Level`), and UI effects.  

---

### **13. `main_menu`**  
- **Role**: Handles main menu UI and transitions.  
- **Key Features**:  
  - Renders text/graphics and detects input (e.g., SPACE to start).  
  - Inherits from `Level` to reuse rendering logic.  

---

## Class Interactions  

1. **Game Loop Flow**:  
   - `GameState` → `Level` → Spawns `Enemy`/`Platform` → `Player` interacts via `Projectile`.  

2. **Collision Resolution**:  
   - `Player`/`Enemy` (via `ObjectWithMovement`) → Check collisions with `Box` → Adjust positions.  

3. **Rendering Pipeline**:  
   - `GameState` → `Level::draw()` → Renders `Platform`, `Enemy`, `Player`, `HealthBar`.  

---

## Key Technical Patterns  

- **Singleton**: `GameState` ensures a single source of truth for game state.  
- **Inheritance**: Polymorphism via `GameObject` allows unified entity management.  
- **Component-Based Design**: Separation of concerns (e.g., `Animation` handles visuals, `Box` handles physics).  

