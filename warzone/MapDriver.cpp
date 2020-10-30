#include "MapDriver.h"
#include <cassert>
#include <iostream>

using std::vector;

int MapDriver::main()
{
	Map* validMap = getValidMap();
	validMap->validate();

	Map* unconnectedMap = getMapUnconnected();
	try {
		unconnectedMap->checkMapIsConnectedGraph();
	}
	catch (std::string exception) {
		assert(exception.compare(Map::UNCONNECTED_MAP_ERROR) == 0);
	}
	delete unconnectedMap;

	Map* unconnectedContinentMap = getMapUnconnectedContinent();
	try {
		unconnectedContinentMap->checkContinentsAreConnectedSubgraphs();
	}
	catch (std::string exception) {
		assert(exception.compare(Map::UNCONNECTED_CONTINENT_ERROR) == 0);
	}
	delete unconnectedContinentMap;

	Map* mapWithTerritoryInNoContinents = getMapTerritoryInNoContinents();
	try {
		mapWithTerritoryInNoContinents->checkTerritoriesBelongToExactlyOneContinent();
	}
	catch (std::string exception) {
		assert(exception.compare(Map::TERRITORY_IN_ZERO_CONTINENTS_ERROR) == 0);
	}
	delete mapWithTerritoryInNoContinents;

	Map* mapWithTerritoryInTwoContinents = getMapTerritoryInTwoContinents();
	try {
		mapWithTerritoryInTwoContinents->checkTerritoriesBelongToExactlyOneContinent();
	}
	catch (std::string exception) {
		assert(exception.compare(Map::TERRITORY_IN_TWO_CONTINENTS_ERROR) == 0);
	}
	delete mapWithTerritoryInTwoContinents;

	std::cout << std::endl << "Map validation successful" << std::endl;
	std::cout << "Printing Map" << std::endl;
	std::cout << *validMap << std::endl;
	delete validMap;

	return 0;
}

Map* MapDriver::getValidMap() {
	Map* map = new Map();

	Continent* amadicia = new Continent("Amadicia", "blue", 5);
	Continent* bellovia = new Continent("Bellovia", "red", 6);
	Continent* caelandia = new Continent("Caelandia", "green", 4);

	map->addContinent(amadicia);
	map->addContinent(bellovia);
	map->addContinent(caelandia);

	Territory* avandria = new Territory("Avandria", amadicia, 375, 450);
	Territory* agruntik = new Territory("Agruntik", amadicia, 500, 500);
	Territory* apollo = new Territory("Apollo", amadicia, 450, 350);

	Territory* burgundy = new Territory("Burgundy", bellovia, 250, 600);
	Territory* byzantium = new Territory("Byzantium", bellovia, 300, 475);

	Territory* crestwall = new Territory("Crestwall", caelandia, 600, 150);
	Territory* cruthnik = new Territory("Cruthnik", caelandia, 500, 250);

	map->addTerritory(avandria);
	map->addTerritory(agruntik);
	map->addTerritory(apollo);
	map->addTerritory(burgundy);
	map->addTerritory(byzantium);
	map->addTerritory(crestwall);
	map->addTerritory(cruthnik);

	vector<Territory*> avandriaBorders{ agruntik, apollo };
	vector<Territory*> agruntikBorders{ avandria, apollo, burgundy, byzantium };
	vector<Territory*> apolloBorders{ avandria, agruntik, crestwall };
	vector<Territory*> burgundyBorders{ agruntik, byzantium };
	vector<Territory*> byzantiumBorders{ burgundy, crestwall, cruthnik };
	vector<Territory*> crestwallBorders{ apollo, byzantium, cruthnik };
	vector<Territory*> cruthnikBorders{ byzantium, crestwall };

	map->addBorder(0, &avandriaBorders);
	map->addBorder(1, &agruntikBorders);
	map->addBorder(2, &apolloBorders);
	map->addBorder(3, &burgundyBorders);
	map->addBorder(4, &byzantiumBorders);
	map->addBorder(5, &crestwallBorders);
	map->addBorder(6, &cruthnikBorders);

	return map;
}

Map* MapDriver::getMapUnconnected() {
	Map* map = getValidMap();

	Territory* unconnectedTerritory = new Territory("Unconnected", map->getContinent(0), 1000, 1000);
	map->addTerritory(unconnectedTerritory);

	return map;
}

Map* MapDriver::getMapUnconnectedContinent() {
	Map* map = getValidMap();

	Territory* unconnectedTerritory = new Territory("Unconnected", map->getContinent(0), 1000, 1000);
	map->addTerritory(unconnectedTerritory);

	Territory* neighbor = map->getTerritory(6);
	vector<Territory*> borders = { neighbor };
	vector<Territory*> neighborBorders = { unconnectedTerritory };
	unconnectedTerritory->addBorders(&borders);
	neighbor->addBorders(&neighborBorders);

	return map;
}

Map* MapDriver::getMapTerritoryInNoContinents() {
	Map* map = getValidMap();
	
	Continent* fakeContinent = new Continent("Fake", "colour", 5);
	Territory* TerritoryNotInContinent = new Territory("NoContinentTerritory", fakeContinent, 1000, 1000);
	map->addTerritory(TerritoryNotInContinent);
	delete(fakeContinent);

	Territory* neighbor = map->getTerritory(6);
	vector<Territory*> borders = { neighbor };
	vector<Territory*> neighborBorders{ TerritoryNotInContinent };
	TerritoryNotInContinent->addBorders(&borders);
	neighbor->addBorders(&neighborBorders);

	return map;
}

Map* MapDriver::getMapTerritoryInTwoContinents() {
	Map* map = getValidMap();

	Continent* continentOne = map->getContinent(0);
	Continent* continentTwo = map->getContinent(1);
	Territory* territoryInTwoContinents = new Territory("TwoContinentTerritory", continentOne, 1000, 1000);
	map->addTerritory(territoryInTwoContinents);
	continentTwo->addTerritory(territoryInTwoContinents);

	Territory* neighborFromContinentOne = map->getTerritory(1);
	Territory* neighborFromContinentTwo = map->getTerritory(3);
	vector<Territory*> borders = { neighborFromContinentOne, neighborFromContinentTwo };
	vector<Territory*> neighborBorders{ territoryInTwoContinents };
	territoryInTwoContinents->addBorders(&borders);
	neighborFromContinentOne->addBorders(&neighborBorders);
	neighborFromContinentTwo->addBorders(&neighborBorders);

	return map;
}
