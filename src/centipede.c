#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"
#include "centipede.h"
#include "player.h"
#include "pod.h"
#include "explosion.h"


// spawn

void spawnCentipede(){}


// movement

void moveCentipede(s16 i){
	if(centipedes[i].flipping){
		centipedes[i].pos.y = fix16Add(centipedes[i].pos.y, (centipedes[i].flippedY ? fix16Sub(FIX16(0), centipedes[i].speed) : centipedes[i].speed));
		centipedes[i].flipClock++;
		if((centipedes[i].flippedY && centipedes[i].pos.y <= centipedes[i].nextY) || (!centipedes[i].flippedY && centipedes[i].pos.y >= centipedes[i].nextY)){
			centipedes[i].flipping = FALSE;
			centipedes[i].pos.y = centipedes[i].nextY;
		}
	} else {
		centipedes[i].pos.x = fix16Add(centipedes[i].pos.x, (centipedes[i].flippedX ? fix16Sub(FIX16(0), centipedes[i].speed) : centipedes[i].speed));
		if(centipedes[i].pos.x >= CENTIPEDE_LIMIT_RIGHT || centipedes[i].pos.x <= CENTIPEDE_LIMIT_LEFT){
			centipedes[i].flippedX = centipedes[i].pos.x >= CENTIPEDE_LIMIT_RIGHT;
			if(!centipedes[i].flippedY && centipedes[i].pos.y >= CENTIPEDE_LIMIT_BOTTOM){
				centipedes[i].flippedY = TRUE;
				if(i == lastCentipede && lastCentipede < centipedeCount){
					struct podSpawner pSpawn = {
						.x = FIX16(fix16ToInt(centipedes[i].pos.x) / 16 * 16),
						.y = FIX16(fix16ToInt(centipedes[i].pos.y) / 16 * 16),
						.random = FALSE
					};
					spawnPod(pSpawn);
				}
				// can add another head
			}else if(centipedes[i].flippedY && centipedes[i].pos.y <= CENTIPEDE_LIMIT_TOP) centipedes[i].flippedY = FALSE;
			centipedes[i].flipping = TRUE;
			centipedes[i].nextY = centipedes[i].flippedY ? fix16Sub(centipedes[i].pos.y, FIX16(16)) : fix16Add(centipedes[i].pos.y, FIX16(16));
		}
		if(centipedes[i].flipClock > 0) centipedes[i].flipClock = 0;
	}
}


// change sprite

void animateCentipede(s16 i){
	if(centipedes[i].definition > 0){
		switch(centipedes[i].definition){
			case 1:
				SPR_setDefinition(centipedes[i].image, &imgGumdropRed);
				break;
			case 2:
				SPR_setDefinition(centipedes[i].image, &imgGumdropGreen);
				break;
			case 3:
				SPR_setDefinition(centipedes[i].image, &imgGumdropBlue);
				break;
		}
		centipedes[i].definition = 0;
	}
}


// collision against centipede

void hitCentipede(s16 i){
	spawnExplosion(fix16ToInt(centipedes[i].pos.x), fix16ToInt(centipedes[i].pos.y), TRUE);
	centipedes[i].health -= CENTIPEDE_HIT;
	if(centipedes[i].health < 67) centipedes[i].definition = 2;
	if(centipedes[i].health < 33){
		centipedes[i].definition = 1;
	}
	if(centipedes[i].health < 0){
		struct podSpawner pSpawn = {
			.x = FIX16(fix16ToInt(centipedes[i].pos.x) / 16 * 16),
			.y = FIX16(fix16ToInt(centipedes[i].pos.y) / 16 * 16),
			.random = FALSE
		};
		spawnPod(pSpawn);
		destroyCentipede(i);
	}
}

void turnCentipede(s16 i, s16 j){
	centipedes[i].flippedX = centipedes[i].flippedX ? FALSE : TRUE;
	centipedes[i].turning = TRUE;
	centipedes[i].turnClock = 0;
	if(centipedes[i].pos.x < pods[j].pos.x) centipedes[i].pos.x = fix16Sub(pods[j].pos.x, FIX16(8));
	else if(centipedes[i].pos.x >= pods[j].pos.x) centipedes[i].pos.x = fix16Add(pods[j].pos.x, FIX16(8));
}

void collideCentipede(s16 i){
	// against pods
	for(s16 j = 0; j < POD_COUNT; j++) if(pods[j].active) {
		centipedePodCheck = getApproximatedDistance(
			fix16ToFix32(centipedes[i].pos.x) - fix16ToFix32(pods[j].pos.x),
			fix16ToFix32(centipedes[i].pos.y) - fix16ToFix32(pods[j].pos.y));
		if(centipedePodCheck < CENTIPEDE_POD_OFFSET) turnCentipede(i, j);
	}

	// against player bullet
	centipedeCollided = FALSE;
	for(s16 j = 0; j < PLAYER_BULLET_LIMIT; j++) if(playerBullets[j].active) {
		if(fix16Sub(playerBullets[j].pos.y, CENTIPEDE_BULLET_OFFSET) <= fix16Add(centipedes[i].pos.y, CENTIPEDE_COLLIDE_OFFSET) &&
			fix16Add(playerBullets[j].pos.y, CENTIPEDE_BULLET_OFFSET) >= fix16Sub(centipedes[i].pos.y, CENTIPEDE_COLLIDE_OFFSET) &&
			fix16Sub(playerBullets[j].pos.x, CENTIPEDE_BULLET_OFFSET) <= fix16Add(centipedes[i].pos.x, CENTIPEDE_COLLIDE_OFFSET) &&
			fix16Add(playerBullets[j].pos.x, CENTIPEDE_BULLET_OFFSET) >= fix16Sub(centipedes[i].pos.x, CENTIPEDE_COLLIDE_OFFSET)){
			centipedeCollided = TRUE;
			hitCentipede(i);
			removePlayerBullet(j);
		}
	}
	// against player
	if(centipedes[i].clock % 4 == 0 && (!centipedeCollided && centipedes[i].pos.y >= fix16Sub(playerPos.y, FIX16(32)))){
		if(fix16Sub(playerPos.y, CENTIPEDE_PLAYER_OFFSET) <= fix16Add(centipedes[i].pos.y, CENTIPEDE_COLLIDE_OFFSET) &&
			fix16Add(playerPos.y, CENTIPEDE_PLAYER_OFFSET) >= fix16Sub(centipedes[i].pos.y, CENTIPEDE_COLLIDE_OFFSET) &&
			fix16Sub(playerPos.x, CENTIPEDE_PLAYER_OFFSET) <= fix16Add(centipedes[i].pos.x, CENTIPEDE_COLLIDE_OFFSET) &&
			fix16Add(playerPos.x, CENTIPEDE_PLAYER_OFFSET) >= fix16Sub(centipedes[i].pos.x, CENTIPEDE_COLLIDE_OFFSET)){
			// hitCentipede(i);
			// turnCentipede(i);
			// hit player here
		}
	}
}

void destroyCentipede(s16 i){
	centipedes[i].active = FALSE;
	centipedes[i].flippedX = FALSE;
	centipedes[i].flippedY = FALSE;
	centipedes[i].flipping = FALSE;
	centipedes[i].flag1 = FALSE;
	centipedes[i].pos.x = CENTIPEDE_DUMP_X;
	centipedes[i].pos.y = CENTIPEDE_DUMP_Y;
	SPR_releaseSprite(centipedes[i].image);
}


// loop

void loadCentipede(){
	centipedeCount = 3;
	if(currentZone >= 5) centipedeCount = 4;
	if(currentZone >= 10) centipedeCount = 5;
	if(currentZone >= 15) centipedeCount = 6;
	for(s16 i = 0; i < centipedeCount; i++){
		centipedes[i].active = TRUE;
		centipedes[i].pos.x = FIX16(16 + 16 * i);
		centipedes[i].pos.y = CENTIPEDE_LIMIT_TOP;
		// centipedes[i].speed = FIX16(currentZone >= 10 ? 4 : 2);
		centipedes[i].speed = FIX16(2);
		centipedes[i].image = SPR_addSprite(&imgGumdropRed, fix16ToInt(centipedes[i].pos.x), fix16ToInt(centipedes[i].pos.y), TILE_ATTR(PAL1, 0, FALSE, FALSE));
		centipedes[i].definition = 3;
		centipedes[i].health = i % 2 == 0 ? 80 : 100;
		centipedes[i].opposite = i % 2 == 1;
		SPR_setDepth(centipedes[i].image, 3);
	}
}

void resetCentipede(){
	for(s16 i = 0; i < centipedeCount; i++) destroyCentipede(i);
}

void updateCentipede(){
	zoneOverCheck = TRUE;
	tempLastCentipede = 0;
	for(s16 i = 0; i < centipedeCount; i++) if(centipedes[i].active) {
		tempLastCentipede++;
		zoneOverCheck = FALSE;
		moveCentipede(i);
		collideCentipede(i);
		animateCentipede(i);
		if(centipedes[i].turning){
			centipedes[i].turnClock++;
			if(centipedes[i].turnClock >= 30) centipedes[i].turning = FALSE;
		}
		SPR_setPosition(centipedes[i].image, fix16ToInt(centipedes[i].pos.x) - CENTIPEDE_OFFSET, fix16ToInt(centipedes[i].pos.y) - CENTIPEDE_OFFSET);
		if(centipedes[i].opposite){
			if(centipedes[i].clock % 40 == 0) SPR_setFrame(centipedes[i].image, 1);
			else if(centipedes[i].clock % 40 == 20) SPR_setFrame(centipedes[i].image, 0);
		}
		centipedes[i].clock++;
		if(centipedes[i].clock >= 600) centipedes[i].clock = 120;
	}
	lastCentipede = tempLastCentipede;
	if(zoneOverCheck) zoneOver = TRUE;
}
