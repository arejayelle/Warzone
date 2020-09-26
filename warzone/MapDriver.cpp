#include "MapDriver.h"
#include <cassert>
#include <iostream>

using std::vector;

int main() {
	MapDriver::main();
}

int MapDriver::main()
{
	Map* validMap = getValidMap();
	validateMap(validMap);

	Map* unconnectedMap = getMapUnconnected();
	try {
		checkMapIsConnectedGraph(unconnectedMap);
	}
	catch (std::string exception) {
		assert(exception.compare(UNCONNECTED_MAP_ERROR) == 0);
	}

	Map* unconnectedContinentMap = getMapUnconnectedContinent();
	try {
		checkContinentsAreConnectedSubgraphs(unconnectedContinentMap);
	}
	catch (std::string exception) {
		assert(exception.compare(UNCONNECTED_CONTINENT_ERROR) == 0);
	}

	Map* mapWithTerritoryInNoContinents = getMapTerritoryInNoContinents();
	try {
		checkTerritoriesBelongToExactlyOneContinent(mapWithTerritoryInNoContinents);
	}
	catch (std::string exception) {
		assert(exception.compare(TERRITORY_IN_ZERO_CONTINENTS_ERROR) == 0);
	}

	Map* mapWithTerritoryInTwoContinents = getMapTerritoryInTwoContinents();
	try {
		checkTerritoriesBelongToExactlyOneContinent(mapWithTerritoryInTwoContinents);
	}
	catch (std::string exception) {
		assert(exception.compare(TERRITORY_IN_TWO_CONTINENTS_ERROR) == 0);
	}

	std::cout << "Validation successful" << std::endl;

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

void MapDriver::validateMap(Map* map) {
	checkMapIsConnectedGraph(map);
	checkContinentsAreConnectedSubgraphs(map);
	checkTerritoriesBelongToExactlyOneContinent(map);
}

/*
Checks that the graph is connected.
Start at node 0. Perform a depth-first search of the graph, visiting every node that is connected to the starting node. 
Mark each node as visited by adding it to a list. At the end of the search, if every node in the graph is in the list 
of visited nodes, the graph is connected.
*/
void MapDriver::checkMapIsConnectedGraph(Map* map)
{
	vector<Territory*> visitedCountries = vector<Territory*>();
	visitTerritory(map->getTerritory(0), &visitedCountries);
	
	const vector<Territory*>* allCountries = map->getTerritories();
	for (vector<Territory*>::const_iterator it = allCountries->begin(); it != allCountries->end(); ++it) {
		if (std::find(visitedCountries.begin(), visitedCountries.end(), *it) == visitedCountries.end()) {
			// Could not find the territory in the list of visited territories, so the graph is not connected
			throw UNCONNECTED_MAP_ERROR;
		}
	}
}

/*
Performs a depth-first search recursively from the given territory. If it is not visited, add it to the list
of visited territories. Then, call this method on each of its neighbors.
*/
void MapDriver::visitTerritory(Territory* territory, vector<Territory*>* visitedCountries)
{
	if (std::find(visitedCountries->begin(), visitedCountries->end(), territory) != visitedCountries->end()) {
		// Territory has already been visited (base case)
		return;
	}
	// Territory has not already been visited (recursive case)
	// Add it to the visited territories, then visit its neighbors
	visitedCountries->push_back(territory);
	const vector<Territory*>* borders = territory->getBorders();
	for (vector<Territory*>::const_iterator it = borders->begin(); it != borders->end(); ++it) {
		visitTerritory(*it, visitedCountries);
	}
}

/*
Checks that each continent is a connected subgraph.
For each continent, performs the same algorithm to check for a connected graph, but does not visit or recurse on territories
that are not in the continent.
*/
void MapDriver::checkContinentsAreConnectedSubgraphs(Map* map)
{
	const std::vector<Continent*>* continents = map->getContinents();

	for (std::vector<Continent*>::const_iterator it = continents->begin(); it != continents->end(); ++it) {
		vector<Territory*> visitedCountries = vector<Territory*>();
		Continent* continent = *it;
		const std::vector<Territory*>* countriesInContinent = continent->getTerritories();

		visitTerritoryInContinent(continent->getTerritories()->at(0), continent, &visitedCountries);

		for (std::vector<Territory*>::const_iterator it = countriesInContinent->begin(); it != countriesInContinent->end(); ++it) {
			if (std::find(visitedCountries.begin(), visitedCountries.end(), *it) == visitedCountries.end()) {
				// Could not find the territory in the list of visited territories, so the continent is not connected
				throw UNCONNECTED_CONTINENT_ERROR;
			}
		}
	}
}

/*
Performs a depth-first search visiting all reachable territories in the same continent.
*/
void MapDriver::visitTerritoryInContinent(Territory* territory, Continent* continent, vector<Territory*>* visitedCountries) {
	if (territory->getContinent() != continent) {
		// Territory is not in continent (base case)
		return;
	}
	
	if (std::find(visitedCountries->begin(), visitedCountries->end(), territory) != visitedCountries->end()) {
		// Territory has already been visited (base case)
		return;
	}

	// Territory has not already been visited (recursive case)
	// Add it to the visited territories, then visit its neighbors
	visitedCountries->push_back(territory);
	const vector<Territory*>* borders = territory->getBorders();
	for (vector<Territory*>::const_iterator it = borders->begin(); it != borders->end(); ++it) {
		visitTerritoryInContinent(*it, continent, visitedCountries);
	}
}

void MapDriver::checkTerritoriesBelongToExactlyOneContinent(Map* map)
{
	const std::vector<Continent*>* continents = map->getContinents();
	
	std::vector<Territory*> visitedCountries = std::vector<Territory*>();

	for (std::vector<Continent*>::const_iterator continentIt = continents->begin(); continentIt != continents->end(); continentIt++) {
		const std::vector<Territory*>* countriesInContinent = (*continentIt)->getTerritories();
		
		for (std::vector<Territory*>::const_iterator territoryIt = countriesInContinent->begin(); territoryIt != countriesInContinent->end(); territoryIt++) {
			if (std::find(visitedCountries.begin(), visitedCountries.end(), *territoryIt) != visitedCountries.end()) {
				//Territory was already found in another continent
				throw TERRITORY_IN_TWO_CONTINENTS_ERROR;
			}
			else {
				visitedCountries.push_back(*territoryIt);
			}
		}
	}

	const std::vector<Territory*>* territories = map->getTerritories();
	
	for (std::vector<Territory*>::const_iterator territoryIt = territories->begin(); territoryIt != territories->end(); territoryIt++) {
		if (std::find(visitedCountries.begin(), visitedCountries.end(), *territoryIt) == visitedCountries.end()) {
			// Could not find the territory in the list of visited territories, so it is not in any continent
			throw TERRITORY_IN_ZERO_CONTINENTS_ERROR;
		}
	}
}
