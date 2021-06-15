#define ENEMY_BULLET_LIMIT 64
#define ENEMY_BULLET_COLLISION_CHECK FIX16(14)

struct enemyBullet {
	bool active, flag1, flag2, flag3, flag4, grazed;
	Vect2D_f16 pos, velocity;
	fix16 speed;
	Sprite* image;
	s16 xOffset, yOffset, clock, angle, int1, int2, int3, int4;
	void (*updater)(s16);
};

struct bulletSpawner {
	bool flag1, flag2, flag3, flag4;
	fix16 speed, velocityX, velocityY, x, y;
	s16 angle, type, int1, int2, int3, int4;
};

struct enemyBullet bullets[ENEMY_BULLET_LIMIT];

bool killBullets;

s32 enemyBulletCollisionDistance;
s16 killBulletsClock, enemyBulletCount;
s8 podBulletSpeed, yinBulletSpeed;

fix16 honeX, honeY, honeSpeed, 
	honeEnemyBullet(fix16, fix16, s16, s16, bool);

void loadEnemies(),
	spawnEnemyBullet(struct bulletSpawner, void *),
	checkEnemyBulletCollision(s16),
	updateEnemyBullet(s16),
	drawEnemyBullet(s16),
	updateKillBullets(),
	eUpdate(s16),
	destroyEnemyBullet(s16),
	resetEnemies(),
	updateEnemies();