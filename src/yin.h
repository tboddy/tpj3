#define YIN_COUNT 3
#define YIN_SPEED 2

struct yin {
	Sprite* image;
	Vect2D_s16 pos;
	bool horizontal, last, flag1, flag2;
	s16 clock, speed, int1, int2, int3;
};

struct yin yins[YIN_COUNT];

void loadYins(),
	moveYinHorizontal(s16),
	moveYinVertical(s16),
	yinPatternOne(s16),
	yinPatternTwo(s16),
	yinPatternThree(s16),
	yinPatternFour(s16),
	yinShoot(s16),
	resetYins(),
	updateYins();