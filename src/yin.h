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
	moveYinHorizontal(s8),
	moveYinVertical(s8),
	yinPatternOne(s8),
	yinPatternTwo(s8),
	yinPatternThree(s8, s8),
	yinPatternFour(s8),
	yinPatternFive(s8),
	yinShoot(s8),
	resetYins(),
	updateYins();