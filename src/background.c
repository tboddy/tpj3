#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "background.h"


void resetBackground(){
	for(s16 y = 0; y < BG_TILES_HEIGHT; y++){
		for(s16 x = 0; x < BG_TILES_WIDTH; x++){
			if(x % 8 == 0 && y % 8 == 0){
				if(currentZone == 5) VDP_drawImageEx(BG_B, &ground2, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), x, y, 0, DMA_QUEUE);
				else if(currentZone > 5 && currentZone < 10) VDP_drawImageEx(BG_B, &ground1, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), x, y, 0, DMA_QUEUE);
				if(currentZone == 10) VDP_drawImageEx(BG_B, &ground2, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), x, y, 0, DMA_QUEUE);
				else if(currentZone > 10 && currentZone < 15) VDP_drawImageEx(BG_B, &ground1, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), x, y, 0, DMA_QUEUE);
				if(currentZone == 15) VDP_drawImageEx(BG_B, &ground2, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), x, y, 0, DMA_QUEUE);
				else if(currentZone > 15) VDP_drawImageEx(BG_B, &ground1, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), x, y, 0, DMA_QUEUE);
				if(currentZone == 20) VDP_drawImageEx(BG_B, &ground2, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), x, y, 0, DMA_QUEUE);
			}
			VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, 11), x, y);
		}
	}
}

// stage

void loadBackgroundStage(){
	resetBackground();
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
	for(s16 i = 0; i < BG_SCROLL_WIDTH; i++) backgroundScrolls[i] -= fix16ToRoundedInt(FIX16(backgroundSpeeds[i] / 2)) - 1;
	VDP_setVerticalScrollTile(BG_B, 0, backgroundScrolls, BG_SCROLL_WIDTH, DMA_QUEUE);
}


// loop

void updateBackground(){
	if(gameStarting) loadBackgroundStage();
	else updateBackgroundStage();
}
