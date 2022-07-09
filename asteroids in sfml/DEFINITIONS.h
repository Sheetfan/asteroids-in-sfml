#pragma once

#define SHIP_1_FILE_PATH "Sprites/ship-1.png"
#define SHIP_2_FILE_PATH "Sprites/ship-2.png"
#define SHIP_3_FILE_PATH "Sprites/ship-3.png"
#define SHIP_4_FILE_PATH "Sprites/ship-4.png"

#define ASTEROID_1_FILE_PATH "Sprites/asteroid-1.png"
#define ASTEROID_2_FILE_PATH "Sprites/asteroid-2.png"
#define ASTEROID_3_FILE_PATH "Sprites/asteroid-3.png"
#define ASTEROID_4_FILE_PATH "Sprites/asteroid-4.png"
#define ASTEROID_5_FILE_PATH "Sprites/asteroid-5.png"
#define ASTEROID_6_FILE_PATH "Sprites/asteroid-6.png"
#define ASTEROID_7_FILE_PATH "Sprites/asteroid-7.png"

#define EXPLOSION_1_FILE_PATH "Sprites/explosion-1.png"
#define EXPLOSION_2_FILE_PATH "Sprites/explosion-2.png"
#define EXPLOSION_3_FILE_PATH "Sprites/explosion-3.png"
#define EXPLOSION_4_FILE_PATH "Sprites/explosion-4.png"

#define HUD_SCORE_FONT "Fonts/Oxanium-Medium.ttf"

#define WINDOW_WIDTH 1400.f
#define WINDOW_HEIGHT 1000.f

#define SHIP_THRAST 2.2f
#define SHIP_FRICTIONVALUE 0.5f
#define SHIP_TURNRATE 60.f
#define SHIP_MAXVELOCITY 10.0f
#define SHIP_ANIMATION_DURATION 0.1f
#define SHIP_RESPAWN_DELAY 1.3f

#define EXPLOSION_ANIMATION_DURATION 1.f

#define BULLET_VELOCITY 30.f
#define BULLET_RATE 2.0
#define BULLET_DESPAWN_TIME 5.0f

#define ASTERIOD_VELOCITY 10.0f

enum class GameStates {
	eReady,
	eDied,
	ePlaying,
	eRespawn,
	eGameOver
};