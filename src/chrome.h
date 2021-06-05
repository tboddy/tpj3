#define ZONE_OVER_CHROME_LIMIT 1

s16 frameTileIndex, zoneOverClock, zoneOverStage;

bool loadedZoneOver;

char currentZoneStr[2],
	zoneHudStr[2],
	currentZoneApp[1],
	zoneOverTime[8];

void loadChrome(),
	loadChromeFrame(),
	loadChromeZoneOver(),
	loadChromeLives(),
	loadChromeScore(),
	updateChromeZoneOver(),
	updateChrome();