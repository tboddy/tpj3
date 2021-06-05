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
	VDP_drawText("?2", 29, 1);
}

void loadChromeScore(){
	VDP_drawText("00000000", 1, 1);
}

void loadChromeZone(){
	intToStr(currentZone, zoneHudStr, 2);
	VDP_drawText("ZONE", 13, 1);
	VDP_drawText(zoneHudStr, 18, 1);
}


// states

void loadChromeZoneOver(){
	currentZone++;
	for(s16 x = 1; x < 31; x++) for(s16 y = 3; y < 27; y++) VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, 11), x, y);
	if(currentZone < 10) strcpy(currentZoneStr, "!");
	else if(currentZone < 20) strcpy(currentZoneStr, "\"");
	switch(currentZone % 10){
		case 0: strcat(currentZoneStr, "!"); break;
		case 1: strcat(currentZoneStr, "\""); break;
		case 2: strcat(currentZoneStr, "#"); break;
		case 3: strcat(currentZoneStr, "$"); break;
		case 4: strcat(currentZoneStr, "%"); break;
		case 5: strcat(currentZoneStr, "&"); break;
		case 6: strcat(currentZoneStr, "'"); break;
		case 7: strcat(currentZoneStr, "("); break;
		case 8: strcat(currentZoneStr, ")"); break;
		case 9: strcat(currentZoneStr, "*"); break;
	}
	VDP_drawText("zone", 11, 12);
	// VDP_drawText(currentZoneStr, 16, 12);
	VDP_drawText("clear", 16, 12);
	VDP_drawText("zone", 11, 14);
	VDP_drawText(currentZoneStr, 16, 14);
	// VDP_drawText("zone", 15, 14);
	VDP_drawText("in", 19, 14);
	VDP_drawText("^", 14, 16);
	loadedZoneOver = TRUE;
}

void updateChromeZoneOver(){
	strcpy(zoneOverTime, zoneOverClock >= 180 ? "$" : (zoneOverClock >= 60 ? "\"" : "!"));
	strcpy(zoneOverTime, zoneOverClock >= 120 ? "#" : (zoneOverClock >= 60 ? "\"" : "!"));
	strcat(zoneOverTime, "/");
	if(zoneOverClock % 60 < 10) strcat(zoneOverTime, "!");
	else if(zoneOverClock % 60 < 20) strcat(zoneOverTime, "\"");
	else if(zoneOverClock % 60 < 30) strcat(zoneOverTime, "#");
	else if(zoneOverClock % 60 < 40) strcat(zoneOverTime, "$");
	else if(zoneOverClock % 60 < 50) strcat(zoneOverTime, "%");
	else if(zoneOverClock % 60 < 60) strcat(zoneOverTime, "&");
	switch(zoneOverClock % 6){
		case 0: strcat(zoneOverTime, "!"); break;
		case 1: strcat(zoneOverTime, "\""); break;
		case 2: strcat(zoneOverTime, "#"); break;
		case 3: strcat(zoneOverTime, "$"); break;
		case 4: strcat(zoneOverTime, "%"); break;
		case 5: strcat(zoneOverTime, "&"); break;
		case 6: strcat(zoneOverTime, "'"); break;
		case 7: strcat(zoneOverTime, "("); break;
		case 8: strcat(zoneOverTime, ")"); break;
		case 9: strcat(zoneOverTime, "*"); break;
	}
	VDP_drawText(zoneOverTime, 14, 16);
	zoneOverClock--;
	if(zoneOverClock <= 0){
		nextZone();
	}
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
	loadChromeZone();
	loadChromeLives();
	zoneOverClock = ZONE_OVER_CHROME_LIMIT;
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