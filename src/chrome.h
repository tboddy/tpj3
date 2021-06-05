s16 frameTileIndex, zoneOverClock, zoneOverStage;

bool loadedZoneOver;

char currentZoneStr[2],
	currentZoneApp[1],
	zoneOverTime[8];

void loadChrome(),
	loadChromeFrame(),
	loadChromeZoneOver(),
	loadChromeLives(),
	loadChromeScore(),
	updateChromeZoneOver(),
	updateChrome();