#pragma once
#include "Map.h"
#include <string>

namespace MapDriver {
	int main();
	Map* getValidMap();
	Map* getMapUnconnected();
	Map* getMapUnconnectedContinent();
	Map* getMapTerritoryInNoContinents();
	Map* getMapTerritoryInTwoContinents();
}