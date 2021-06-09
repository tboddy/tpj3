// #define CENTIPEDE_COUNT 1
// #define CENTIPEDE_COUNT 7
#define CENTIPEDE_MAX 16
#define CENTIPEDE_OFFSET 8
#define CENTIPEDE_LIMIT_LEFT FIX16(8)
#define CENTIPEDE_LIMIT_RIGHT FIX16(GAME_WIDTH - 8)
#define CENTIPEDE_LIMIT_TOP FIX16(32)
#define CENTIPEDE_LIMIT_BOTTOM FIX16(GAME_HEIGHT - 8)

#define CENTIPEDE_COLLIDE_OFFSET FIX16(8)
#define CENTIPEDE_BULLET_OFFSET FIX16(8)
#define CENTIPEDE_PLAYER_OFFSET FIX16(2)
#define CENTIPEDE_POD_OFFSET FIX32(4)

#define CENTIPEDE_DUMP_X FIX16(GAME_WIDTH + 64)
#define CENTIPEDE_DUMP_Y FIX16(0 - 64)

#define CENTIPEDE_HIT 8
// #define CENTIPEDE_HIT 100

struct centipede {
	Sprite* image;
	Vect2D_f16 pos;
	bool flippedX, flippedY, flipping, active, flag1, turning, opposite;
	s16 clock, flipClock, definition, health, turnClock;
	f16 speed, nextY;
};

s16 centipedeCount, lastCentipede, tempLastCentipede;
s32 centipedePodCheck;
f16 centipedeSpeed;

struct centipede centipedes[CENTIPEDE_MAX];

bool centipedeCollided, zoneOverCheck;

void loadCentipede(),
	moveCentipede(s16),
	collideCentipede(s16),
	animateCentipede(s16),
	destroyCentipede(s16),
	splitCentipede(s16),
	turnCentipede(s16, s16),
	resetCentipede(),
	updateCentipede();