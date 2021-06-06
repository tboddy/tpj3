// #define ZONE_OVER_CHROME_LIMIT 1
// #define ZONE_OVER_CHROME_LIMIT 240
#define ZONE_OVER_CHROME_LIMIT 60

#define BOSS_TILE_X 6
#define BOSS_TILE_Y 3
#define BOSS_TILE_COUNT 25
#define BOSS_TILE_PX BOSS_TILE_COUNT * 8

s16 frameTileIndex, zoneOverClock, zoneOverStage, lastBossHealth, bossTileIndex;

fix16 bossLimit, lastBossLimit;

bool loadedZoneOver;

char currentZoneStr[2],
	zoneHudStr[2],
	currentZoneApp[1],
	zoneOverTime[8];

void loadChrome(),
	loadChromeZoneOver(),
	loadChromeLives(),
	loadChromeRank(),
	loadChromeScore(),
	updateChromeZoneOver(),
	updateChrome();