#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"
#include "yin.h"


// movement

void moveYinHorizontal(s16 i){
	yins[i].pos.x += yins[i].flag1 ? 0 - YIN_SPEED : YIN_SPEED;
	if(yins[i].pos.x >= GAME_WIDTH - 10){
		yins[i].flag1 = TRUE;
		SPR_setHFlip(yins[i].image, 1);
	} else if(yins[i].pos.x <= 10){
		yins[i].flag1 = FALSE;
		SPR_setHFlip(yins[i].image, 0);
	}
}

void moveYinVertical(s16 i){
	yins[i].pos.y += yins[i].flag1 ? 0 - YIN_SPEED : YIN_SPEED;
	if(yins[i].pos.y >= 176){
		yins[i].flag1 = TRUE;
	} else if(yins[i].pos.y <= 56){
		yins[i].flag1 = FALSE;
	}
}


// shooting

void yinPatternOne(s16 i){
	if(yins[i].clock % 80 == 40){
		struct bulletSpawner bSpawn = {
			.x = FIX16(yins[i].pos.x),
			.y = FIX16(yins[i].pos.y),
			.type = 1
		};
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 3, 0, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 3, 0, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
	}
}

// void yinPatternTwo(s16 i){
// 	if(yins[i].clock % 80 < 40 && yins[i].clock % 20 == 0){
// 		if(yins[i].clock % 80 == 0){
// 			yins[i].int1 = random() % 1024;
// 			yins[i].int2 = yins[i].pos.x + 4;
// 			yins[i].int3 = yins[i].pos.y + 4;
// 			yins[i].flag2 = random() % 2 < 1;
// 		}
// 		struct bulletSpawner bSpawn = {
// 			.x = FIX16(yins[i].int2),
// 			.y = FIX16(yins[i].int3),
// 			.type = 1,
// 			.angle = yins[i].int1,
// 			.speed = FIX16(4),
// 			.flag1 = yins[i].flag2
// 		};
// 		void bUpdate(s16 bI){
// 			if(bullets[bI].clock % 5 == 0){
// 				if(bullets[bI].clock >= 15 && bullets[bI].clock < 30){
// 					bullets[bI].angle += bullets[bI].flag1 ? -64 : 64;
// 					updateEnemyBulletVelocity(bI);
// 				} else if(bullets[bI].clock >= 30 && bullets[bI].clock < 60){
// 					bullets[bI].angle -= bullets[bI].flag1 ? -64 : 64;
// 					updateEnemyBulletVelocity(bI);
// 				}
// 			}
// 		}
// 		for(s16 j = 0; j < 6; j++){
// 			spawnEnemyBullet(bSpawn, bUpdate);
// 			bSpawn.angle += 171;
// 		}
// 	}
// }

// void yinPatternThree(s16 i){
// 	if(yins[i].clock % 40 == 0){
// 		struct bulletSpawner bSpawn = {
// 			.x = FIX16(yins[i].pos.x + 4),
// 			.y = FIX16(yins[i].pos.y + 4),
// 			.type = 1,
// 			.speed = FIX16(5),
// 			.angle = random() % 1024,
// 			.flag1 = yins[i].horizontal
// 		};
// 		void bUpdate(s16 bI){
// 			if(bullets[bI].clock % 5 == 0 && bullets[bI].speed > FIX16(0)){
// 				bullets[bI].speed = fix16Sub(bullets[bI].speed, FIX16(1));
// 				updateEnemyBulletVelocity(bI);
// 			} else if(bullets[bI].clock == 30){
// 				bullets[bI].velocity.x = honeEnemyBullet(bullets[bI].pos.x, bullets[bI].pos.y, 4, bullets[bI].flag1 ? 48 : 0, TRUE);
// 				bullets[bI].velocity.y = honeEnemyBullet(bullets[bI].pos.x, bullets[bI].pos.y, 4, bullets[bI].flag1 ? 0 : 48, FALSE);
// 			}
// 		}
// 		for(s16 j = 0; j < 5; j++){
// 			spawnEnemyBullet(bSpawn, bUpdate);
// 			bSpawn.angle += 205;
// 		}
// 	}
// }

void yinPatternTwo(s16 i){
	if(yins[i].clock % 40 == 20){
		struct bulletSpawner bSpawn = {
			.x = FIX16(yins[i].pos.x),
			.y = FIX16(yins[i].pos.y),
			.type = yins[i].clock % 80 == 20 ? 2 : 1
		};
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, bSpawn.type == 1 ? 4 : 3, bSpawn.type == 1 ? 32 : 0, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, bSpawn.type == 1 ? 4 : 3, bSpawn.type == 1 ? 32 : 0, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
	}
}

void yinPatternThree(s16 i){
	if(yins[i].clock % 80 >= 20 && yins[i].clock % 80 < 40 && yins[i].clock % 4 == 0){
		struct bulletSpawner bSpawn = {
			.x = FIX16(yins[i].pos.x),
			.y = FIX16(yins[i].pos.y),
			.type = yins[i].clock % 8 == 0 ? 2 : 1
		};
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, bSpawn.type == 1 ? 5 : 4, yins[i].clock % 80 == 20 ? 0 : 32, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, bSpawn.type == 1 ? 5 : 4, yins[i].clock % 80 == 20 ? 0 : 32, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
	}
}

void yinShoot(s16 i){
	if((!yins[i].horizontal && !yins[i].last && yins[i].clock % 240 < 80) ||
		(yins[i].horizontal && yins[i].clock % 240 >= 80 && yins[i].clock % 240 < 160) ||
		(yins[i].last && yins[i].clock % 240 >= 160)){
		// if(currentZone < 5) yinPatternOne(i);
		// else if(currentZone < 10) yinPatternTwo(i);
		// else yinPatternThree(i);
		yinPatternThree(i);
	}
}


// loop

void loadYins(){
	for(s16 i = 0; i < YIN_COUNT; i++){
		yins[i].pos.x = i == 0 ? 6 : (i == 2 ? 251 : 96);
		yins[i].pos.y = i % 2 == 0 ? 96 : 24;
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
		yins[i].pos.x = GAME_WIDTH + 32;
		yins[i].pos.y = 64;
		SPR_releaseSprite(yins[i].image);
	}
}

void updateYins(){
	for(s16 i = 0; i < YIN_COUNT; i++){
		if(yins[i].clock % yins[i].speed == 0) yins[i].horizontal ? moveYinHorizontal(i) : moveYinVertical(i);
		else if(yins[i].clock % yins[i].speed == 1) SPR_setPosition(yins[i].image, yins[i].pos.x - 4, yins[i].pos.y - 4);
		if(yins[i].clock % 5 == 0 && yins[i].speed > 2) yins[i].speed--;
		zoneOver ? SPR_setVisibility(yins[i].image, HIDDEN) : yinShoot(i);
		if(!zoneOver) yins[i].clock++;
		if(yins[i].clock >= 240) yins[i].clock = 0;
	}
}