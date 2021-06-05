#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"
#include "explosion.h"
#include "player.h"
#include "boss.h"


// shooting

void shootBoss(){
	void patternOne(bool second){

		if(bossClock % 60 <= 30 && bossClock % 3 == 0){
			if(bossClock % 60 == 0) bossInt1 = random() % 512;
			struct bulletSpawner bSpawn = {
				.x = BOSS_B_X,
				.y = BOSS_B_Y,
				.angle = bossInt1,
				.speed = FIX16(4),
				.type = bossClock % 6 == 0 ? 1 : 3,
			};
			bossInt1 += 128;
			// if(bossClock % 60 >= 7 && bossClock % 60 < 15) bSpawn.type = 4;
			// else if(bossClock % 60 >= 15 && bossClock % 60 < 24) bSpawn.type = 6;
			// else if(bossClock % 60 >= 14) bSpawn.type = 8;
			void bUpdate(s16 i){
				if(bullets[i].clock == 5){
					bullets[i].speed = FIX16(3);
					updateEnemyBulletVelocity(i);
				} else if(bullets[i].clock == 10){
					bullets[i].speed = FIX16(0);
					updateEnemyBulletVelocity(i);
				} else if(bullets[i].clock == 30){
					bullets[i].velocity.x = honeEnemyBullet(bullets[i].pos.x, bullets[i].pos.y, 4, 48, TRUE);
					bullets[i].velocity.y = honeEnemyBullet(bullets[i].pos.x, bullets[i].pos.y, 4, 48, FALSE);
				}
			}
			spawnEnemyBullet(bSpawn, bUpdate);
		}

	}
	patternOne(FALSE);
}


// collision

void hitBoss(){}

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


// loop

void loadBoss(){
	bossType++;
	bossLoaded = FALSE;
	bossActive = TRUE;
}

void updateBoss(){
	if(bossActive) {
		if(bossLoaded){
			collideBoss();
			shootBoss();
		} else if(bossClock == BOSS_LOAD_TIME){
			VDP_drawImageEx(BG_A, (bossType == 1 ? &cake : &cake), TILE_ATTR_FULL(PAL1, 0, 0, 0, 92), 12, 4, 0, DMA_QUEUE);
			bossLoaded = TRUE;
			bossClock = -1;
		}
		bossClock++;
		if(bossClock > 600) bossClock = 60;
	}
}