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

void updateChromeScore(){
	chromeCurrentScore = currentScore;
	intToStr(chromeCurrentScore, chromeScoreStr, 8);
	VDP_drawText(chromeScoreStr, 12, 1);
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
	VDP_drawText("NO-MISS", 7, 12);
	VDP_drawText(noMiss ? (currentZone >= 10 ? "35000" : "25000") : "00000", 20, 12);
	VDP_drawText("STAGE", 7, 14);
	VDP_drawText(currentZone >= 10 ? "15000" : "10000", 20, 14);
	if(currentZone % 5 == 0){
		VDP_drawText("BOSS", 7, 16);
		VDP_drawText(currentZone >= 10 ? "30000" : "20000", 20, 16);
		currentScore += currentZone >= 10 ? 30000 : 20000;
	}
	if(currentZone == 10) XGM_stopPlay();
	currentZone++;
	VDP_drawText("next stage", 7, 21);
	loadedZoneOver = TRUE;
	if(noMiss) currentScore += currentZone >= 10 ? 35000 : 25000;
	currentScore += currentZone >= 10 ? 15000 : 10000;
	updateChromeScore();
	XGM_startPlayPCM(SFX_ZONE_OVER, 1, SOUND_PCM_CH2);
}

void updateChromeZoneOver(){ // what the fuck am i on to do this
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
	if(zoneOverClock <= 0) nextZone();
}

void loadChromeGameOver(bool beatIt){
	loadedChromeGameOver = TRUE;
	VDP_drawText(beatIt ? "beat game!" : "game over!", 11, 10);
	VDP_drawText(currentScore > highScore ? "NEW HI SCORE" : "FINAL SCORE;", 10, 13);
	VDP_drawText(chromeScoreStr, 12, 15);
	if(beatIt){
		VDP_drawText("special thanks", 9, 19);
		VDP_drawText("TOUHOU GAMEDEV DISCORD", 5, 21);
	} else VDP_drawText("press any button", 8, 18);
	if(currentScore > highScore) highScore = currentScore;
	XGM_startPlayPCM(beatIt ? SFX_BEAT_GAME : SFX_GAME_OVER, 2, SOUND_PCM_CH2);
}

void loadChromeBeatGame(){
	gameOver = TRUE;
	loadChromeGameOver(TRUE);
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
	VDP_loadTileSet(bossBar.tileset, 8, DMA);
	updateChromeScore();
	loadChromeZone();
	loadChromeLives();
	zoneOverClock = ZONE_OVER_CHROME_LIMIT;
}

void updateChrome(){
	if(zoneStarting) loadChrome();
	else {
		if(zoneOver){
			if(!loadedZoneOver) currentZone == 20 ? loadChromeBeatGame() : loadChromeZoneOver();
			updateChromeZoneOver();
		} else if(gameOver){
			if(!loadedChromeGameOver) loadChromeGameOver(FALSE);
		} else {
			updateChromePlayerLives();
			updateChromeBoss();
			if(chromeCurrentScore < currentScore) updateChromeScore();
		}
	}
}