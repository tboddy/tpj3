#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "chrome.h"
#include "background.h"
#include "enemies.h"
#include "player.h"
#include "explosion.h"

void loadResources(){
	VDP_loadFont(font.tileset, DMA);
	VDP_loadTileSet(half.tileset, 10, DMA);
	VDP_loadTileSet(least.tileset, 11, DMA);
	VDP_setPalette(PAL1, font.palette -> data);
	VDP_setTextPalette(1);
}

void loadGame(){
	currentZone = 1;
	initLives = 2;
	started = TRUE;
	zoneStarting = TRUE;
	loadExplosion();
};

void updateGame(){
	if(started && !paused){
		updateBackground();
		updateEnemies();
		updatePlayer();
		updateExplosion();
		gameClock++;
		if(gameClock >= 1800) gameClock = 0;
	}
	updateChrome();
	if(zoneFinished) zoneFinished = FALSE;
	else if(zoneStarting) zoneStarting = FALSE;
};

void nextZone(){
	resetBackground();
	resetEnemies();
	resetPlayer();
	zoneOver = FALSE;
	loadedZoneOver = FALSE;
	zoneFinished = TRUE;
	zoneStarting = TRUE;
	zoneOverClock = 0;
	gameClock = 0;
}

int main() {
	VDP_setScreenWidth256();
	JOY_init();
	JOY_setEventHandler(&updateControls);
	loadResources();
	SPR_init(0, 0, 0);
	loadGame();
	while(1){
		updateGame();
		SPR_update();
		SYS_doVBlankProcess();
	}
	return (0);
}