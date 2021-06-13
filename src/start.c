#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "start.h"


void loadStartBg(){
	VDP_loadTileSet(startTop.tileset, 13, DMA);
	VDP_loadTileSet(startBottom.tileset, 14, DMA);
	for(s8 y = 0; y < START_BG_HEIGHT; y++)
		for(s8 x = -1; x < START_BG_WIDTH; x++) VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, y > START_BG_HEIGHT - 2 ? 14 : 13), x, y);
	for(s8 x = 0; x < START_BG_WIDTH; x++){
		VDP_drawImageEx(BG_B, &startGradient, TILE_ATTR_FULL(PAL1, 0, 0, 0, 200), x, START_GRADIENT_Y, 0, DMA_QUEUE);
		for(s8 y = 0; y < 12; y++) VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, 11), x, y + START_GRADIENT_Y);
	}
}

void loadStartLogo(){
	s8 logoCount = 0;
	for(s8 i = 0; i < START_LOGO_LINES; i++) startLogoScrolls[i] = random() % 4 - 2;
	VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_2TILE);
	VDP_drawImageEx(BG_B, &startLogo, TILE_ATTR_FULL(PAL1, 0, 0, 0, 15), 3, 5, 0, DMA_QUEUE);
	VDP_drawImageEx(BG_B, &startLogoV, TILE_ATTR_FULL(PAL1, 0, 0, 0, 100), 3, 9, 0, DMA_QUEUE);
	animateStartLogo();
}

void animateStartLogo(){
	if(startClock % 5 == 0){
		for(s8 i = 0; i < START_LOGO_LINES; i++){
			if(i < START_LOGO_LINES / 3 || (i >= START_LOGO_LINES / 3 && i < START_LOGO_LINES / 3 * 2 && startClock % 10 == 0) ||
				(i >= START_LOGO_LINES / 3 * 2 && startClock % 20 == 0)){
				startLogoScrollsFlip[i] ? startLogoScrolls[i]-- : startLogoScrolls[i]++;
				if(startLogoScrolls[i] >= 2) startLogoScrollsFlip[i] = TRUE;
				else if(startLogoScrolls[i] <= -2) startLogoScrollsFlip[i] = FALSE;
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
	if(currentStartMenu != lastStartMenu){
		VDP_clearTileMapRect(BG_A, START_MENU_X - 1, START_MENU_Y + lastStartMenu * 2, 1, 1);
		VDP_drawText(">", START_MENU_X - 1, START_MENU_Y + currentStartMenu * 2);
		lastStartMenu = currentStartMenu;
	}
	if((controls.up || controls.down) && !selectingStartMenu){
		currentStartMenu += controls.up ? -1 : 1;
		if(currentStartMenu > 1) currentStartMenu = 0;
		else if(currentStartMenu < 0) currentStartMenu = 1;
		selectingStartMenu = TRUE;
	} else if(!controls.up && !controls.down && selectingStartMenu) selectingStartMenu = FALSE;
}


// menu

void selectStartMenu(){
	switch(currentStartMenu){
		case 0:
			resetStart();
			loadGame();
			break;
		case 1:
			resetStart();
			loadGame();
			break;
	}
}


// loop

void loadStart(){
	currentStartMenu = 0;
	loadStartBg();
	loadStartLogo();
	loadStartMenu();
	// resetStart();
	// loadGame();
}

void resetStart(){
	VDP_clearTileMapRect(BG_B, 0, 0, START_BG_WIDTH, START_BG_HEIGHT);
	VDP_clearTileMapRect(BG_A, 0, 0, START_BG_WIDTH, START_BG_HEIGHT);
}

void updateStart(){
	updateStartMenu();
	animateStartLogo();
	if(controls.a || controls.start) selectStartMenu();
	startClock++;
	if(startClock >= 600) startClock = 0;
}