#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"
#include "explosion.h"
#include "player.h"
#include "boss.h"


// shooting

void bossPatternOne(){
	if(bossClock % 10 == 0 && bossClock % 60 <= 50){
		if(bossClock % 60 == 0) bossInt1 = random() % 1024;
		struct bulletSpawner bSpawn = {
			.x = FIX16(bossClock % 120 < 60 ? 208 : 48),
			.y = BOSS_B_Y,
			.type = 1,
			.angle = bossInt1,
			.speed = FIX16(5)
		};
		for(s8 b = 0; b < 8; b++){
			if(bSpawn.angle % 1024 >= 0 && bSpawn.angle % 1024 <= 512) spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.angle += 128;
		}
		bossInt1 += bossClock % 120 < 60 ? 32 : -32;
		if(bossClock % 30 == 0) spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		if(bossClock % 20 == 10){
			bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 96, TRUE);
			bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 16, FALSE);
			bSpawn.type = 4;
			spawnEnemyBullet(bSpawn, eUpdate);
		}
	}
}

void bossPatternTwo(){
	if(bossClock % 60 == 0){
		bossInt1 = 240 + random() % 32;
		bossInt2 = bossClock % 120 == 0 ? 48 : -48;
		bossInt3 = bossInt2 / 2;
	}
	if(bossClock % 5 == 0){
		struct bulletSpawner bSpawn = {
			.x = FIX16(bossClock % 120 < 60 ? 208 : 48),
			.y = BOSS_B_Y,
			.type = 4,
			.angle = bossInt1 - bossInt2,
			.speed = FIX16(5.5)
		};
		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		for(s8 b = 0; b < 3; b++){
			spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.speed = fix16Add(bSpawn.speed, FIX16(1.5));
			bSpawn.angle += bossInt3;
		}
		bossInt1 += bossInt2;
	}
}

void bossPatternThree(){
	if(bossClock % 60 < 18 && bossClock % 6 == 0){
		if(bossClock % 60 == 0){
			bossInt1 = 3; 
			bossInt2 = bossClock % 120 == 0 ? 68 : -68;
			bossInt3 = bossClock % 120 == 0 ? 224 : 288;
			bossFix1 = FIX16(bossClock % 120 < 60 ? 208 : 48);
		}
		struct bulletSpawner bSpawn = {
			.x = bossFix1,
			.y = BOSS_B_Y,
			.type = 3,
			.angle = bossInt3,
			.speed = FIX16(bossInt1)
		};
		if(bossClock % 60 == 0) spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		for(s8 b = 0; b < 4; b++){
			spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.angle += bossInt2;
		}
		bossInt1++;
	}
	else if(bossClock % 60 >= 30 && bossClock % 5 == 0){
		if(bossClock % 60 == 30){
			bossFix1 = FIX16(32 + random() % 192);
			spawnExplosion(fix16ToInt(bossFix1), fix16ToInt(BOSS_B_Y), FALSE);
		}
		struct bulletSpawner bSpawn = {
			.x = bossFix1,
			.y = BOSS_B_Y,
			.type = 2
		};
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 96, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 16, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
	}
}

void bossPatternFour(){
	if(bossClock % 60 <= 6 && bossClock % 3 == 0){
		if(bossClock % 60 == 0) bossInt1 = 4;
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.speed = FIX16(bossInt1)
		};
		bSpawn.angle = bossClock % 60 == 3 ? 32 : 0;
		bSpawn.type = bossClock % 60 == 0 ? 3 : 4;
		for(s8 b = 0; b < (bossClock % 60 == 3 ? 5 : 6); b++){
			bSpawn.angle += 64;
			if(b > 0) spawnEnemyBullet(bSpawn, eUpdate);
		}
		bossInt1++;
	} else if(bossClock % 60 >= 30 && bossClock % 5 == 0){
		struct bulletSpawner bSpawn = {
			.x = FIX16(bossClock % 10 == 0 ? 208 : 48),
			.y = BOSS_B_Y,
			.type = 1
		};
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 96, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 16, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
	}
}

void bossPatternFive(){
	if(bossClock % 60 == 0){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.angle = random() % 1024,
			.speed = FIX16(4),
			.type = 4
		};
		for(s8 b = 0; b < 16; b++){
			if(bSpawn.angle % 1024 > 0 && bSpawn.angle % 1024 < 512){
				spawnEnemyBullet(bSpawn, eUpdate);
			}
			bSpawn.angle += 64;
		}
	} else if(bossClock % 60 >= 30 && bossClock % 60 < 45 && bossClock % 3 == 0){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.type = bossClock % 60 >= 38 ? 3 : 4
		};
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 5, 128, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 5, 16, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
	}
	if(bossClock % 60 >= 30 && bossClock % 3 == 0){
		struct bulletSpawner bSpawn = {
			.x = FIX16(bossClock % 30 < 15 ? 208 : 48),
			.y = BOSS_B_Y,
			.type = bossClock % 15 > 6 ? 1 : 2
		};
		if(bossClock % 15 == 0){
			bossFix1 = bSpawn.x;
			bossFix2 = bSpawn.y;
		}
		if(bossClock % 5 == 0) spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		bSpawn.velocityX = honeEnemyBullet(bossFix1, bossFix2, 4, 32, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bossFix1, bossFix2, 4, 16, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
	}
}

void bossPatternSix(){
	if(bossClock % 3 == 0 && bossClock % 120 < 110){
		if(bossClock % 120 == 0){
			bossInt1 = 0 + random() % 32;
			bossInt2 = 512 - random() % 32;
			bossInt3 = 1;
		}
		struct bulletSpawner bSpawn = {
			.x = FIX16(48),
			.y = BOSS_B_Y,
			.angle = bossInt1,
			.speed = FIX16(7),
			.type = bossClock % 240 < 120 ? 4 : 2 
		};
		if(bossClock % 6 == 0) spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		for(s8 b = 0; b < 2; b++){
			if(bSpawn.angle % 1024 < 512) spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.angle += 512;
		}
		bSpawn.x = FIX16(208);
		bSpawn.angle = bossInt2;
		if(bossClock % 6 == 3) spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		for(s8 b = 0; b < 2; b++){
			if((bSpawn.angle < 0 && abs(bSpawn.angle) % 1024 > 512) || (bSpawn.angle >= 0 && bSpawn.angle < 512)) spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.angle += 512;
		}
		bossInt1 += 5 * bossInt3;
		bossInt2 -= 10 * bossInt3;
		bossInt3++;
	}
}

void bossPatternSeven(){
	if(bossClock % 120 < 100){
		if(bossClock % 120 == 0) bossInt1 = 0;
		if(bossClock % 12 == 0){
			struct bulletSpawner bSpawn = {
				.x = BOSS_B_X,
				.y = BOSS_B_Y,
				.angle = 0 + bossInt1,
				.speed = FIX16(8),
				.type = 2
			};
			for(s8 b = 0; b < 16; b++){
				if(bSpawn.angle % 1024 > 32 && bSpawn.angle % 1024 < 480) spawnEnemyBullet(bSpawn, eUpdate);
				bSpawn.angle += 64;
			}
			bossInt1 += 24;
		} else if(bossClock % 6 == 3){
			struct bulletSpawner bSpawn = {
				.x = BOSS_B_X,
				.y = BOSS_B_Y,
				.type = 3
			};
			bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 5, 128, TRUE);
			bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 5, 16, FALSE);
			spawnEnemyBullet(bSpawn, eUpdate);
		}
	}
}

void bossPatternEight(){
	if(bossClock % 30 == 0){
		struct bulletSpawner bSpawn = {
			.x = FIX16(bossClock % 60 == 0 ? 208 : 48),
			.y = BOSS_B_Y,
			.angle = random() % 1024,
			.speed = FIX16(8),
			.type = 1
		};
		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		for(s8 b = 0; b < 8; b++){
			if(bSpawn.angle % 1024 > 0 && bSpawn.angle % 1024 < 512){
				spawnEnemyBullet(bSpawn, eUpdate);
				bSpawn.angle += 24;
				spawnEnemyBullet(bSpawn, eUpdate);
				bSpawn.angle += 24;
				spawnEnemyBullet(bSpawn, eUpdate);
			} else bSpawn.angle += 48;
			bSpawn.angle += 80;
		}
	} else if(bossClock % 30 == 15){
		struct bulletSpawner bSpawn = {
			.x = FIX16(bossClock % 60 == 15 ? 192 : 64),
			.y = BOSS_B_Y,
			.angle = random() % 1024,
			.speed = FIX16(6),
			.type = 4
		};
		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		for(s8 b = 0; b < 16; b++){
			if(bSpawn.angle % 1024 > 0 && bSpawn.angle % 1024 < 512) spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.angle += 64;
		}
	}
}

void bossPatternNine(){
	if(bossClock % 60 < 45 && bossClock % 5 == 0){
		struct bulletSpawner bSpawn = {
			.x = FIX16(64 + random() % 128),
			.y = BOSS_B_Y,
			.type = 3
		};
		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		for(s8 b = 0; b < 4; b++){
			bSpawn.type = b % 2 == 0 ? 3 : 4;
			bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 5, 192, TRUE);
			bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 5, 8, FALSE);
			spawnEnemyBullet(bSpawn, eUpdate);
		}
	}
}

void bossPatternTen(){
	if(bossClock % 15 == 0){
		struct bulletSpawner bSpawn = {
			.x = FIX16(64 + random() % 128),
			.y = BOSS_B_Y,
			.type = bossClock % 30 == 0 ? 4 : 3,
			.angle = random() % 1024,
			.speed = FIX16(bossClock % 30 == 0 ? 7 : 5)
		};
		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		for(s8 b = 0; b < 16; b++){
			if(bSpawn.angle % 1024 > 0 && bSpawn.angle % 1024 < 512) spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.angle += 64;
		}
	}
	else if(bossClock % 60 > 15 && bossClock % 60 < 30 && bossClock % 2 == 0){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.type = bossClock % 4 == 0 ? 2 : 1
		};
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 6, 96, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 6, 8, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
	}
}

void bossPatternEleven(){
	if(bossClock % 60 < 30 && bossClock % 4 == 0){
		struct bulletSpawner bSpawn = {
			.x = FIX16(bossClock % 120 < 60 ? 208 : 48),
			.y = BOSS_B_Y,
			.type = 3
		};
		if(bossClock % 60 == 0) bossInt1 = 4;
		if(bossClock % 60 == 0 || bossClock % 60 == 12) spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, bossInt1, 64, TRUE);
		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, bossInt1, 8, FALSE);
		spawnEnemyBullet(bSpawn, eUpdate);
		bossInt1++;
	}
	if(bossClock % 15 == 5){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.type = 2,
			.angle = bossClock % 30 == 5 ? 32 : 0,
			.speed = FIX16(6)
		};
		for(s8 b = 0; b < 16; b++){
			if(bSpawn.angle % 1024 > 0 && bSpawn.angle % 1024 < 512) spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.angle += 64;
		}
	}
}

void bossPatternTwelve(){
	if(bossClock % 60 < 35 && bossClock % 5 == 0){
		if(bossClock % 60 == 0){
			bossInt1 = 320;
			bossInt2 = 192;
		}
		struct bulletSpawner bSpawn = {
			.x = FIX16(bossClock % 10 == 0 ? 208 : 48),
			.y = BOSS_B_Y,
			.speed = FIX16(7),
			.angle = bossClock % 10 == 0 ? bossInt2 : bossInt1,
			.type = 4
		};
		for(s8 b = 0; b < 4; b++){
			spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.angle += bossClock % 10 == 0 ? 64 : -64;
		}
		bossInt1 -= 8;
		bossInt2 += 8;
	}
	if(bossClock % 2 == 1 && bossClock % 30 < 15){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.type = 1
		};
		if(bossClock % 30 == 1){
			bossFix1 = honeEnemyBullet(bSpawn.x, bSpawn.y, 7, 0, TRUE);
			bossFix2 = honeEnemyBullet(bSpawn.x, bSpawn.y, 7, 0, FALSE);
		}
		bSpawn.velocityX = bossFix1;
		bSpawn.velocityY = bossFix2;
		spawnEnemyBullet(bSpawn, eUpdate);
	}
}

void bossPatternThirteen(){ // 8:09
	if(bossClock % 4 == 0){
		if(bossClock == 0){
			bossInt1 = 0;
			bossInt2 = 1024;
		}
		struct bulletSpawner bSpawn = {
			.x = FIX16(bossClock % 8 == 0 ? 208 : 48),
			.y = BOSS_B_Y,
			.type = 3,
			.angle = bossClock % 8 ? bossInt2 : bossInt1,
			.speed = FIX16(6)
		};
		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
		for(s8 b = 0; b < 5; b++){
			if(bSpawn.angle % 1024 > 0 && bSpawn.angle % 1024 < 512) spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.angle += 205;
		}
		bossInt1 += 19;
		bossInt2 -= 15;
		if(bossInt1 >= 1024) bossInt1 = 0;
		if(bossInt2 <= 0) bossInt2 = 1024;
	}
	if(bossClock % 60 == 35 || bossClock % 60 == 36){
		struct bulletSpawner bSpawn = {
			.x = BOSS_B_X,
			.y = BOSS_B_Y,
			.type = bossClock % 60 == 35 ? 2 : 1,
			.angle = bossClock % 60 == 35 ? 0 : 32,
			.speed = FIX16(bossClock % 60 == 35 ? 5 : 8)
		};
		for(s8 b = 0; b < 8; b++){
			if(b > 0 && (bossClock % 60 == 35 || (bossClock % 60 == 36 && b < 7))) spawnEnemyBullet(bSpawn, eUpdate);
			bSpawn.angle += 64;
		}
	}
}

void hitBossPattern(u8 i){
	if(!hitBossPatterns[i]){
		hitBossPatterns[i] = TRUE;
		bossClock = BOSS_SWITCH_TIME;
		killBullets = TRUE;
	}
}

void shootBoss(){
	switch(bossType){
		case 1:
			if(bossHealth < 50){
				hitBossPattern(0);
				if(bossClock >= 0) bossPatternTwo();
			} else if(bossClock >= 0) bossPatternOne();
			break;
		case 2:
			if(bossHealth < 50){
				hitBossPattern(2);
				if(bossClock >= 0) bossPatternFive();
			} else if(bossHealth < 100){
				hitBossPattern(1);
				if(bossClock >= 0) bossPatternFour();
			} else if(bossClock >= 0) bossPatternThree();
			break;
		case 3:
			if(bossHealth < 50){
				hitBossPattern(4);
				if(bossClock >= 0) bossPatternEight();
			} else if(bossHealth < 100){
				hitBossPattern(3);
				if(bossClock >= 0) bossPatternSeven();
			} else if(bossClock >= 0) bossPatternSix();
			break;
		case 4:
			if(bossHealth < 50){
				hitBossPattern(8);
				if(bossClock >= 0) bossPatternThirteen();
			} else if(bossHealth < 100){
				hitBossPattern(7);
				if(bossClock >= 0) bossPatternTwelve();
			} else if(bossHealth < 150){
				hitBossPattern(6);
				if(bossClock >= 0) bossPatternEleven();
			} else if(bossHealth < 200){
				hitBossPattern(5);
				if(bossClock >= 0) bossPatternTen();
			} else if(bossClock >= 0) bossPatternNine();
			break;
	}
}


// collision

void hitBoss(){
	// bossHealth--;
	bossHealth -= 2;
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
	bossClock = BOSS_SWITCH_TIME;
}


// loop

void loadBoss(){
	bossType++;
	// bossType = 3;
	switch(bossType){
		case 1:
			bossHealth = 100;
			break;
		case 2:
			bossHealth = 150;
			break;
		case 3:
			bossHealth = 150;
			break;
		case 4:
			bossHealth = 250;
			break;
	}
	bossLoaded = FALSE;
	bossActive = TRUE;
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
				TILE_ATTR_FULL(PAL1, 0, 0, 0, 92), 12, 4, 0, DMA_QUEUE);
			bossLoaded = TRUE;
			bossClock = -1;
		}
		bossClock++;
		if(bossClock >= 600) bossClock = 0;
	}
}





// boss one

// boss two
// void bossPatternOne(){
// 	if(bossClock % 3 == 0){
// 		struct bulletSpawner bSpawn = {
// 			.x = BOSS_B_X,
// 			.y = BOSS_B_Y,
// 			.speed = FIX16(4),
// 			.angle = 672 + random() % 192,
// 			.type = random() % 4 + 1,
// 			.int1 = 35
// 		};
// 		if(bSpawn.type % 2 == 1) bSpawn.int1 = 65;
// 		void bUpdate(s16 i){
// 			if(bullets[i].clock % 5 == 0 && bullets[i].clock <= bullets[i].int1){
// 				bullets[i].velocity.y = fix16Add(bullets[i].velocity.y, FIX16(1));
// 			}
// 		}
// 		spawnEnemyBullet(bSpawn, bUpdate);
// 	}
// }

// void bossPatternTwo(){
// 	// middle
// 	if(bossClock % 60 < 30 && bossClock % 3 == 0){
// 		if(bossClock % 60 == 0) bossInt1 = random() % 512;
// 		struct bulletSpawner bSpawn = {
// 			.x = BOSS_B_X,
// 			.y = BOSS_B_Y,
// 			.angle = bossInt1,
// 			.speed = fix16Add(FIX16(4), cosFix16(bossInt1 * 2)),
// 			.type = bossClock % 6 == 0 ? 1 : 3,
// 		};
// 		bossInt1 += 128;
// 		void bUpdate(s16 i){
// 			if(bullets[i].clock == 5){
// 				bullets[i].speed = FIX16(3);
// 				updateEnemyBulletVelocity(i);
// 			} else if(bullets[i].clock == 10){
// 				bullets[i].speed = FIX16(0);
// 				updateEnemyBulletVelocity(i);
// 			} else if(bullets[i].clock == 30){
// 				bullets[i].velocity.x = honeEnemyBullet(bullets[i].pos.x, bullets[i].pos.y, 4, 32, TRUE);
// 				bullets[i].velocity.y = honeEnemyBullet(bullets[i].pos.x, bullets[i].pos.y, 4, 32, FALSE);
// 			}
// 		}
// 		spawnEnemyBullet(bSpawn, bUpdate);
// 	}
// 	// sides
// 	else if(bossClock % 60 >= 30 && bossClock % 10 == 0){
// 		struct bulletSpawner bSpawn = {
// 			.x = fix16Add(BOSS_B_X, bossClock % 120 < 60 ? BOSS_X_OFFSET : BOSS_X_OFFSET_NEG),
// 			.y = BOSS_B_Y,
// 			.type = bossClock % 120 < 60 ? 4 : 2,
// 		};
// 		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 32, TRUE);
// 		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 32, FALSE);
// 		spawnEnemyBullet(bSpawn, eUpdate);
// 		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
// 	}
// }
// void bossPatternThree(){
// 	// spots
// 	if(bossClock % 120 < 60 && bossClock % 2 == 0){
// 		if(bossClock % 20 == 0){
// 			bossInt1 = random() % 192 + 32;
// 			bossInt2 = 32 + random() % 32;
// 		}
// 		struct bulletSpawner bSpawn = {
// 			.x = FIX16(bossInt1),
// 			.y = FIX16(bossInt2),
// 			.type = 1
// 		};
// 		if(bossClock % 120 >= 20 && bossClock % 120 < 40) bSpawn.type = 3;
// 		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 92, TRUE);
// 		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 4, 0, FALSE);
// 		spawnEnemyBullet(bSpawn, eUpdate);
// 		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
// 	}
// 	// middle
// 	if(bossClock % 120 == 96){
// 		struct bulletSpawner bSpawn = {
// 			.x = BOSS_B_X,
// 			.y = BOSS_B_Y,
// 			.speed = FIX16(6),
// 			.angle = random() % 512,
// 			.type = 4
// 		};
// 		void bUpdate(s16 i){
// 			if(bullets[i].speed > FIX16(3) && bullets[i].clock % 10 == 0){
// 				bullets[i].speed = fix16Sub(bullets[i].speed, FIX16(1));
// 				updateEnemyBulletVelocity(i);
// 			}
// 		}
// 		for(s16 b = 0; b < 25; b++){
// 			if(bSpawn.angle % 1024 > 64 && bSpawn.angle % 1024 < 448) spawnEnemyBullet(bSpawn, bUpdate);
// 			bSpawn.angle += 41;
// 		}
// 	}
// }

// // boss three
// void bossPatternFour(){
// 	// curvy
// 	if(bossClock % 30 == 0){
// 		if(bossClock % 60 == 0){
// 			bossInt1 = 768;
// 			bossInt2 = 0;
// 		}
// 		struct bulletSpawner bSpawn = {
// 			.x = BOSS_B_X,
// 			.y = BOSS_B_Y,
// 			.speed = FIX16(0.5),
// 			.type = 1,
// 			.angle = bossInt1 + bossInt2,
// 			.flag1 = bossClock % 120 < 60 ? TRUE : FALSE,
// 		};
// 		bossInt2 += bSpawn.flag1 ? 32 : -32;
// 		if(bSpawn.flag1) bSpawn.type = 3;
// 		void bUpdate(s16 i){
// 			if(bullets[i].clock % 5 == 0){
// 				bullets[i].angle += bullets[i].flag1 ? 48 : -48;
// 				bullets[i].speed = fix16Add(bullets[i].speed, FIX16(0.5));
// 				updateEnemyBulletVelocity(i);
// 			}
// 		}
// 		for(s16 i = 0; i < 6; i++){
// 			spawnEnemyBullet(bSpawn, bUpdate);
// 			bSpawn.angle += bSpawn.flag1 ? 64 : -64;
// 		}
// 	}
// 	//middle
// 	if(bossClock % 120 == 60){
// 		struct bulletSpawner bSpawn = {
// 			.x = BOSS_B_X,
// 			.y = BOSS_B_Y,
// 			.speed = FIX16(5),
// 			.type = 4,
// 			.angle = random() % 512
// 		};
// 		void bUpdate(s16 i){
// 			if(bullets[i].clock % 5 == 0 && bullets[i].speed >= FIX16(3.5)){
// 				bullets[i].speed = fix16Sub(bullets[i].speed, FIX16(0.5));
// 				updateEnemyBulletVelocity(i);
// 			}
// 		}
// 		for(s16 i = 0; i < 16; i++){
// 			if(bSpawn.angle % 1024 > 64 && bSpawn.angle % 1024 < 448) spawnEnemyBullet(bSpawn, bUpdate);
// 			bSpawn.angle += 64;
// 		}
// 	}
// }
// void bossPatternFive(){
// 	// spray
// 	if(bossClock % 15 == 0){
// 		struct bulletSpawner bSpawn = {
// 			.x = BOSS_B_X,
// 			.y = BOSS_B_Y,
// 			.speed = FIX16(6),
// 			.type = 1,
// 			.flag1 = bossClock % 30 == 0 ? TRUE : FALSE
// 		};
// 		if(bSpawn.flag1) bSpawn.type = 3;
// 		bSpawn.angle = bSpawn.flag1 ? 512 : 0;
// 		void bUpdate(s16 i){
// 			if(bullets[i].clock % 5 == 0 && bullets[i].clock > 0){
// 				bullets[i].angle += bullets[i].flag1 ? -32 : 32;
// 				if(bullets[i].clock <= 10) bullets[i].speed = fix16Sub(bullets[i].speed, FIX16(1));
// 				updateEnemyBulletVelocity(i);
// 			}
// 		}
// 		for(s16 i = 0; i < 6; i++){
// 			spawnEnemyBullet(bSpawn, bUpdate);
// 			bSpawn.angle += bSpawn.flag1 ? -64 : 64;
// 		}
// 	}
// 	// homing
// 	if(bossClock % 30 == 25){
// 		struct bulletSpawner bSpawn = {
// 			.x = FIX16(random() % 192 + 32),
// 			.y = FIX16(32 + random() % 32),
// 			.type = 2
// 		};
// 		if(bossClock % 60 == 25) bSpawn.type = 4;
// 		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 3, 0, TRUE);
// 		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 3, 0, FALSE);
// 		spawnEnemyBullet(bSpawn, eUpdate);
// 		spawnExplosion(fix16ToInt(bSpawn.x), fix16ToInt(bSpawn.y), FALSE);
// 	}
// }

// // boss four
// void bossPatternSix(){
// 	if(bossClock % 60 < 30 && bossClock % 15 == 0){
// 		struct bulletSpawner bSpawn = {
// 			.x = BOSS_B_X,
// 			.y = BOSS_B_Y,
// 			.speed = FIX16(4.5),
// 			.type = 4,
// 			.angle = random() % 1024,
// 			.flag1 = bossClock % 30 == 0
// 		};
// 		if(bSpawn.flag1) bSpawn.type = 2;
// 		void bUpdate(s16 i){
// 			if(bullets[i].clock % 5 == 0 && bullets[i].clock < 40){
// 				bullets[i].angle += bullets[i].flag1 ? 64 : -64;
// 				updateEnemyBulletVelocity(i);
// 			}
// 		}
// 		for(s16 i = 0; i < 14; i++){
// 			spawnEnemyBullet(bSpawn, bUpdate);
// 			bSpawn.angle += 73;
// 		}
// 	}
// }
// void bossPatternSeven(){
// 	if(bossClock % 50 == 0){
// 		struct bulletSpawner bSpawn = {
// 			.x = BOSS_B_X,
// 			.y = BOSS_B_Y,
// 			.type = 2
// 		};
// 		bSpawn.velocityX = honeEnemyBullet(bSpawn.x, bSpawn.y, 2, 0, TRUE);
// 		bSpawn.velocityY = honeEnemyBullet(bSpawn.x, bSpawn.y, 2, 0, FALSE);
// 		void bUpdate(s16 i){
// 			if(bullets[i].clock % 30 == 15 && bullets[i].clock < 60){
// 				struct bulletSpawner bSpawn = {
// 					.x = bullets[i].pos.x,
// 					.y = bullets[i].pos.y,
// 					.type = 3,
// 					.angle = random() % 1024,
// 					.speed = FIX16(3),
// 					.flag1 = bullets[i].pos.x < playerPos.x
// 				};
// 				void bbUpdate(s16 h){
// 					if(bullets[h].clock % 5 == 0 && bullets[h].clock < 60){
// 						bullets[h].angle += bullets[h].flag1 ? -32 : 32;
// 						// bullets[h].speed = fix16Add(bullets[h].speed, FIX16(0.25));
// 						updateEnemyBulletVelocity(h);
// 					}
// 				}
// 				for(s16 h = 0; h < 8; h++){
// 					spawnEnemyBullet(bSpawn, bbUpdate);
// 					bSpawn.angle += 128;
// 				}
// 			}
// 		}
// 		spawnEnemyBullet(bSpawn, bUpdate);
// 	}
// }