#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "chrome.h"
#include "start.h"
#include "background.h"
#include "enemies.h"
#include "player.h"
#include "explosion.h"

void loadResources(){
	VDP_loadFont(font.tileset, DMA);
	VDP_loadTileSet(half.tileset, 10, DMA);
	VDP_loadTileSet(least.tileset, 11, DMA);
	VDP_loadTileSet(full.tileset, 12, DMA);
	VDP_setPalette(PAL1, font.palette -> data);
	VDP_setTextPalette(1);
}

void loadGame(){
	currentZone = 1;
	started = TRUE;
	zoneStarting = TRUE;
	gameStarting = TRUE;
	noMiss = TRUE;
	yinBulletSpeed = 4;
	podBulletSpeed = 3;
	playerLives = 3;
	loadExplosion();
};

void resetGame(){
	VDP_clearPlane(BG_A, TRUE);
	VDP_clearPlane(BG_B, TRUE);
	DMA_waitCompletion();
	zoneOver = FALSE;
	started = FALSE;
	paused = FALSE;
	gameOver = FALSE;
	SPR_reset();
	for(s8 i = 0; i < BG_SCROLL_WIDTH; i++) backgroundScrolls[i] = 0;
	VDP_setVerticalScrollTile(BG_B, 0, backgroundScrolls, BG_SCROLL_WIDTH, DMA_QUEUE);
	loadStart();
}

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
	if(zoneStarting) zoneStarting = FALSE;
	if(gameStarting) gameStarting = FALSE;
	if(!gameOver && started && gameClock >= 15){
		if(controls.start && !pausing){
			pausing = TRUE;
			paused = paused ? FALSE : TRUE;
		} else if(!controls.start && pausing) pausing = FALSE;
	} else if(gameOver){
		if(gameOverClock < 600) gameOverClock++;
		if(gameOverClock >= 30 && (controls.a || controls.b || controls.c || controls.start)) resetGame();
	}
};

void nextZone(){
	SPR_reset();
	loadExplosion();
	if(currentZone % 5 == 0) loadBoss();
	resetBackground();
	resetEnemies();
	resetPlayer();
	zoneOver = FALSE;
	loadedZoneOver = FALSE;
	zoneStarting = TRUE;
	zoneOverClock = 0;
	gameClock = 0;
	noMiss = TRUE;
}

int main() {
	VDP_setScreenWidth256();
	JOY_init();
	JOY_setEventHandler(&updateControls);
	loadResources();
	SPR_init(0, 0, 0);
	// loadGame();
	loadStart();
	while(1){
		started ? updateGame() : updateStart();
		SPR_update();
		SYS_doVBlankProcess();
	}
	return (0);
}