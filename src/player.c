#include <genesis.h>
#include <resources.h>
#include "player.h"
#include "main.h"
#include "controls.h"


// movement

void updatePlayerBounds(){
	if(playerPos.x < PLAYER_LIMIT_LEFT) playerPos.x = PLAYER_LIMIT_LEFT;
	else if(playerPos.x > PLAYER_LIMIT_RIGHT) playerPos.x = PLAYER_LIMIT_RIGHT;
	if(playerPos.y < PLAYER_LIMIT_TOP) playerPos.y = PLAYER_LIMIT_TOP;
	else if(playerPos.y > PLAYER_LIMIT_BOTTOM) playerPos.y = PLAYER_LIMIT_BOTTOM;
}

void updatePlayerMove(){
	playerVelocity.x = FIX16(0);
	playerVelocity.y = FIX16(0);
	if(controls.left){
		if(controls.down){
			playerVelocity.x = MOVEMENT_NORMALIZE_NEG;
			playerVelocity.y = MOVEMENT_NORMALIZE;
		}
		else if(controls.up){
			playerVelocity.x = MOVEMENT_NORMALIZE_NEG;
			playerVelocity.y = MOVEMENT_NORMALIZE_NEG;
		}
		else playerVelocity.x = MOVEMENT_NEG;
	} else if(controls.right){
		if(controls.down){
			playerVelocity.x = MOVEMENT_NORMALIZE;
			playerVelocity.y = MOVEMENT_NORMALIZE;
		}
		else if(controls.up){
			playerVelocity.x = MOVEMENT_NORMALIZE;
			playerVelocity.y = MOVEMENT_NORMALIZE_NEG;
		}
		else playerVelocity.x = MOVEMENT_POS;
	} else if(controls.up || controls.down) playerVelocity.y = controls.up ? MOVEMENT_NEG : MOVEMENT_POS;
	playerPos.x += fix16Mul(playerVelocity.x, controls.b ? PLAYER_SPEED_FOCUS : PLAYER_SPEED);
	playerPos.y += fix16Mul(playerVelocity.y, controls.b ? PLAYER_SPEED_FOCUS : PLAYER_SPEED);
	updatePlayerBounds();
	SPR_setPosition(playerSprite, fix16ToInt(playerPos.x) - 11, fix16ToInt(playerPos.y) - 16);
}


// shooting

void spawnPlayerBullet(bool downward){
	static s16 i = 0;
	for(s16 j = 0; j < PLAYER_BULLET_LIMIT; j++) if(!playerBullets[j].active) i = j;
	playerBullets[i].active = TRUE;
	playerBullets[i].pos.x = playerPos.x;
	playerBullets[i].pos.y = fix16Sub(playerPos.y, FIX16(8));
	playerBullets[i].downward = downward ? TRUE : FALSE;
	SPR_setVFlip(playerBullets[i].image, downward ? 1 : 0);
}

void removePlayerBullet(s16 i){
	playerBullets[i].pos.x = FIX16(PLAYER_BULLET_DUMP_X);
	playerBullets[i].pos.y = FIX16(PLAYER_BULLET_DUMP_Y);
	SPR_setPosition(playerBullets[i].image, PLAYER_BULLET_DUMP_X, PLAYER_BULLET_DUMP_Y);
	playerBullets[i].active = FALSE;
}

void updatePlayerBullets(){
	for(s16 i = 0; i < PLAYER_BULLET_LIMIT; i++) if(playerBullets[i].active){
		playerBullets[i].pos.y = fix16Sub(playerBullets[i].pos.y, (playerBullets[i].downward ? PLAYER_BULLET_SPEED_DOWN : PLAYER_BULLET_SPEED));
		SPR_setPosition(playerBullets[i].image, fix16ToInt(playerBullets[i].pos.x) - 8, fix16ToInt(playerBullets[i].pos.y) - 8);
		if(playerBullets[i].pos.y <= PLAYER_BULLET_UP_LIMIT || playerBullets[i].pos.y >= PLAYER_BULLET_DOWN_LIMIT || zoneOver) removePlayerBullet(i);
	}
}

void updatePlayerShot(){
	if(playerShotClock >= PLAYER_SHOT_INTERVAL && (controls.a || controls.c)) playerShotClock = 0;
	if(playerShotClock == 0 && !zoneOver) spawnPlayerBullet(controls.c && !controls.a);
	playerShotClock++;
	if(playerShotClock >= 600) playerShotClock = PLAYER_SHOT_INTERVAL;
}


// get hit

void updatePlayerHit(){
	if(hitPlayer){
		hitPlayer = FALSE;
		playerRecovering = TRUE;
		playerPos.x = PLAYER_INIT_X;
		playerPos.y = PLAYER_INIT_Y;
		playerLives -= 1;
		noMiss = FALSE;
		if(playerLives < 0) gameOver = TRUE;
	}
	// if(!gameOver && player.recovering){
		// if(player.recoverClock % RECOVER_INTERVAL == 0){
		// 	SPR_setVisibility(player.image, HIDDEN);
		// 	SPR_setVisibility(player.hitboxImage, HIDDEN);
		// } else if(player.recoverClock % RECOVER_INTERVAL == RECOVER_INTERVAL / 2){
		// 	SPR_setVisibility(player.image, VISIBLE);
		// 	SPR_setVisibility(player.hitboxImage, VISIBLE);
		// }
		// player.recoverClock++;
		// if(player.recoverClock >= RECOVER_INTERVAL * 6){
		// 	SPR_setVisibility(player.image, VISIBLE);
		// 	SPR_setVisibility(player.hitboxImage, VISIBLE);
		// 	player.recoverClock = 0;
		// 	player.recovering = FALSE;
		// }
	// }
}


// loop


void loadPlayer(){
	playerShotClock = PLAYER_SHOT_INTERVAL;
	playerPos.x = PLAYER_INIT_X;
	playerPos.y = PLAYER_INIT_Y;
	playerSprite = SPR_addSprite(&imgPlayer, playerPos.x, playerPos.y, TILE_ATTR(PAL1, 1, FALSE, FALSE));
	SPR_setDepth(playerSprite, 4);
	for(s16 i = 0; i < PLAYER_BULLET_LIMIT; i++){
		playerBullets[i].image = SPR_addSprite(&imgBullet, PLAYER_BULLET_DUMP_X, PLAYER_BULLET_DUMP_Y, TILE_ATTR(PAL1, 1, FALSE, FALSE));
		SPR_setDepth(playerBullets[i].image, 4);
	}
}

void resetPlayer(){
	playerPos.x = PLAYER_INIT_X;
	playerPos.y = PLAYER_INIT_Y;
	SPR_releaseSprite(playerSprite);
	for(s16 i = 0; i < PLAYER_BULLET_LIMIT; i++) if(playerBullets[i].active){
		playerBullets[i].active = FALSE;
		SPR_releaseSprite(playerBullets[i].image);
	}
}

void updatePlayer(){
	if(zoneStarting) loadPlayer();
	else {
		updatePlayerBullets();
		if(!gameOver && !paused){
			if(zoneOver) SPR_setVisibility(playerSprite, HIDDEN);
			else {
				updatePlayerMove();
				updatePlayerHit();
			}
			updatePlayerShot();
		} else if(gameOver) resetPlayer();
	}
}