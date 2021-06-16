#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "start.h"


// background

void loadStartBg(){
	for(s8 y = 0; y < START_BG_HEIGHT; y++)
		for(s8 x = -1; x < START_BG_WIDTH; x++) if(y > START_BG_HEIGHT - 2) VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, 14), x, y);
	loadStartGradient();
}

void loadStartGradient(){
	for(s8 x = 0; x < START_BG_WIDTH; x++){
		VDP_drawImageEx(BG_B, &startGradient, TILE_ATTR_FULL(PAL1, 0, 0, 0, 200), x, START_GRADIENT_Y, 0, DMA_QUEUE);
		for(s8 y = 0; y < 12; y++) VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, 11), x, y + START_GRADIENT_Y);
	}
}


// logo

void loadStartLogo(){
	s8 logoCount = 0;
	for(s8 i = 0; i < START_LOGO_LINES; i++) startLogoScrolls[i] = random() % 4 - 2;
	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_2TILE);
	VDP_drawImageEx(BG_B, &startLogo, TILE_ATTR_FULL(PAL1, 0, 0, 0, 15), 3, START_LOGO_Y, 0, DMA_QUEUE);
	VDP_drawImageEx(BG_B, &startLogoV, TILE_ATTR_FULL(PAL1, 0, 0, 0, 100), 3, START_LOGO_Y + 4, 0, DMA_QUEUE);
	animateStartLogo();
}

void animateStartLogo(){
	if(startClock % 8 == 0){
		for(s8 i = 0; i < START_LOGO_LINES; i++){
			if(aboutShowing){
				startLogoScrolls[i] = 0;
			} else {
				if(i < START_LOGO_LINES / 3 || (i >= START_LOGO_LINES / 3 && i < START_LOGO_LINES / 3 * 2 && startClock % 16 == 0) ||
					(i >= START_LOGO_LINES / 3 * 2 && startClock % 32 == 0)){
					startLogoScrollsFlip[i] ? startLogoScrolls[i]-- : startLogoScrolls[i]++;
					if(startLogoScrolls[i] >= (2)) startLogoScrollsFlip[i] = TRUE;
					else if(startLogoScrolls[i] <= (	-2)) startLogoScrollsFlip[i] = FALSE;
				}
			}
		}
		VDP_setHorizontalScrollLine(BG_B, 72, startLogoScrolls, START_LOGO_LINES, DMA_QUEUE);
	}
}



// menu

void loadStartMenu(){
	VDP_drawText(">", START_MENU_X - 1, START_MENU_Y);
	VDP_drawText("START GAME", START_MENU_X, START_MENU_Y);
	VDP_drawText("ABOUT", START_MENU_X, START_MENU_Y + 2);
}

void updateStartMenu(){
	if(currentStartMenu != lastStartMenu && !aboutShowing){
		VDP_clearTileMapRect(BG_A, START_MENU_X - 1, START_MENU_Y + lastStartMenu * 2, 1, 1);
		VDP_drawText(">", START_MENU_X - 1, START_MENU_Y + currentStartMenu * 2);
		lastStartMenu = currentStartMenu;
	}
	if((controls.up || controls.down) && !selectingStartMenu && !aboutShowing){
		currentStartMenu += controls.up ? -1 : 1;
		if(currentStartMenu > 1) currentStartMenu = 0;
		else if(currentStartMenu < 0) currentStartMenu = 1;
		selectingStartMenu = TRUE;
	} else if(!controls.up && !controls.down && !controls.a && !controls.b && !controls.c && !controls.start && selectingStartMenu) selectingStartMenu = FALSE;
}

void selectStartMenu(){
	selectingStartMenu = TRUE;
	switch(currentStartMenu){
		case 0:
			resetStart();
			loadGame();
			break;
		case 1:
			loadStartAbout();
			break;
	}
}


// about

void loadStartAbout(){
	aboutShowing = TRUE;
	for(s8 x = 0; x < START_BG_WIDTH; x++)
		for(s8 y = 0; y < START_BG_HEIGHT; y++)
			VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, 13), x, y);
	VDP_clearTileMapRect(BG_A, 0, 0, START_BG_WIDTH, START_BG_HEIGHT);
	aboutY = 2;
	VDP_drawText("the story so far", 8, aboutY);
	aboutY += 2;
	VDP_drawText("MOMOYO IS YOUR REGULAR HARD-", 2, aboutY); aboutY++;
	VDP_drawText("WORKING CENTIPEDE WHO LIVES IN", 1, aboutY); aboutY++;
	VDP_drawText("THE MOMENT... BUT DOES HER NEW", 1, aboutY); aboutY++;
	VDP_drawText("BOSS HAVE HER MAKING NEW PLANS", 1, aboutY); aboutY += 2;
	VDP_drawText("USE HER TOOLS OVER 20 STAGES &", 1, aboutY); aboutY++;
	VDP_drawText("DIG UP SOME SWEETS TO BRING TO", 1, aboutY); aboutY++;
	VDP_drawText("##MEGUMU##", 11, aboutY);
	aboutY += 3;
	VDP_drawText("how to play", 1, aboutY); aboutY += 2;
	VDP_drawText("d=pad  MOVE", 1, aboutY); aboutY++;
	VDP_drawText("a,c    SHOOT", 1, aboutY); aboutY++;
	VDP_drawText("b      FOCUS/SLOW", 1, aboutY); aboutY++;
	VDP_drawText("start  PAUSE", 1, aboutY);
	aboutY += 3;
	VDP_drawText("EVERYTHING BY T.BODDY", 1, aboutY); aboutY++;
	VDP_drawText("FOR touhou pride game jam iii", 1, aboutY); aboutY++;
	VDP_drawText("TOUHOU PROJECT COPYRIGHT ZUN?", 1, aboutY); aboutY += 2;
	VDP_drawText("press any button to go back", 1, aboutY); aboutY++;
	startClock = SEGA_LIMIT + 120;
}

void startGoBack(){
	selectingStartMenu = TRUE;
	aboutShowing = FALSE;
	currentStartMenu = 0;
	VDP_clearTileMapRect(BG_B, 0, 0, START_BG_WIDTH, START_BG_HEIGHT);
	VDP_clearTileMapRect(BG_A, 0, 0, START_BG_WIDTH, START_BG_HEIGHT);
	for(s8 y = 0; y < START_BG_HEIGHT; y++)
		for(s8 x = -1; x < START_BG_WIDTH; x++) VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, 13), x, y);
	loadStartBg();
	loadStartLogo();
	loadStartMenu();
	loadStartScore();
	loadStartCredit();
}

void updateStartAbout(){
	if(startClock % 120 == 0) VDP_drawImageEx(BG_B, &startAbout, TILE_ATTR_FULL(PAL1, 0, 0, 0, 64), 22, 12, 0, DMA_QUEUE);
	else if(startClock % 120 == 60) VDP_drawImageEx(BG_B, &startAbout2, TILE_ATTR_FULL(PAL1, 0, 0, 0, 128), 22, 12, 0, DMA_QUEUE);
}


// score & credit

void loadStartScore(){
	intToStr(highScore, startHighScoreStr, 8);
	VDP_drawText("HI", 1, 26);
	VDP_drawText(startHighScoreStr, 4, 26);
}

void loadStartCredit(){
	VDP_drawText("06.2021 T.BODDY", 16, 26);
}


// loop

void loadStart(){
	VDP_loadTileSet(startTop.tileset, 13, DMA);
	VDP_loadTileSet(startBottom.tileset, 14, DMA);
	for(s8 y = 0; y < START_BG_HEIGHT; y++)
		for(s8 x = -1; x < START_BG_WIDTH; x++) VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, 13), x, y);
	segaImage1 = SPR_addSprite(&startBoddy1, SEGA_X - 56, SEGA_Y, TILE_ATTR(PAL1, 0, 0, 0));
	segaImage2 = SPR_addSprite(&startBoddy2, SEGA_X, SEGA_Y, TILE_ATTR(PAL1, 0, 0, 0));
	// VDP_drawImage(BG_B, &startBoddy, 0, 0);
}

void resetStart(){
	VDP_clearTileMapRect(BG_B, 0, 0, START_BG_WIDTH, START_BG_HEIGHT);
	VDP_clearTileMapRect(BG_A, 0, 0, START_BG_WIDTH, START_BG_HEIGHT);
}

void updateStart(){
	if(startClock >= SEGA_LIMIT + 15){
		updateStartMenu();
		animateStartLogo();
		if((controls.a || controls.b || controls.c || controls.start) && aboutShowing && !selectingStartMenu) startGoBack();
		else if((controls.a || controls.start) && !aboutShowing && !selectingStartMenu) selectStartMenu();
		if(aboutShowing) updateStartAbout();
	} else if(startClock == SEGA_LIMIT - 25){
		for(s8 y = 0; y < START_BG_HEIGHT; y++)
			for(s8 x = -1; x < START_BG_WIDTH; x++) VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, 10), x, y);
	} else if(startClock == SEGA_LIMIT - 20){
		for(s8 y = 0; y < START_BG_HEIGHT; y++)
			for(s8 x = -1; x < START_BG_WIDTH; x++) VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, 11), x, y);
	} else if(startClock == SEGA_LIMIT - 15){
		SPR_releaseSprite(segaImage1);
		SPR_releaseSprite(segaImage2);
	} else if(startClock == SEGA_LIMIT - 10){
		VDP_setScreenWidth256();
	} else if(startClock == SEGA_LIMIT - 5){
		loadStartBg();
	} else if(startClock == SEGA_LIMIT){
		for(s8 y = 0; y < START_BG_HEIGHT; y++)
			for(s8 x = -1; x < START_BG_WIDTH; x++) VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, 10), x, y);
	} else if(startClock == SEGA_LIMIT + 5){
		VDP_clearTileMapRect(BG_A, -1, 0, START_BG_WIDTH, START_BG_HEIGHT);
	} else if(startClock == SEGA_LIMIT + 10){
		loadStartLogo();
		loadStartMenu();
		loadStartScore();
		loadStartCredit();
		XGM_setLoopNumber(0);
		XGM_startPlay(&bgmStart);
	}
	startClock++;
	if(startClock >= 1800) startClock = SEGA_LIMIT + 120;
}