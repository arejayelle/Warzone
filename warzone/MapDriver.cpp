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

	Map* unconnectedMap = getUnconnectedMap();
	try {
		validateMap(unconnectedMap);
	}
	catch (std::string exception) {
		assert(exception.compare(UNCONNECTED_MAP_ERROR) == 0);
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

	Country* avandria = new Country("Avandria", amadicia, 375, 450);
	Country* agruntik = new Country("Agruntik", amadicia, 500, 500);
	Country* apollo = new Country("Apollo", amadicia, 450, 350);

	Country* burgundy = new Country("Burgundy", bellovia, 250, 600);
	Country* byzantium = new Country("Byzantium", bellovia, 300, 475);

	Country* crestwall = new Country("Crestwall", caelandia, 600, 150);
	Country* cruthnik = new Country("Cruthnik", caelandia, 500, 250);

	map->addCountry(avandria);
	map->addCountry(agruntik);
	map->addCountry(apollo);
	map->addCountry(burgundy);
	map->addCountry(byzantium);
	map->addCountry(crestwall);
	map->addCountry(cruthnik);

	vector<Country*> avandriaBorders{ agruntik, apollo };
	vector<Country*> agruntikBorders{ avandria, apollo, burgundy, byzantium };
	vector<Country*> apolloBorders{ avandria, agruntik, crestwall };
	vector<Country*> burgundyBorders{ agruntik, byzantium };
	vector<Country*> byzantiumBorders{ burgundy, crestwall, cruthnik };
	vector<Country*> crestwallBorders{ apollo, byzantium, cruthnik };
	vector<Country*> cruthnikBorders{ byzantium, crestwall };

	map->addBorder(0, &avandriaBorders);
	map->addBorder(1, &agruntikBorders);
	map->addBorder(2, &apolloBorders);
	map->addBorder(3, &burgundyBorders);
	map->addBorder(4, &byzantiumBorders);
	map->addBorder(5, &crestwallBorders);
	map->addBorder(6, &cruthnikBorders);

	return map;
}

Map* MapDriver::getUnconnectedMap() {
	Map* map = getValidMap();

	Country* unconnectedCountry = new Country("Unconnected", map->getContinent(0), 1000, 1000);
	map->addCountry(unconnectedCountry);

	return map;
}

void MapDriver::validateMap(Map* map) {
	checkMapIsConnectedGraph(map);
	checkContinentsAreConnectedSubgraphs(map);
	checkCountriesBelongToExactlyOneContinent(map);
}

void MapDriver::checkMapIsConnectedGraph(Map* map)
{
	vector<Country*> visitedCountries = vector<Country*>();
	visitCountry(map, map->getCountry(0), &visitedCountries);
	
	const vector<Country*>* allCountries = map->getCountries();
	for (vector<Country*>::const_iterator it = allCountries->begin(); it != allCountries->end(); ++it) {
		if (std::find(visitedCountries.begin(), visitedCountries.end(), *it) == visitedCountries.end()) {
			// Could not find the country in the list of visited countries, so the graph is not connected
			throw UNCONNECTED_MAP_ERROR;
		}
	}
}

// Recursively visit the given country and its neighbors, adding them to the list of visited countries
void MapDriver::visitCountry(Map* map, Country* country, vector<Country*>* visitedCountries)
{
	if (std::find(visitedCountries->begin(), visitedCountries->end(), country) != visitedCountries->end()) {
		// Country has already been visited (base case)
		return;
	}
	// Country has not already been visited (recursive case)
	// Add it to the visited countries, then visit its neighbors
	visitedCountries->push_back(country);
	const vector<Country*>* borders = country->getBorders();
	for (vector<Country*>::const_iterator it = borders->begin(); it != borders->end(); ++it) {
		visitCountry(map, *it, visitedCountries);
	}
}

void MapDriver::checkContinentsAreConnectedSubgraphs(Map* map)
{
}

void MapDriver::checkCountriesBelongToExactlyOneContinent(Map* map)
{
}
