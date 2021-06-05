#define GAME_WIDTH 256
#define GAME_HEIGHT 224

bool gameOver, stageOver, noMiss, paused, started, zoneOver, zoneStarting,
	zoneFinished;

s16 initLives, gameClock, currentZone;

void loadResources(),
	loadGame(),
	updateGame();

int main();