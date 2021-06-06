#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "start.h"


void loadStartBg(){
	for(s16 y = 0; y < START_BG_HEIGHT; y++){
		for(s16 x = 0; x < START_BG_WIDTH; x++){
			VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, 12), x, y);
		}
	}
}

void loadStartLogo(){
	VDP_drawText("egg", 1, 2);
}

void loadStartGirl(){
	VDP_drawImageEx(BG_A, &girl, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), 15, 4, 0, DMA_QUEUE);
}


// menu

void loadStartMenu(){
	VDP_drawText(">", 1, 5);
	VDP_drawText("START EASY", 2, 5);
	VDP_drawText("START HARD", 2, 7);
}

void updateStartMenu(){
	if(currentStartMenu != lastStartMenu){
		VDP_clearTileMapRect(BG_A, 1, 5 + lastStartMenu * 2, 1, 1);
		VDP_drawText(">", 1, 5 + currentStartMenu * 2);
		lastStartMenu = currentStartMenu;
	}
	if((controls.up || controls.down) && !selectingStartMenu){
		currentStartMenu += controls.up ? 1 : -1;
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
	}
}


// loop

void loadStart(){
	currentStartMenu = 0;
	loadStartBg();
	loadStartLogo();
	loadStartGirl();
	loadStartMenu();
}

void resetStart(){
	VDP_clearTileMapRect(BG_B, 0, 0, START_BG_WIDTH, START_BG_HEIGHT);
}

void updateStart(){
	updateStartMenu();
	if(controls.a || controls.start) selectStartMenu();
}