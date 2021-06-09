#define POD_COUNT 16

#define POD_DUMP_X FIX16(GAME_WIDTH + 32)
#define POD_DUMP_Y FIX16(GAME_HEIGHT + 32)

#define POD_TIME_LIMIT 150

struct pod {
	bool active, random;
	s16 clock;
	Vect2D_f16 pos;
	Sprite* image;
};

struct podSpawner {
	f16 x, y;
	bool random;
};

struct pod pods[POD_COUNT];

s16 currentPodCount;

Vect2D_f16 currentPodPos[POD_COUNT];

bool foundRandomPodMatch;

void loadPod(),
	podPatternOne(s16),
	podPatternTwo(s16),
	podPatternThree(s16),
	podPatternFour(s16),
	podPatternFive(s16),
	shootPod(s16),
	destroyPod(s16),
	killPod(s16),
	resetPod(),
	updatePod();