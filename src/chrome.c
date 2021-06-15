#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "chrome.h"
#include "boss.h"
#include "player.h"


// lives

void loadChromeLives(){
	VDP_drawImageEx(BG_A, &chromePlayer, TILE_ATTR_FULL(PAL1, 1, 0, 0, 160), 1, 1, 0, DMA_QUEUE);
}

void updateChromePlayerLives(){
	if(chromePlayerLives != playerLives){
		for(s8 x = 0; x < 6; x++){
			VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, 11), x + 6, 1);
			if(x < playerLives) VDP_drawText("#", x + 6, 1);
		}
		chromePlayerLives = playerLives;
	}
}


// score

void loadChromeScore(){
	VDP_drawText("00000000", 12, 1);
}


// zone

void loadChromeZone(){
	intToStr(currentZone, zoneHudStr, 2);
	VDP_drawText(zoneHudStr, 29, 1);
	VDP_drawImageEx(BG_A, &chromeStage, TILE_ATTR_FULL(PAL1, 1, 0, 0, 170), 24, 1, 0, DMA_QUEUE);
}


// states

void loadChromeZoneOver(){
	chromePlayerLives = 0;
	intToStr(currentZone, currentZoneStr, 2);

	VDP_drawText("stage", 7, 8);
	VDP_drawText(currentZoneStr, 13, 8);
	VDP_drawText("complete!", 16, 8);

	VDP_drawText("BONUS TIME", 7, 12);
	VDP_drawText("00000", 20, 12);

	VDP_drawText("NO-MISS", 7, 14);
	VDP_drawText("00000", 20, 14);

	VDP_drawText("STAGE", 7, 16);
	VDP_drawText("00000", 20, 16);

	currentZone++;
	VDP_drawText("next stage", 7, 21);
	loadedZoneOver = TRUE;
}

void updateChromeZoneOver(){ // lmao
	strcpy(zoneOverTime, zoneOverClock >= 180 ? "3" : (zoneOverClock >= 120 ? "2" : (zoneOverClock >= 60 ? "1" : "0")));
	strcat(zoneOverTime, ";");
	if(zoneOverClock % 60 < 10) strcat(zoneOverTime, "0");
	else if(zoneOverClock % 60 < 20) strcat(zoneOverTime, "1");
	else if(zoneOverClock % 60 < 30) strcat(zoneOverTime, "2");
	else if(zoneOverClock % 60 < 40) strcat(zoneOverTime, "3");
	else if(zoneOverClock % 60 < 50) strcat(zoneOverTime, "4");
	else if(zoneOverClock % 60 < 60) strcat(zoneOverTime, "5");
	switch(zoneOverClock % 6){
		case 0: strcat(zoneOverTime, "0"); break;
		case 1: strcat(zoneOverTime, "1"); break;
		case 2: strcat(zoneOverTime, "2"); break;
		case 3: strcat(zoneOverTime, "3"); break;
		case 4: strcat(zoneOverTime, "4"); break;
		case 5: strcat(zoneOverTime, "5"); break;
		case 6: strcat(zoneOverTime, "6"); break;
		case 7: strcat(zoneOverTime, "7"); break;
		case 8: strcat(zoneOverTime, "8"); break;
		case 9: strcat(zoneOverTime, "9"); break;
	}
	VDP_drawText(zoneOverTime, 21, 21);
	zoneOverClock--;
	if(zoneOverClock <= 0){
		nextZone();
	}
}


// boss

void updateChromeBoss(){
	if(bossActive){
		if(lastBossHealth != bossHealth){
			VDP_drawImageEx(BG_A, &chromeEnemy, TILE_ATTR_FULL(PAL1, 1, 0, 0, 190), 1, BOSS_TILE_Y, 0, DMA_QUEUE);
			bossLimit = fix16Div(fix16Mul(fix16Div(FIX16(bossHealth), FIX16(bossMax)), BOSS_TILE_PX), 8);
			for(s16 x = 0; x < BOSS_TILE_COUNT; x++){
				if(bossHealth <= 1 || FIX16(x) >= bossLimit){
					VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, 11), x + BOSS_TILE_X, BOSS_TILE_Y);
				}
			}
			for(s16 x = 0; x < BOSS_TILE_COUNT; x++){
				if(bossHealth > 1 && FIX16(x) < bossLimit) VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, 8), x + BOSS_TILE_X, BOSS_TILE_Y);
			}
			lastBossHealth = bossHealth;
		}
	}
}


// loop

void loadChrome(){
	VDP_loadTileSet(frame1.tileset, 3, DMA);
	VDP_loadTileSet(frame2.tileset, 4, DMA);
	VDP_loadTileSet(frame3.tileset, 5, DMA);
	VDP_loadTileSet(frame4.tileset, 6, DMA);
	VDP_loadTileSet(frame5.tileset, 7, DMA);
	VDP_loadTileSet(bossBar.tileset, 8, DMA);
	// loadChromeFrame();
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
		} else {
			updateChromePlayerLives();
			updateChromeBoss();
		}
	}
}