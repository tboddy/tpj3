#define PLAYER_LIMIT_LEFT FIX16(4)
#define PLAYER_LIMIT_RIGHT fix16Sub(FIX16(GAME_WIDTH), PLAYER_LIMIT_LEFT)
#define PLAYER_LIMIT_TOP PLAYER_LIMIT_LEFT
#define PLAYER_LIMIT_BOTTOM fix16Sub(FIX16(GAME_HEIGHT), PLAYER_LIMIT_LEFT)

#define MOVEMENT_NORMALIZE FIX16(0.707)
#define MOVEMENT_NORMALIZE_NEG FIX16(-0.707)
#define MOVEMENT_POS FIX16(1)
#define MOVEMENT_NEG FIX16(-1)

#define PLAYER_SPEED FIX16(3.25)
#define PLAYER_SPEED_FOCUS FIX16(2)

#define PLAYER_INIT_X FIX16(GAME_WIDTH / 2)
#define PLAYER_INIT_Y FIX16(GAME_HEIGHT - 32)

#define PLAYER_BULLET_LIMIT 3
#define PLAYER_SHOT_INTERVAL 10
#define PLAYER_BULLET_SPEED FIX16(8 * 4)

#define PLAYER_BULLET_UP_LIMIT FIX16(8)
#define PLAYER_BULLET_DOWN_LIMIT FIX16(GAME_HEIGHT + 16)

#define PLAYER_BULLET_DUMP_X GAME_WIDTH + 16
#define PLAYER_BULLET_DUMP_Y GAME_HEIGHT + 16

#define RECOVER_INTERVAL 30
#define RECOVER_INTERVAL_HALF 15
#define RECOVER_MAX RECOVER_INTERVAL * 6

#define BOMB_LIMIT 200
#define BOMB_INTERVAL 10

struct playerBullet {
	bool active, downward;
	Vect2D_f16 pos;
	Sprite* image;
};
struct playerBullet playerBullets[PLAYER_BULLET_LIMIT];

Sprite* playerSprite;

Vect2D_f16 playerPos, playerVelocity;

s16 playerShotClock, recoverClock, bombClock;
s8 playerLives, playerBombs;

bool hitPlayer, playerRecovering, bombing;

void loadPlayer(),
	updatePlayer(),
	updatePlayerBounds(),
	updatePlayerMove(),
	updatePlayerShot(),
	updatePlayerBullets(),
	spawnPlayerBullet(),
	spawnBomb(),
	updatePlayerBomb(),
	resetPlayer(),
	updatePlayerHit(),
	removePlayerBullet(s16);