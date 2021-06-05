#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"
#include "pod.h"
#include "explosion.h"
#include "boss.h"


void spawnPod(struct podSpawner spawner){
	s16 i = -1;
	for(s16 h = 0; h < POD_COUNT; h++) if(!pods[h].active && i == -1) i = h;
	if(i > -1){
		pods[i].active = TRUE;
		pods[i].pos.x = spawner.x;
		pods[i].pos.y = spawner.y;
		pods[i].clock = 0;
		pods[i].random = spawner.random;
		pods[i].image = SPR_addSprite(&imgSpider, fix16ToInt(POD_DUMP_X), fix16ToInt(POD_DUMP_Y), TILE_ATTR(PAL1, 0, FALSE, FALSE));
	}
	spawnExplosion(fix16ToInt(pods[i].pos.x), fix16ToInt(pods[i].pos.y), FALSE);
}

void shootPod(s16 i){
	void patternOne(){
		struct bulletSpawner bSpawn = {
			.x = fix16Add(pods[i].pos.x, FIX16(4)),
			.y = fix16Add(pods[i].pos.y, FIX16(4)),
			.type = 3,
			.speed = FIX16(1),
			.angle = random() % 1024,
			.flag1 = FALSE
		};
		void bUpdate(s16 j){
			if(bullets[j].clock % 10 == 0 && bullets[j].speed < FIX16(bullets[j].flag1 ? 2 : 4))
				bullets[j].speed = fix16Add(bullets[j].speed, FIX16(bullets[j].flag1 ? 0.5 : 1));
				updateEnemyBulletVelocity(j);
		}
		for(s16 b = 0; b < 4; b++){
			spawnEnemyBullet(bSpawn, bUpdate);
			bSpawn.angle += 256;
		}
		bSpawn.angle += 128;
		bSpawn.type = 4;
		bSpawn.flag1 = TRUE;
		for(s16 b = 0; b < 4; b++){
			spawnEnemyBullet(bSpawn, bUpdate);
			bSpawn.angle += 256;
		}
	}
	patternOne();
}

void destroyPod(s16 i){
	killPod(i);
	if(pods[i].random) spawnRandomPod();
	spawnExplosion(fix16ToInt(pods[i].pos.x), fix16ToInt(pods[i].pos.y), FALSE);
}

void spawnRandomPod(){
	struct podSpawner pSpawn = {
		.x = FIX16((32 + random() % 192) / 16 * 16),
		.y = FIX16((48 + random() % 96) / 16 * 16),
		.random = TRUE
	};
	foundRandomPodMatch = FALSE;
	for(s16 i = 0; i < POD_COUNT; i++) if(currentPodPos[i].x == pSpawn.x && currentPodPos[i].y == pSpawn.y) foundRandomPodMatch = TRUE;
	foundRandomPodMatch ? spawnRandomPod() : spawnPod(pSpawn);
}

void killPod(s16 i){
	pods[i].active = FALSE;
	pods[i].pos.x = POD_DUMP_X;
	pods[i].pos.y = POD_DUMP_Y;
	SPR_releaseSprite(pods[i].image);
}


// loop

void loadPod(){
	currentPodCount = 2;
	for(s16 i = 0; i < POD_COUNT; i++){
		pods[i].pos.x = POD_DUMP_X;
		pods[i].pos.y = POD_DUMP_Y;
		pods[i].random = FALSE;
		pods[i].clock = 0;
	}
}

void resetPod(){
	for(s16 i = 0; i < POD_COUNT; i++){
		pods[i].active = FALSE;
		pods[i].pos.x = POD_DUMP_X;
		pods[i].pos.y = POD_DUMP_Y;
		SPR_releaseSprite(pods[i].image);
	}
}

void updatePod(){
	for(s16 i = 0; i < POD_COUNT; i++) if(pods[i].active) {
		if(pods[i].clock >= POD_TIME_LIMIT){
			shootPod(i);
			destroyPod(i);
		} else {
			if(pods[i].clock % 60 == 0 && pods[i].clock > 0){
				SPR_setAnimAndFrame(pods[i].image, pods[i].clock / 60, pods[i].clock % 40 == 0 ? 0 : 1);
			}
			SPR_setPosition(pods[i].image, fix16ToInt(pods[i].pos.x) - 8, fix16ToInt(pods[i].pos.y) - 8);
		}
		if(zoneOver) killPod(i);
		pods[i].clock++;
	}
	for(s16 i = 0; i < currentPodCount; i++) if(podClock == i * 120 + 120 && !bossActive) spawnRandomPod();
	podClock++;
	if(podClock >= 600) podClock = 300;
}