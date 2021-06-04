#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "chrome.h"


// hud

void loadChromeFrame(){
	for(s16 x = 0; x < 32; x++){
		for(s16 y = 0; y < 28; y++){
			if((x == 0 || x == 31) || (y < 3 || y == 27)){
				frameTileIndex = 3;
				if(y == 2 || y == 27) frameTileIndex = x > 0 && x < 31 ? 5 : 6;
				else if((x == 0 || x == 31) && y > 2 && y < 27) frameTileIndex = 4;
				VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, y == 27 ? 1 : 0, x == 31 ? 1 : 0, frameTileIndex), x, y);
			}
		}
	}
}

void loadChromeLives(){
	VDP_drawText("X2", 29, 1);
}

void loadChromeScore(){
	VDP_drawText("SC 00000000", 1, 1);
}


// states

void loadChromeZoneOver(){
	for(s16 x = 1; x < 31; x++) for(s16 y = 3; y < 27; y++) VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, 11), x, y);
	VDP_drawText("zone", 11, 12);
	VDP_drawText("clear", 16, 12);
	VDP_drawText("next", 10, 14);
	VDP_drawText("zone", 15, 14);
	VDP_drawText("in", 20, 14);
	VDP_drawText("^", 14, 16);
	loadedZoneOver = TRUE;
}

void updateChromeZoneOver(){
	if(zoneOverClock % 60 == 0 && zoneOverClock > 0){
		VDP_drawText(zoneOverStage >= 1 ? (zoneOverStage >= 2 ? "[" : "\\") : "]", 14, 16);
		zoneOverStage++;
	}
	VDP_drawText("/!!", 15, 16);
	zoneOverClock++;
	if(zoneOverClock >= 240) nextZone();
}


// loop

void loadChrome(){
	VDP_loadTileSet(frame1.tileset, 3, DMA);
	VDP_loadTileSet(frame2.tileset, 4, DMA);
	VDP_loadTileSet(frame3.tileset, 5, DMA);
	VDP_loadTileSet(frame4.tileset, 6, DMA);
	VDP_loadTileSet(frame5.tileset, 7, DMA);
	loadChromeFrame();
	loadChromeScore();
	// VDP_drawText("Zone 1", 1, 1);
	loadChromeLives();
	zoneOverStage = 0;
}

void updateChrome(){
	if(zoneStarting) loadChrome();
	else {
		if(zoneOver){
			if(!loadedZoneOver) loadChromeZoneOver();
			updateChromeZoneOver();
		}
	}
}