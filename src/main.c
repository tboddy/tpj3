#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "chrome.h"
#include "start.h"
#include "boss.h"
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

	XGM_setPCM(SFX_MENU_SELECT, sfxMenuSelect, sizeof(sfxMenuSelect)); // shit
	XGM_setPCM(SFX_MENU_CHOOSE, sfxMenuChoose, sizeof(sfxMenuChoose));
	XGM_setPCM(SFX_START_GAME, sfxStartGame, sizeof(sfxStartGame));
	XGM_setPCM(SFX_PLAYER_SHOT, sfxPlayerShot, sizeof(sfxPlayerShot));
	XGM_setPCM(SFX_ZONE_OVER, sfxZoneOver, sizeof(sfxZoneOver));

	XGM_setPCM(SFX_BULLET_1, sfxBullet1, sizeof(sfxBullet1));

	XGM_setPCM(SFX_EXPLOSION_1, sfxExplosion1, sizeof(sfxExplosion1));
	XGM_setPCM(SFX_EXPLOSION_2, sfxExplosion2, sizeof(sfxExplosion2));
	XGM_setPCM(SFX_EXPLOSION_3, sfxExplosion3, sizeof(sfxExplosion3));

	XGM_setPCM(SFX_GAME_OVER, sfxGameOver, sizeof(sfxGameOver));
	XGM_setPCM(SFX_BEAT_GAME, sfxBeatGame, sizeof(sfxBeatGame));

}

void loadGame(){
	currentZone = 1;
	started = TRUE;
	zoneStarting = TRUE;
	gameStarting = TRUE;
	noMiss = TRUE;
	yinBulletSpeed = 4;
	podBulletSpeed = 3;
	currentScore = 0;
	loadExplosion();
	XGM_startPlay(&bgmStage1);
}

void resetGame(){
	VDP_clearPlane(BG_A, TRUE);
	VDP_clearPlane(BG_B, TRUE);
	DMA_waitCompletion();
	startClock = 0;
	zoneOver = FALSE;
	started = FALSE;
	gameOverClock = 0;
	paused = FALSE;
	gameOver = FALSE;
	loadedChromeGameOver = FALSE;
	loadedZoneOver = FALSE;
	zoneStarting = FALSE;
	gameClock = 0;
	playerLives = 2;
	playerBombs = 3;
	bossType = 0;
	noMiss = TRUE;
	SPR_reset();
	for(s8 i = 0; i < BG_SCROLL_WIDTH; i++) backgroundScrolls[i] = 0;
	VDP_setVerticalScrollTile(BG_B, 0, backgroundScrolls, BG_SCROLL_WIDTH, DMA_QUEUE);
	VDP_setScreenWidth320();
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
	if(doZoneStart){
		zoneStarting = TRUE;
		doZoneStart = FALSE;
	}
	if(!gameOver && started && gameClock >= 15 && !zoneOver){
		if(controls.start && !pausing){
			pausing = TRUE;
			paused = paused ? FALSE : TRUE;
		} else if(!controls.start && pausing) pausing = FALSE;
	} else if(gameOver){
		if(gameOverClock < 600) gameOverClock++;
		if(gameOverClock >= 120 && (controls.a || controls.b || controls.c || controls.start)) resetGame();
	}
};

void nextZone(){
	if(currentZone == 21){
		resetGame();
	} else {
		SPR_reset();
		loadExplosion();
		if(currentZone % 5 == 0) loadBoss();
		resetBackground();
		resetEnemies();
		resetPlayer();
		doZoneStart = TRUE;
		zoneOver = FALSE;
		loadedZoneOver = FALSE;
		gameClock = -5;
		noMiss = TRUE;
		XGM_startPlayPCM(SFX_START_GAME, 1, SOUND_PCM_CH2);
		if(currentZone == 11) XGM_startPlay(&bgmStage2);
	}
}

int main() {
	XGM_setLoopNumber(-1);
	JOY_init();
	JOY_setEventHandler(&updateControls);
	loadResources();
	SPR_init(0, 0, 0);
	loadStart();
	playerLives = 2;
	playerBombs = 3;
	while(1){
		started ? updateGame() : updateStart();
		SPR_update();
		SYS_doVBlankProcess();
	}
	return (0);
}