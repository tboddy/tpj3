#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"
#include "yin.h"


// movement

void moveYinHorizontal(s16 i){
	yins[i].pos.x += yins[i].flag1 ? 0 - YIN_SPEED : YIN_SPEED;
	if(yins[i].pos.x >= GAME_WIDTH - 16){
		yins[i].flag1 = TRUE;
		SPR_setHFlip(yins[i].image, 1);
	} else if(yins[i].pos.x <= 8){
		yins[i].flag1 = FALSE;
		SPR_setHFlip(yins[i].image, 0);
	}
}

void moveYinVertical(s16 i){
	yins[i].pos.y += yins[i].flag1 ? 0 - YIN_SPEED : YIN_SPEED;
	if(yins[i].pos.y >= 208){
		yins[i].flag1 = TRUE;
	} else if(yins[i].pos.y <= 24){
		yins[i].flag1 = FALSE;
	}
}


// shooting

void yinShoot(s16 i){

	void patternOne(){ // homing vomit
		if(yins[i].clock % 40 == 0){
			struct bulletSpawner bSpawn = {
				.x = FIX16(yins[i].pos.x + 4),
				.y = FIX16(yins[i].pos.y + 4),
				.type = 1
			};
			bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 3, yins[i].horizontal ? 64 : 0, TRUE);
			bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 3, yins[i].horizontal ? 0 : 64, FALSE);
			spawnEnemyBullet(bSpawn, eUpdate);
		}
	}

	void patternTwo(){ // curvy ring
		if(yins[i].clock % 80 < 40 && yins[i].clock % 20 == 0){
			if(yins[i].clock % 80 == 0){
				yins[i].int1 = random() % 1024;
				yins[i].int2 = yins[i].pos.x + 4;
				yins[i].int3 = yins[i].pos.y + 4;
				yins[i].flag2 = random() % 2 < 1;
			}
			struct bulletSpawner bSpawn = {
				.x = FIX16(yins[i].int2),
				.y = FIX16(yins[i].int3),
				.type = 1,
				.angle = yins[i].int1,
				.speed = FIX16(5),
				.flag1 = yins[i].flag2
			};
			void bUpdate(s16 bI){
				if(bullets[bI].clock % 5 == 0){
					if(bullets[bI].clock >= 15 && bullets[bI].clock < 30){
						bullets[bI].angle += bullets[bI].flag1 ? -64 : 64;
						updateEnemyBulletVelocity(bI);
					} else if(bullets[bI].clock >= 30 && bullets[bI].clock < 60){
						bullets[bI].angle -= bullets[bI].flag1 ? -64 : 64;
						updateEnemyBulletVelocity(bI);
					}
				}
			}
			for(s16 j = 0; j < 8; j++){
				spawnEnemyBullet(bSpawn, bUpdate);
				bSpawn.angle += 128;
			}
		}
	}

	void patternThree(){ // homing ring
		if(yins[i].clock % 40 == 0){
			struct bulletSpawner bSpawn = {
				.x = FIX16(yins[i].pos.x + 4),
				.y = FIX16(yins[i].pos.y + 4),
				.type = 1,
				.speed = FIX16(5),
				.angle = yins[i].horizontal ? 0 : (yins[i].last ? 256 : 768)
			};
			void bUpdate(s16 bI){
				if(bullets[bI].clock % 5 == 0 && bullets[bI].speed > FIX16(0)){
					bullets[bI].speed = fix16Sub(bullets[bI].speed, FIX16(1));
					updateEnemyBulletVelocity(bI);
				} else if(bullets[bI].clock == 30){
					bullets[bI].velocity.x = honeEnemyBullet(bullets[bI].pos.x, bullets[bI].pos.y, 5, 48, TRUE);
					bullets[bI].velocity.y = honeEnemyBullet(bullets[bI].pos.x, bullets[bI].pos.y, 5, 48, FALSE);
				}
			}
			for(s16 j = 0; j < 6; j++){
				if(j > 0) spawnEnemyBullet(bSpawn, bUpdate);
				bSpawn.angle += 83;
				if(j > 1) bSpawn.angle++;
			}
		}
	}

	if(yins[i].clock % 10 == 0){
		if((!yins[i].horizontal && !yins[i].last && yins[i].clock % 240 < 80) ||
			(yins[i].horizontal && yins[i].clock % 240 >= 80 && yins[i].clock % 240 < 160) ||
			(yins[i].last && yins[i].clock % 240 >= 160)) patternOne();
	}
}


// loop

void loadYins(){
	for(s16 i = 0; i < YIN_COUNT; i++){
		yins[i].pos.x = i == 0 ? 3 : (i == 2 ? GAME_WIDTH - 10 : random() % 256 + 32);
		yins[i].pos.y = i % 2 == 0 ? i == 0 ? 32 : 96 : 19;
		yins[i].speed = 20;
		yins[i].horizontal = i % 2 == 1;
		yins[i].last = i % 3 == 2;
		yins[i].image = SPR_addSprite(&imgYin1, yins[i].pos.x, yins[i].pos.y, TILE_ATTR(PAL1, 1, FALSE, FALSE));
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
		else if(yins[i].clock % yins[i].speed == 1) SPR_setPosition(yins[i].image, yins[i].pos.x, yins[i].pos.y);
		if(yins[i].clock % 5 == 0 && yins[i].speed > 2) yins[i].speed--;
		zoneOver ? SPR_setVisibility(yins[i].image, HIDDEN) : yinShoot(i);
		yins[i].clock++;
		if(yins[i].clock >= 240) yins[i].clock = 0;
	}
}