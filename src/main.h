#define GAME_WIDTH 256
#define GAME_HEIGHT 224

bool gameOver, noMiss, paused, pausing, zoneOver, zoneStarting, gameStarting, noMiss, doZoneStart;

s16 gameClock, currentZone, gameOverClock;
s32 currentScore, highScore;

void loadResources(),
	loadGame(),
	resetGame(),
	updateGame();

int main();