#define START_BG_HEIGHT 28
#define START_BG_WIDTH 34

#define START_MENU_X 11
#define START_MENU_Y 17

#define START_LOGO_LINES 32

#define START_GRADIENT_Y 22

bool started, selectingStartMenu;

s16 currentStartMenu, lastStartMenu, startClock;

s16 startLogoScrolls[START_LOGO_LINES];
bool startLogoScrollsFlip[START_LOGO_LINES];

void loadStartBg(),
	loadStart(),
	loadStartLogo(),
	loadStartMenu(),
	resetStart(),
	animateStartLogo(),
	selectStartMenu(),
	updateStartMenu(),
	updateStart();