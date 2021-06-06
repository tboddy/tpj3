#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "boss.h"
#include "background.h"


void resetBackground(){
	VDP_clearTileMapRect(BG_A, 0, 0, 32, 32);
	VDP_clearTileMapRect(BG_B, 0, 0, 32, 32);
}

// stage

void loadBackgroundStage(){
	for(s16 i = 0; i < BG_SCROLL_WIDTH; i++){
		backgroundSpeeds[i] = i < 8 ? BG_SCROLL_WIDTH - i - 2 : i - 1;
		backgroundSpeeds[i]--;
	}
	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_2TILE);
	for(s16 y = 0; y < BG_TILES_HEIGHT; y++){
		for(s16 x = 0; x < BG_TILES_WIDTH; x++){
			if(x % 8 == 0 && y % 8 == 0) VDP_drawImageEx(BG_B, &ground1, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), x, y, 0, DMA_QUEUE);
			VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, 11), x, y);
		}
	}
}

void updateBackgroundStage(){
	for(s16 i = 0; i < BG_SCROLL_WIDTH; i++) backgroundScrolls[i] -= fix16ToRoundedInt(FIX16(backgroundSpeeds[i] / 4));
	VDP_setVerticalScrollTile(BG_B, 0, backgroundScrolls, BG_SCROLL_WIDTH, DMA_QUEUE);
}


// boss

void loadBackgroundBoss(){
	for(s16 i = 0; i < BG_SCROLL_WIDTH; i++) backgroundScrolls[i] = 0;
	VDP_setVerticalScrollTile(BG_B, 0, backgroundScrolls, BG_SCROLL_WIDTH, DMA_QUEUE);
	for(s16 y = 0; y < BG_TILES_HEIGHT; y++){
		for(s16 x = 0; x < BG_TILES_WIDTH; x++){
			VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, 12), x, y);
			VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, 11), x, y);
		}
	}
	VDP_drawImageEx(BG_B, &heart, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), 2, 1, 0, DMA_QUEUE);
	VDP_drawImageEx(BG_B, &heart, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), 18, 8, 0, DMA_QUEUE);
	VDP_drawImageEx(BG_B, &heart, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), 5, 15, 0, DMA_QUEUE);
	// VDP_drawImage(BG_B, &heart, 1, 1);
}

void updateBackgroundBoss(){}


// loop

void updateBackground(){
	if(zoneStarting) bossActive ? loadBackgroundBoss() : loadBackgroundStage();
	else bossActive ? updateBackgroundBoss() : updateBackgroundStage();
}
