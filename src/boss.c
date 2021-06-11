#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"
#include "explosion.h"
#include "player.h"
#include "boss.h"


// shooting

// boss one
void bossPatternOne(){
	// middle
	if(bossClock % 60 < 30 && bossClock % 3 == 0){
		if(bossClock % 60 == 0) bossInt1 = random() % 512;
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.angle = bossInt1,
			.speed = fix16Add(FIX16(4), cosFix16(bossInt1 * 2)),
			.type = bossClock % 6 == 0 ? 1 : 3,
		};
		bossInt1 += 128;
		void bUpdate(s16 i){
			if(bullets[i].clock == 5){
				bullets[i].speed = FIX16(3);
				updateEnemyBulletVelocity(i);
			} else if(bullets[i].clock == 10){
				bullets[i].speed = FIX16(0);
				updateEnemyBulletVelocity(i);
			} else if(bullets[i].clock == 30){
				bullets[i].velocity.x = honeEnemyBullet(bullets[i].pos.x, bullets[i].pos.y, 4, 32, TRUE);
				bullets[i].velocity.y = honeEnemyBullet(bullets[i].pos.x, bullets[i].pos.y, 4, 32, FALSE);
			}
		}
		spawnEnemyBullet(bSpawn, bUpdate);
	}
	// sides
	else if(bossClock % 60 >= 30 && bossClock % 10 == 0){
		struct bulletSpawner bSpawn = {
			.x = fix16Add(BOSS_B_X, bossClock % 120 < 60 ? BOSS_X_OFFSET : BOSS_X_OFFSET_NEG),
			.y = BOSS_B_Y,
			.type = bossClock % 120 < 60 ? 4 : 2,
		};
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 32, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 32, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
	}
}

// boss two
void bossPatternTwo(){
	if(bossClock % 3 == 0){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.speed = FIX16(4),
			.angle = 672 + random() % 192,
			.type = random() % 4 + 1,
			.int1 = 35
		};
		if(bSpawn.type % 2 == 1) bSpawn.int1 = 65;
		void bUpdate(s16 i){
			if(bullets[i].clock % 5 == 0 && bullets[i].clock <= bullets[i].int1){
				bullets[i].velocity.y = fix16Add(bullets[i].velocity.y, FIX16(1));
			}
		}
		spawnEnemyBullet(bSpawn, bUpdate);
	}
}
void bossPatternThree(){
	// spots
	if(bossClock % 120 < 60 && bossClock % 2 == 0){
		if(bossClock % 20 == 0){
			bossInt1 = random() % 192 + 32;
			bossInt2 = 32 + random() % 32;
		}
		struct bulletSpawner bSpawn = {
			.x = FIX16(bossInt1),
			.y = FIX16(bossInt2),
			.type = 1
		};
		if(bossClock % 120 >= 20 && bossClock % 120 < 40) bSpawn.type = 3;
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 92, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 0, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
	}
	// middle
	if(bossClock % 120 == 96){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.speed = FIX16(6),
			.angle = random() % 512,
			.type = 4
		};
		void bUpdate(s16 i){
			if(bullets[i].speed > FIX16(3) && bullets[i].clock % 10 == 0){
				bullets[i].speed = fix16Sub(bullets[i].speed, FIX16(1));
				updateEnemyBulletVelocity(i);
			}
		}
		for(s16 b = 0; b < 25; b++){
			if(bSpawn.angle % 1024 > 64 && bSpawn.angle % 1024 < 448) spawnEnemyBullet(bSpawn, bUpdate);
			bSpawn.angle += 41;
		}
	}
}

// boss three
void bossPatternFour(){
	// curvy
	if(bossClock % 30 == 0){
		if(bossClock % 60 == 0){
			bossInt1 = 768;
			bossInt2 = 0;
		}
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.speed = FIX16(0.5),
			.type = 1,
			.angle = bossInt1 + bossInt2,
			.flag1 = bossClock % 120 < 60 ? TRUE : FALSE,
		};
		bossInt2 += bSpawn.flag1 ? 32 : -32;
		if(bSpawn.flag1) bSpawn.type = 3;
		void bUpdate(s16 i){
			if(bullets[i].clock % 5 == 0){
				bullets[i].angle += bullets[i].flag1 ? 48 : -48;
				bullets[i].speed = fix16Add(bullets[i].speed, FIX16(0.5));
				updateEnemyBulletVelocity(i);
			}
		}
		for(s16 i = 0; i < 6; i++){
			spawnEnemyBullet(bSpawn, bUpdate);
			bSpawn.angle += bSpawn.flag1 ? 64 : -64;
		}
	}
	//middle
	if(bossClock % 120 == 60){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.speed = FIX16(5),
			.type = 4,
			.angle = random() % 512
		};
		void bUpdate(s16 i){
			if(bullets[i].clock % 5 == 0 && bullets[i].speed >= FIX16(3.5)){
				bullets[i].speed = fix16Sub(bullets[i].speed, FIX16(0.5));
				updateEnemyBulletVelocity(i);
			}
		}
		for(s16 i = 0; i < 16; i++){
			if(bSpawn.angle % 1024 > 64 && bSpawn.angle % 1024 < 448) spawnEnemyBullet(bSpawn, bUpdate);
			bSpawn.angle += 64;
		}
	}
}
void bossPatternFive(){
	// spray
	if(bossClock % 15 == 0){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.speed = FIX16(6),
			.type = 1,
			.flag1 = bossClock % 30 == 0 ? TRUE : FALSE
		};
		if(bSpawn.flag1) bSpawn.type = 3;
		bSpawn.angle = bSpawn.flag1 ? 512 : 0;
		void bUpdate(s16 i){
			if(bullets[i].clock % 5 == 0 && bullets[i].clock > 0){
				bullets[i].angle += bullets[i].flag1 ? -32 : 32;
				if(bullets[i].clock <= 10) bullets[i].speed = fix16Sub(bullets[i].speed, FIX16(1));
				updateEnemyBulletVelocity(i);
			}
		}
		for(s16 i = 0; i < 6; i++){
			spawnEnemyBullet(bSpawn, bUpdate);
			bSpawn.angle += bSpawn.flag1 ? -64 : 64;
		}
	}
	// homing
	if(bossClock % 30 == 25){
		struct bulletSpawner bSpawn = {
			.x = FIX16(random() % 192 + 32),
			.y = FIX16(32 + random() % 32),
			.type = 2
		};
		if(bossClock % 60 == 25) bSpawn.type = 4;
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 3, 0, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 3, 0, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
	}
}

// boss four
void bossPatternSix(){
	if(bossClock % 60 < 30 && bossClock % 15 == 0){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.speed = FIX16(4.5),
			.type = 4,
			.angle = random() % 1024,
			.flag1 = bossClock % 30 == 0
		};
		if(bSpawn.flag1) bSpawn.type = 2;
		void bUpdate(s16 i){
			if(bullets[i].clock % 5 == 0 && bullets[i].clock < 40){
				bullets[i].angle += bullets[i].flag1 ? 64 : -64;
				updateEnemyBulletVelocity(i);
			}
		}
		for(s16 i = 0; i < 14; i++){
			spawnEnemyBullet(bSpawn, bUpdate);
			bSpawn.angle += 73;
		}
	}
}
void bossPatternSeven(){
	if(bossClock % 50 == 0){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.type = 2
		};
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 2, 0, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 2, 0, FALSE);
		void bUpdate(s16 i){
			if(bullets[i].clock % 30 == 15 && bullets[i].clock < 60){
				struct bulletSpawner bSpawn = {
					.x = bullets[i].pos.x,
					.y = bullets[i].pos.y,
					.type = 3,
					.angle = random() % 1024,
					.speed = FIX16(3),
					.flag1 = bullets[i].pos.x < playerPos.x
				};
				void bbUpdate(s16 h){
					if(bullets[h].clock % 5 == 0 && bullets[h].clock < 60){
						bullets[h].angle += bullets[h].flag1 ? -32 : 32;
						// bullets[h].speed = fix16Add(bullets[h].speed, FIX16(0.25));
						updateEnemyBulletVelocity(h);
					}
				}
				for(s16 h = 0; h < 8; h++){
					spawnEnemyBullet(bSpawn, bbUpdate);
					bSpawn.angle += 128;
				}
			}
		}
		spawnEnemyBullet(bSpawn, bUpdate);
	}
}


void shootBoss(){
	bossPatternOne();
}


// collision

void hitBoss(){
	bossHealth--;
	if(bossHealth <= 0) finishBoss();
}

void collideBoss(){
	for(s16 j = 0; j < PLAYER_BULLET_LIMIT; j++) if(playerBullets[j].active) {
		bossCollisionDistance = getApproximatedDistance(
			fix32Sub(fix16ToFix32(playerBullets[j].pos.x), BOSS_X),
			fix32Sub(fix16ToFix32(playerBullets[j].pos.y), BOSS_Y));
		if(bossCollisionDistance < BOSS_COLLIDE_OFFSET){
			spawnExplosion(fix16ToInt(playerBullets[j].pos.x), fix16ToInt(playerBullets[j].pos.y), TRUE);
			hitBoss();
			removePlayerBullet(j);
		}
	}
}

void finishBoss(){
	bossActive = FALSE;
	bossLoaded = FALSE;
	zoneOver = TRUE;
	bossClock = 0;
}


// loop

void loadBoss(){
	bossType++;
	bossLoaded = FALSE;
	bossActive = TRUE;
	bossHealth = 25;
	bossMax = bossHealth;
}

void updateBoss(){
	if(bossActive) {
		if(bossLoaded){
			collideBoss();
			shootBoss();
		} else if(bossClock == BOSS_LOAD_TIME){
			VDP_drawImageEx(BG_A, 
				(bossType == 1 ? &roll : (bossType == 2 ? &waffle : (bossType == 3 ? &cake : &parfait))), 
				TILE_ATTR_FULL(PAL1, 0, 0, 0, 92), 12, 5, 0, DMA_QUEUE);
			bossLoaded = TRUE;
			bossClock = -1;
		}
		bossClock++;
		if(bossClock >= 600) bossClock = 0;
	}
}