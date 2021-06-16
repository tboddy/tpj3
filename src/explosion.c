#include <genesis.h>
#include <resources.h>
#include "main.h"
#include "explosion.h"

void loadExplosion(){
	explosionClock = 0;
	explosionClockPlayerShot = 0;
	explosionImage = SPR_addSprite(&imgExplosionPlayer, EXPLOSION_DUMP_X, EXPLOSION_DUMP_Y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
	explosionImagePlayerShot = SPR_addSprite(&imgExplosionPlayer, EXPLOSION_DUMP_X, EXPLOSION_DUMP_Y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
	SPR_setDepth(explosionImage, 3);
	SPR_setDepth(explosionImagePlayerShot, 1);
}

void spawnExplosion(s16 x, s16 y, bool isPlayerShot){
	SPR_setPosition(isPlayerShot ? explosionImagePlayerShot : explosionImage, x - EXPLOSION_SPRITE_OFFSET, y - EXPLOSION_SPRITE_OFFSET);
	isPlayerShot ? (explosionClockPlayerShot = 0) : (explosionClock = 0);
	// XGM_startPlayPCM(random() % 2 < 1 ? SFX_EXPLOSION_1 : SFX_EXPLOSION_2, 1, SOUND_PCM_CH4);
}

void updateExplosion(){
	if(explosionClock >= EXPLOSION_LIMIT || paused) SPR_setPosition(explosionImage, EXPLOSION_DUMP_X, EXPLOSION_DUMP_Y);
	if(explosionClockPlayerShot >= EXPLOSION_LIMIT || paused) SPR_setPosition(explosionImagePlayerShot, EXPLOSION_DUMP_X, EXPLOSION_DUMP_Y);
	explosionClock++;
	explosionClockPlayerShot++;
	if(explosionClock >= 600) explosionClock = 60;
	if(explosionClockPlayerShot >= 600) explosionClockPlayerShot = 60;
}