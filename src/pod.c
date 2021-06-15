#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "enemies.h"
#include "pod.h"
#include "explosion.h"
#include "boss.h"


// spawn

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
}


// shoot

void podPatternOne(s16 i){
	struct bulletSpawner bSpawn = {
		.x = pods[i].pos.x,
		.y = pods[i].pos.y,
		.type = 4,
		.angle = random() % 1024,
		.speed = FIX16(podBulletSpeed)
	};
	for(s8 b = 0; b < 3; b++){
		spawnEnemyBullet(bSpawn, eUpdate);
		bSpawn.angle += 341;
	}
}

void podPatternTwo(s8 i, s8 mod, s16 aMod){
	struct bulletSpawner bSpawn = {
		.x = pods[i].pos.x,
		.y = pods[i].pos.y,
		.type = 4,
		.angle = random() % 1024,
		.speed = FIX16(podBulletSpeed)
	};
	for(s8 b = 0; b < 3 + mod; b++){
		spawnEnemyBullet(bSpawn, eUpdate);
		bSpawn.angle += aMod;
	}
	bSpawn.speed = FIX16(podBulletSpeed + 1);
	bSpawn.type = 3;
	bSpawn.angle += aMod / 2;
	for(s8 b = 0; b < 3 + mod; b++){
		spawnEnemyBullet(bSpawn, eUpdate);
		bSpawn.angle += aMod;
	}
}

void shootPod(s16 i){
	if(currentZone == 1) podPatternOne(i);
	else if(currentZone < 5) podPatternTwo(i, 0, 342);
	else if(currentZone < 10) podPatternTwo(i, 1, 256);
	else podPatternTwo(i, 2, 204);
}


// die

void killPod(s16 i){
	pods[i].active = FALSE;
	pods[i].pos.x = POD_DUMP_X;
	pods[i].pos.y = POD_DUMP_Y;
	SPR_releaseSprite(pods[i].image);
}


// loop

void loadPod(){
	if(currentZone % 5 == 1 && currentZone > 1) podBulletSpeed++;
	currentPodCount = 0;
	if(currentZone >= 3) currentPodCount = 1;
	if(currentZone >= 6) currentPodCount = 2;
	if(currentZone >= 11) currentPodCount = 3;
	if(currentZone >= 16) currentPodCount = 4;
	if(currentPodCount > 0){
		for(s16 i = 0; i < POD_COUNT; i++){
			pods[i].pos.x = POD_DUMP_X;
			pods[i].pos.y = POD_DUMP_Y;
			pods[i].random = FALSE;
			pods[i].clock = 0;
		}
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
			killPod(i);
			spawnExplosion(fix16ToInt(pods[i].pos.x), fix16ToInt(pods[i].pos.y), FALSE);
		} else {
			if(pods[i].clock % 60 == 0 && pods[i].clock > 0){
				SPR_setAnimAndFrame(pods[i].image, pods[i].clock / 60, pods[i].clock % 40 == 0 ? 0 : 1);
			}
			SPR_setPosition(pods[i].image, fix16ToInt(pods[i].pos.x) - 8, fix16ToInt(pods[i].pos.y) - 8);
		}
		if(zoneOver) killPod(i);
		pods[i].clock++;
	}
}