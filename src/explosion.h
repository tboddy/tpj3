#define EXPLOSION_DUMP_X GAME_WIDTH + 32
#define EXPLOSION_DUMP_Y GAME_HEIGHT + 64

#define EXPLOSION_SPRITE_OFFSET 12
#define EXPLOSION_LIMIT 20

s16 explosionClock,
	explosionClockPlayerShot;

Sprite* explosionImage;
Sprite* explosionImagePlayerShot;

void loadExplosion(),
	spawnExplosion(s16, s16, bool),
	updateExplosion();