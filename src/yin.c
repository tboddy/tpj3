#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "explosion.h"
#include "enemies.h"
#include "yin.h"


// movement

void moveYinHorizontal(s8 i){
	yins[i].pos.x += yins[i].flag1 ? 0 - YIN_SPEED : YIN_SPEED;
	if(yins[i].pos.x >= GAME_WIDTH - 10){
		yins[i].flag1 = TRUE;
		SPR_setHFlip(yins[i].image, 1);
	} else if(yins[i].pos.x <= 10){
		yins[i].flag1 = FALSE;
		SPR_setHFlip(yins[i].image, 0);
	}
}

void moveYinVertical(s8 i){
	yins[i].pos.y += yins[i].flag1 ? 0 - YIN_SPEED : YIN_SPEED;
	if(yins[i].pos.y >= 112){
		yins[i].flag1 = TRUE;
	} else if(yins[i].pos.y <= 56){
		yins[i].flag1 = FALSE;
	}
}


// shooting

void yinPatternOne(s8 i){
	if(yins[i].clock % 80 == 40){
		struct bulletSpawner bSpawn = {
			.x = FIX16(yins[i].pos.x),
			.y = FIX16(yins[i].pos.y),
			.type = 1
		};
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, yinBulletSpeed, 0, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, yinBulletSpeed, 0, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
		spawnExplosion(yins[i].pos.x, yins[i].pos.y, FALSE);
	}
}

void yinPatternTwo(s8 i){
	if(yins[i].clock % 40 == 20){
		struct bulletSpawner bSpawn = {
			.x = FIX16(yins[i].pos.x),
			.y = FIX16(yins[i].pos.y),
			.type = yins[i].clock % 80 == 20 ? 2 : 1
		};
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, yinBulletSpeed, bSpawn.type == 1 ? 32 : 0, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, yinBulletSpeed, bSpawn.type == 1 ? 32 : 0, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
		spawnExplosion(yins[i].pos.x, yins[i].pos.y, FALSE);
	}
}

void yinPatternThree(s8 i, s8 count){
	if(yins[i].clock % 80 >= 20 && yins[i].clock % 80 < 30 && yins[i].clock % 5 == 0){
		struct bulletSpawner bSpawn = {
			.x = FIX16(yins[i].pos.x),
			.y = FIX16(yins[i].pos.y),
			.type = yins[i].clock % 8 == 0 ? 2 : 1,
			.int1 = 64
		};
		for(s8 b = 0; b < count; b++){
			bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, yinBulletSpeed, yins[i].horizontal ? bSpawn.int1 : 0, TRUE);
			bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, yinBulletSpeed, yins[i].horizontal ? 0 : bSpawn.int1, FALSE);
			spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.type = bSpawn.type == 2 ? 1 : 2;
			bSpawn.int1 += 16;
		}
	}
}

void yinShoot(s8 i){
	if((!yins[i].horizontal && !yins[i].last && yins[i].clock % 240 < 80) ||
		(yins[i].horizontal && yins[i].clock % 240 >= 80 && yins[i].clock % 240 < 160) ||
		(yins[i].last && yins[i].clock % 240 >= 160)){
		if(currentZone == 1) yinPatternOne(i);
		else if(currentZone < 5) yinPatternTwo(i);
		else if(currentZone < 10) yinPatternThree(i, 1);
		else if(currentZone < 15) yinPatternThree(i, 2);
		else yinPatternThree(i, 3);
	}
}


// loop

void loadYins(){
	if(currentZone % 5 == 1 && currentZone > 1) yinBulletSpeed++;
	for(s16 i = 0; i < YIN_COUNT; i++){
		yins[i].pos.x = i == 0 ? 6 : (i == 2 ? 251 : 128);
		yins[i].pos.y = i % 2 == 0 ? (i == 0 ? 64 : 96) : 21;
		yins[i].speed = 20;
		yins[i].horizontal = i % 2 == 1;
		yins[i].last = i % 3 == 2;
		yins[i].clock = 0;
		yins[i].image = SPR_addSprite(&imgYin1, yins[i].pos.x, yins[i].pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
		if(yins[i].last) yins[i].flag1 = TRUE;
		SPR_setDepth(yins[i].image, 1);
	}
}

void resetYins(){
	for(s16 i = 0; i < YIN_COUNT; i++){
		yins[i].pos.x = i == 0 ? 6 : (i == 2 ? 251 : 128);
		yins[i].pos.y = i % 2 == 0 ? (i == 0 ? 64 : 96) : 21;
		SPR_releaseSprite(yins[i].image);
	}
}

void updateYins(){
	for(s16 i = 0; i < YIN_COUNT; i++){
		if(yins[i].clock % yins[i].speed == 0) yins[i].horizontal ? moveYinHorizontal(i) : moveYinVertical(i);
		else if(yins[i].clock % yins[i].speed == 1) SPR_setPosition(yins[i].image, yins[i].pos.x - 4, yins[i].pos.y - 4);
		if(yins[i].clock % 5 == 0 && yins[i].speed > 2) yins[i].speed--;
		if(zoneOver) SPR_setVisibility(yins[i].image, HIDDEN);
		else if(!gameOver) yinShoot(i);
		if(!zoneOver) yins[i].clock++;
		if(yins[i].clock >= 240) yins[i].clock = 0;
	}
}