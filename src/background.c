#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "background.h"

void loadBackgroundTiles(){
	for(s16 y = 0; y < BG_TILES_HEIGHT; y++){
		for(s16 x = 0; x < BG_TILES_WIDTH; x++){
			if(x % 8 == 0 && y % 8 == 0) VDP_drawImageEx(BG_B, &ground1, TILE_ATTR_FULL(PAL1, 0, 0, 0, 16), x, y, 0, DMA_QUEUE);
			VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, 11), x, y);
		}
	}
}

void loadBackground(){
	for(s16 i = 0; i < BG_SCROLL_WIDTH; i++){
		backgroundSpeeds[i] = i < 8 ? BG_SCROLL_WIDTH - i - 2 : i - 1;
		backgroundSpeeds[i]--;
	}
	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_2TILE);
	loadBackgroundTiles();
}

void resetBackground(){
	VDP_clearTileMapRect(BG_A, 0, 0, 32, 32);
	VDP_clearTileMapRect(BG_B, 0, 0, 32, 32);
}

void updateBackground(){
	if(zoneStarting) loadBackground();
	else {
		for(s16 i = 0; i < BG_SCROLL_WIDTH; i++){
			backgroundScrolls[i] -= fix16ToRoundedInt(FIX16(backgroundSpeeds[i] / 4));
		}
		VDP_setVerticalScrollTile(BG_B, 0, backgroundScrolls, BG_SCROLL_WIDTH, DMA_QUEUE);
	}
}
