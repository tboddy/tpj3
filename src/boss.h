#define BOSS_LOAD_TIME 15

#define BOSS_X FIX32(16 * 8)
#define BOSS_Y FIX32(8 * 8)
#define BOSS_B_X fix32ToFix16(BOSS_X)
#define BOSS_B_Y fix32ToFix16(BOSS_Y)
#define BOSS_X_OFFSET FIX16(8 * 10)
#define BOSS_X_OFFSET_NEG fix16Sub(FIX16(0), BOSS_X_OFFSET)

#define BOSS_COLLIDE_OFFSET FIX32(40)

#define BOSS_SWITCH_TIME -90

s16 bossClock, bossInt1, bossInt2, bossInt3, bossType, bossHealth, bossMax;
f16 bossFix1, bossFix2;
s32 bossCollisionDistance;

bool hitBossPatterns[8];
bool bossActive, bossLoaded;

void loadBoss(),

	bossPatternOne(),
	bossPatternTwo(),

	bossPatternThree(),
	bossPatternFour(),
	bossPatternFive(),

	bossPatternSix(),
	bossPatternSeven(),
	bossPatternEight(),

	bossPatternNine(),
	bossPatternTen(),
	bossPatternEleven(),
	bossPatternTwelve(),
	bossPatternThirteen(),

	hitBossPattern(u8),

	drawBoss(),
	collideBoss(),
	hitBoss(),
	finishBoss(),
	shootBoss(),
	updateBoss();