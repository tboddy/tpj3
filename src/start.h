#define START_BG_HEIGHT 28
#define START_BG_WIDTH 40

#define START_MENU_X 11
#define START_MENU_Y 15

#define START_LOGO_LINES 32
#define START_LOGO_Y 5

#define START_GRADIENT_Y 23

// #define SEGA_LIMIT 90
#define SEGA_LIMIT 60 * 4

#define SEGA_X 320 / 2
#define SEGA_Y GAME_HEIGHT / 2 - 16

bool started, selectingStartMenu, aboutShowing, loadedStart;

s16 currentStartMenu, lastStartMenu, startClock, aboutY;

s16 startLogoScrolls[START_LOGO_LINES];
bool startLogoScrollsFlip[START_LOGO_LINES], updatingStartCount;

s8 startCurrentLives, startCurrentBombs;

char startHighScoreStr[10];

Sprite* segaImage1;
Sprite* segaImage2;

void loadStartBg(),
	loadStart(),
	loadStartLogo(),
	loadStartMenu(),
	loadStartGradient(),
	resetStart(),
	animateStartLogo(),
	startGoBack(),
	selectStartMenu(),
	updateStartMenu(),
	loadStartScore(),
	updateStartLives(),
	updateStartBombs(),
	updateStartAbout(),
	loadStartCredits(),
	loadStartAbout(),
	updateStart();