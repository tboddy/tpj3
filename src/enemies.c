#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"
#include "player.h"
#include "yin.h"
#include "centipede.h"
#include "pod.h"
#include "boss.h"


// bullets

void spawnEnemyBullet(struct bulletSpawner spawner, void(*updater)){
	s16 i = -1;
	for(s16 h = 0; h < ENEMY_BULLET_LIMIT; h++) if(!bullets[h].active && i == -1) i = h;
	if(i > -1 && !gameOver){
		bullets[i].active = TRUE;
		bullets[i].grazed = FALSE;
		bullets[i].pos.x = spawner.x;
		bullets[i].pos.y = spawner.y;
		bullets[i].speed = spawner.speed ? spawner.speed : FIX16(2);
		bullets[i].angle = spawner.angle ? spawner.angle : 0;
		bullets[i].flag1 = spawner.flag1 ? TRUE : FALSE;
		bullets[i].flag2 = spawner.flag2 ? TRUE : FALSE;
		bullets[i].flag3 = spawner.flag3 ? TRUE : FALSE;
		bullets[i].flag4 = spawner.flag4 ? TRUE : FALSE;
		bullets[i].int1 = spawner.int1 ? spawner.int1 : 0;
		bullets[i].int2 = spawner.int2 ? spawner.int2 : 0;
		bullets[i].int3 = spawner.int3 ? spawner.int3 : 0;
		bullets[i].int4 = spawner.int4 ? spawner.int4 : 0;
		bullets[i].velocity.x = spawner.velocityX ? spawner.velocityX : fix16Mul(cosFix16(spawner.angle), spawner.speed);
		bullets[i].velocity.y = spawner.velocityY ? spawner.velocityY : fix16Mul(sinFix16(spawner.angle), spawner.speed);
		bullets[i].updater = updater;
		bullets[i].clock = 0;
		switch(spawner.type){
			case 1: bullets[i].image = SPR_addSprite(&imgSmallRedBullet, bullets[i].pos.x, bullets[i].pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE)); break;
			case 2: bullets[i].image = SPR_addSprite(&imgBigRedBullet, bullets[i].pos.x, bullets[i].pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE)); break;
			case 3: bullets[i].image = SPR_addSprite(&imgSmallBlueBullet, bullets[i].pos.x, bullets[i].pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE)); break;
			case 4: bullets[i].image = SPR_addSprite(&imgBigBlueBullet, bullets[i].pos.x, bullets[i].pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE)); break;
			case 5: bullets[i].image = SPR_addSprite(&imgSmallPinkBullet, bullets[i].pos.x, bullets[i].pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE)); break;
			case 6: bullets[i].image = SPR_addSprite(&imgBigPinkBullet, bullets[i].pos.x, bullets[i].pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE)); break;
		}
		if(spawner.type % 2 == 0){
			bullets[i].xOffset = 8;
			bullets[i].yOffset = 8;
			SPR_setDepth(bullets[i].image, 2);
		} else if(spawner.type % 2 == 1){
			bullets[i].xOffset = 4;
			bullets[i].yOffset = 4;
			SPR_setDepth(bullets[i].image, 1);
		}
		SPR_setPosition(bullets[i].image, fix16ToInt(bullets[i].pos.x) - bullets[i].xOffset, fix16ToInt(bullets[i].pos.y) - bullets[i].yOffset);
	}
}

void checkEnemyBulletCollision(s16 i){
	enemyBulletCollisionDistance = getApproximatedDistance(
		fix16ToFix32(playerPos.x) - fix16ToFix32(bullets[i].pos.x),
		fix16ToFix32(playerPos.y) - fix16ToFix32(bullets[i].pos.y));
	if(enemyBulletCollisionDistance < intToFix32(bullets[i].xOffset) && !playerRecovering){
		spawnExplosion(fix16ToInt(bullets[i].pos.x), fix16ToInt(bullets[i].pos.y), TRUE);
		destroyEnemyBullet(i);
		hitPlayer = TRUE;
		killBullets = TRUE;
		// SND_startPlayPCM_XGM(SFX_EXPLOSION2, 15, SOUND_PCM_CH2);
	} else if(!bullets[i].grazed){
		bullets[i].grazed = TRUE;
		currentScore += 50;
		// SND_startPlayPCM_XGM(SFX_GRAZE, 15, SOUND_PCM_CH2);
	}
}

void updateEnemyBullet(s16 i){
	bullets[i].pos.x = fix16Add(bullets[i].pos.x, bullets[i].velocity.x);
	bullets[i].pos.y = fix16Add(bullets[i].pos.y, bullets[i].velocity.y);
	bullets[i].updater(i);
	enemyBulletCount++;
	bullets[i].clock++;
	if(bullets[i].pos.x < FIX16(0 - bullets[i].xOffset) || bullets[i].pos.x > FIX16(256 + bullets[i].xOffset) ||
		bullets[i].pos.y < FIX16(0 - bullets[i].yOffset) || bullets[i].pos.y > FIX16(224 + bullets[i].yOffset) ||
		killBullets || bullets[i].clock >= 600 || zoneOver){
		destroyEnemyBullet(i);
	}
}

void destroyEnemyBullet(s16 i){
	SPR_releaseSprite(bullets[i].image);
	bullets[i].active = FALSE;
	bullets[i].clock = 0;
	bullets[i].pos.x = FIX16(GAME_WIDTH);
	bullets[i].pos.y = FIX16(32);
}

void drawEnemyBullet(s16 i){
	SPR_setPosition(bullets[i].image,
		fix16ToInt(bullets[i].pos.x) - bullets[i].xOffset, fix16ToInt(bullets[i].pos.y) - bullets[i].yOffset);
	if(bullets[i].pos.y > fix16Sub(playerPos.y, ENEMY_BULLET_COLLISION_CHECK) &&
		bullets[i].pos.y < fix16Add(playerPos.y, ENEMY_BULLET_COLLISION_CHECK) &&
		bullets[i].pos.x > fix16Sub(playerPos.x, ENEMY_BULLET_COLLISION_CHECK) &&
		bullets[i].pos.x < fix16Add(playerPos.x, ENEMY_BULLET_COLLISION_CHECK)){
		checkEnemyBulletCollision(i);
	}
}


// utils

void eUpdate(s16 i){if(i){}}

void updateEnemyBulletVelocity(s16 i){
	bullets[i].velocity.x = fix16Mul(cosFix16(bullets[i].angle), bullets[i].speed);
	bullets[i].velocity.y = fix16Mul(sinFix16(bullets[i].angle), bullets[i].speed);
}

fix16 honeEnemyBullet(fix16 x, fix16 y, s16 speed, s16 lerp, bool isX){
	honeX = playerPos.x;
	honeY = playerPos.y;
	if(lerp > 0){
		honeX = fix16Add(fix16Sub(honeX, FIX16(lerp)), FIX16(random() % (lerp * 2)));
		honeY = fix16Add(fix16Sub(honeY, FIX16(lerp)), FIX16(random() % (lerp * 2)));
	}
	honeSpeed = fix32ToFix16(getApproximatedDistance(fix16ToFix32(x) - fix16ToFix32(honeX), fix16ToFix32(y) - fix16ToFix32(honeY)));
	return isX ? fix16Mul(fix16Div(fix16Sub(honeX, x), honeSpeed), FIX16(speed)) : fix16Mul(fix16Div(fix16Sub(honeY, y), honeSpeed), FIX16(speed));
}


// kill bullets dramatically

void updateKillBullets(){
	if(enemyBulletCount >= ENEMY_BULLET_LIMIT) killBullets = TRUE;
	if(killBullets){
		if(killBulletsClock % 4 == 0 && killBulletsClock < 20){
			spawnExplosion(32 + random() % 192, 32 + random() % 128, FALSE);
		}
		killBulletsClock++;
		if(killBulletsClock >= 30){
			killBullets = FALSE;
			killBulletsClock = 0;
		}
	}
}


// loop

void loadEnemies(){
	loadYins();
	loadCentipede();
	loadPod();
}

void resetEnemies(){
	resetYins();
	resetCentipede();
	resetPod();
	for(s16 i = 0; i < ENEMY_BULLET_LIMIT; i++) destroyEnemyBullet(i);
}

void updateEnemies(){
	if(zoneStarting && !bossActive) loadEnemies();
	else {
		if(bossActive) updateBoss();
		else {
			updateYins();
			updateCentipede();
			updatePod();
		}
		if(gameClock % 2 == 0){
			enemyBulletCount = 0;
			// for(s16 i = 0; i < ENEMY_LIMIT; i++) if(enemies[i].active) updateEnemy(i);
			for(s16 i = 0; i < ENEMY_BULLET_LIMIT; i++) if(bullets[i].active) updateEnemyBullet(i);
			updateKillBullets();
		} else for(s16 i = 0; i < ENEMY_BULLET_LIMIT; i++) if(bullets[i].active) drawEnemyBullet(i);
	}
}