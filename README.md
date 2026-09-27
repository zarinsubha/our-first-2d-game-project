# The Last Jade Marquis

## Game Description

**The Last Jade Marquis** is a 2D action-adventure graphics game developed using the **iGraphics** library with **C++**. The game combines player movement, enemy combat, animation, health management, scoring, scrolling backgrounds, level progression, gates, and Jade collection.

The player progresses through three levels. Each level introduces enemies and a different environment. The main objective is to defeat the required enemies, pass through the gates, and finally collect the Jade to complete the game.

## Features

- 3 playable game levels.
- Story, menu, level-select, game-over, and win screens.
- Player movement using keyboard controls.
- Player running and attack animations.
- Enemy idle, running, and attack animations.
- Different enemy types in Levels 2 and 3.
- Enemy health and player health systems.
- Health bar and health display.
- Score system with coin display.
- 5 points are awarded for each defeated enemy.
- Scrolling backgrounds in selected gameplay stages.
- Gate-based level progression.
- Jade collection as the final objective.
- Background music, attack sound, enemy-hit sound, victory sound, and game-over sound.
- Separate stages within the levels.
- Camera-follow system for scrolling gameplay.

## Project Details

- **Game Title:** The Last Jade Marquis
- **Repository:** [our-first-2d-game-project](https://github.com/zarinsubha/our-first-2d-game-project)
- **IDE:** Visual Studio 2013
- **Language:** C++
- **Graphics Library:** iGraphics
- **Platform:** Windows PC
- **Genre:** 2D Action Adventure
- **Screen Resolution:** 1000 × 600

The project uses separate header files for the player, enemy, and environment/gameplay systems. The main source file controls the game states, input handling, asset loading, timers, and overall game flow.

## Game Progression

### Level 1

Level 1 begins with the player fighting a sequence of enemies.

- The player starts with **20 health points**.
- There are **10 enemies** in Level 1.
- The player attacks enemies using the attack action.
- Each defeated enemy gives **5 points**.
- After all 10 enemies are defeated, the player moves to the next stage.
- The player then moves to the door.
- After reaching the door, the player proceeds to the Jade area.
- The player collects the Jade to complete the Level 1 progression.

### Level 2

Level 2 introduces different enemy types and additional stages.

- Level 2 contains **10 enemies**.
- The first **5 enemies** use the first enemy type.
- The next **5 enemies** use the second enemy type.
- The level uses a scrolling background during the enemy stages.
- After defeating all required enemies, the player moves through the gate-related stages.
- The final objective is to reach the Jade area.

Level 2 also supports jumping using the `W` key.

### Level 3

Level 3 is divided into five stages:

1. **Background 1 + First Gate**
2. **Background 2 + First 5 Enemies**
3. **Background 3 + Second Gate**
4. **Background 4 + Second 5 Enemies**
5. **Background 5 + Jade**

The first enemy area contains 5 enemies of the first enemy type. After they are defeated, the player proceeds to the second gate and then enters the second enemy area.

The second enemy area contains another 5 enemies of the second enemy type. After all 10 Level 3 enemies are defeated, the player reaches the final Jade area.

Collecting the Jade completes the game and displays the Win screen.

## How to Run the Project

Make sure you have:

- **Visual Studio 2013**
- **iGraphics Library**
- The complete project files
- The `Images` folder containing the required image assets
- The `Audios` folder containing the required audio files

### Steps

1. Open **Visual Studio 2013**.
2. Open the game project/solution.
3. Make sure the required `.cpp`, `.h`, image, and audio files are in their expected folders.
4. Build the project using **Build → Build Solution**.
5. Run the game using **Debug → Start Without Debugging**.

The game window is initialized with a resolution of **1000 × 600**.

## How to Play

### Controls

| Action | Key |
|---|---|
| Move Right | `D` |
| Move Left | `A` |
| Jump | `W` |
| Attack | Left Mouse Button |
| Back to Menu | `B` |

**Note:** Jumping is implemented for Level 2 and Level 3 in the current source code. The attack action is available in all three levels.

## Game Rules

- The player starts with **20 HP**.
- The maximum player health is **20 HP**.
- A player's attack deals **20 damage** to an enemy.
- Each enemy starts with **100 HP**.
- An enemy is damaged when the player attacks within the defined attack range.
- Each defeated enemy increases the score by **5 points**.
- Enemies move toward the player when they are sufficiently far away.
- When an enemy gets close enough, it attacks the player.
- Enemy attacks reduce player health.
- When player health reaches **0**, the Game Over screen is displayed.
- Completing the required enemy and gate progression eventually leads to the Jade.
- Collecting the final Jade displays the Win screen.

## Game States

| State | Description |
|---:|---|
| `0` | Menu |
| `1` | Story |
| `2` | Level 1 |
| `3` | Game Over |
| `4` | Win |
| `5` | Level 2 |
| `6` | Level Select |
| `7` | Level 3 |

## Enemy System

The game contains enemy systems for all three levels.

### Level 1 Enemy

- One enemy type.
- Idle animation.
- 3-frame running animation.
- 2-frame attack animation.
- 10 enemies are defeated sequentially.

### Level 2 Enemies

Level 2 contains two enemy types.

**Enemy Type 1**
- Idle animation.
- 3-frame running animation.
- 3-frame attack animation.
- Used for the first 5 enemies.

**Enemy Type 2**
- Idle animation.
- 3-frame running animation.
- 3-frame attack animation.
- Used for the second 5 enemies.

### Level 3 Enemies

Level 3 also contains two enemy types.

**Enemy Type 1**
- Idle animation.
- 3-frame running animation.
- 2-frame attack animation.
- Used for the first 5 enemies.

**Enemy Type 2**
- Idle animation.
- 3-frame running animation.
- 2-frame attack animation.
- Used for the second 5 enemies.

## Player System

The player system includes:

- Player position and movement.
- Running animation.
- Attack animation.
- Attack damage.
- Health management.
- Jumping.
- Player direction tracking.
- Animation frame management.

The player uses a 4-frame attack animation and a 3-frame running animation.

## Scoring System

- Each defeated enemy = **5 points**.
- The score is displayed with a coin icon.
- The score is tracked during gameplay.
- Level 3 is designed to continue the score from Level 2 when started through the normal progression.

## Health System

- Maximum health: **20**
- Starting health: **20**
- Enemy attacks reduce the player's health.
- The health bar changes according to the player's remaining health.
- Reaching 0 HP changes the game state to Game Over.

## Animation System

The game uses image-based frame animation.

### Player
- Idle image
- 3 running images
- 4 attack images

### Level 1 Enemy
- Idle image
- 3 running images
- 2 attack images

### Level 2 Enemy Types
Each Level 2 enemy type has:
- 1 idle image
- 3 running images
- 3 attack images

### Level 3 Enemy Types
Each Level 3 enemy type has:
- 1 idle image
- 3 running images
- 2 attack images

Animation updates are handled through iGraphics timers.

## Camera and Scrolling

- Level 1 uses a world width of 3000.
- Level 2 uses a world width of 3000.
- Level 3 uses a world width of 3000.
- The camera follows the player after the camera-follow position is reached.
- Selected Level 2 and Level 3 stages use repeated background images to create a scrolling effect.

## Audio

- `background.mp3` — background music
- `attack.wav` — player attack sound
- `enemy_hit.wav` — enemy hit sound
- `victory.wav` — victory sound
- `gameover.mp3` — game-over sound

## Project Contributors
1. Zarin 
2. Raisa
3. Urmi

### **Menu**
<img width="500" height="300" alt="menu" src="https://github.com/user-attachments/assets/431bfe30-f77e-49c2-85a5-86479b2e0736" />

### **Character**
<img width="158" height="150" alt="player" src="https://github.com/user-attachments/assets/5a25d502-4678-4806-ae69-b6cf0887831b" />
<img width="158" height="150" alt="enemy" src="https://github.com/user-attachments/assets/8cf8128e-1c07-4e85-901d-f3d14f9b9a6d" />

## Youtube Link
https://youtu.be/qObVY6AoV-A?si=RxlORZLjASZm7Xzy




   
