#define GAME_WIDTH 256
#define GAME_HEIGHT 224

#define SFX_MENU_SELECT 64
#define SFX_MENU_CHOOSE 65
#define SFX_START_GAME 66
#define SFX_PLAYER_SHOT 67
#define SFX_ZONE_OVER 68

#define SFX_BULLET_1 69

#define SFX_EXPLOSION_1 73
#define SFX_EXPLOSION_2 74
#define SFX_EXPLOSION_3 75

#define SFX_GAME_OVER 76
#define SFX_BEAT_GAME 77

bool gameOver, noMiss, paused, pausing, zoneOver, zoneStarting, gameStarting, noMiss, doZoneStart;

s16 gameClock, currentZone, gameOverClock;
s32 currentScore, highScore;

void loadResources(),
	loadGame(),
	resetGame(),
	updateGame();

int main();