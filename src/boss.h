#define BOSS_LOAD_TIME 15

#define BOSS_X FIX32(16 * 8)
#define BOSS_Y FIX32(8 * 8)
#define BOSS_B_X fix32ToFix16(BOSS_X)
#define BOSS_B_Y fix32ToFix16(BOSS_Y)

#define BOSS_COLLIDE_OFFSET FIX32(40)

s16 bossClock, bossInt1, bossType;
s32 bossCollisionDistance;

bool bossActive, bossLoaded;

void loadBoss(),
	drawBoss(),
	collideBoss(),
	hitBoss(),
	shootBoss(),
	updateBoss();