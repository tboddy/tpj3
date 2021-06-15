#define GAME_WIDTH 256
#define GAME_HEIGHT 224

bool gameOver, noMiss, paused, pausing, zoneOver, zoneStarting, gameStarting, zoneFinished;

s16 initLives, gameClock, currentZone, gameOverClock;

void loadResources(),
	loadGame(),
	updateGame();

int main();