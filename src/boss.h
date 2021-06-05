#define BOSS_LOAD_TIME 15

#define BOSS_X FIX32(16 * 8)
#define BOSS_Y FIX32(8 * 8)
#define BOSS_B_X fix32ToFix16(BOSS_X)
#define BOSS_B_Y fix32ToFix16(BOSS_Y)
#define BOSS_X_OFFSET FIX16(8 * 10)
#define BOSS_X_OFFSET_NEG fix16Sub(FIX16(0), BOSS_X_OFFSET)

#define BOSS_COLLIDE_OFFSET FIX32(40)

s16 bossClock, bossInt1, bossInt2, bossType;
s32 bossCollisionDistance;

bool bossActive, bossLoaded;

void loadBoss(),
	bossPatternOne(),
	bossPatternTwo(),
	bossPatternThree(),
	bossPatternFour(),
	bossPatternFive(),
	bossPatternSix(),
	bossPatternSeven(),
	drawBoss(),
	collideBoss(),
	hitBoss(),
	shootBoss(),
	updateBoss();