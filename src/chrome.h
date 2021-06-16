// #define ZONE_OVER_CHROME_LIMIT 1
#define ZONE_OVER_CHROME_LIMIT 240
// #define ZONE_OVER_CHROME_LIMIT 60

#define BOSS_TILE_X 6
#define BOSS_TILE_Y 3
#define BOSS_TILE_COUNT 25
#define BOSS_TILE_PX BOSS_TILE_COUNT * 8

#define PLAYER_BOMBS_Y 26

s16 frameTileIndex, zoneOverClock, zoneOverStage, lastBossHealth, bossTileIndex;
s8 chromePlayerLives, chromePlayerBombs;
s32 chromeCurrentScore;

fix16 bossLimit, lastBossLimit;

bool loadedZoneOver, loadedChromeGameOver;

char currentZoneStr[2],
	zoneHudStr[2],
	currentZoneApp[1],
	zoneOverTime[8],
	chromeScoreStr[10];

void loadChrome(),
	loadChromeZoneOver(),
	loadChromeLives(),
	loadChromeGameOver(bool),
	updateChromeZoneOver(),
	updateChromeScore(),
	loadChromeBeatGame(),
	updateChromePlayerLives(),
	updateChromePlayerBombs(),
	updateChromeBoss(),
	updateChrome();