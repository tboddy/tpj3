#define BG_TILES_WIDTH 32
#define BG_TILES_HEIGHT 32
#define BG_SCROLL_WIDTH 16

s16 backgroundY;
s16 backgroundScrolls[BG_SCROLL_WIDTH],
	backgroundSpeeds[BG_SCROLL_WIDTH];

void loadBackgroundStage(),
	loadBackgroundBoss(),
	loadBackgroundTiles(),
	resetBackground(),
	updateBackgroundStage(),
	updateBackgroundBoss(),
	updateBackground();