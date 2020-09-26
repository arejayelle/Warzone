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

	Country* avandria = new Country("Avandria", 0, 375, 450);
	Country* agruntik = new Country("Agruntik", 0, 500, 500);
	Country* apollo = new Country("Apollo", 0, 450, 350);

	Country* burgundy = new Country("Burgundy", 1, 250, 600);
	Country* byzantium = new Country("Byzantium", 1, 300, 475);

	Country* crestwall = new Country("Crestwall", 2, 600, 150);
	Country* cruthnik = new Country("Cruthnik", 2, 500, 250);

	map->addCountry(avandria);
	map->addCountry(agruntik);
	map->addCountry(apollo);
	map->addCountry(burgundy);
	map->addCountry(byzantium);
	map->addCountry(crestwall);
	map->addCountry(cruthnik);

	vector<int> avandriaBorders{ 1, 2 };
	vector<int> agruntikBorders{ 0, 2, 3, 4 };
	vector<int> apolloBorders{ 0, 1, 5 };
	vector<int> burgundyBorders{ 1, 4 };
	vector<int> byzantiumBorders{ 3, 5, 6 };
	vector<int> crestwallBorders{ 2, 4, 6 };
	vector<int> cruthnikBorders{ 4, 5 };

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

	Country* unconnectedCountry = new Country("Unconnected", 0, 1000, 1000);
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
	visitCountry(map, 0, &visitedCountries);
	
	const vector<Country*>* allCountries = map->getCountries();
	for (vector<Country*>::const_iterator it = allCountries->begin(); it != allCountries->end(); ++it) {
		if (std::find(visitedCountries.begin(), visitedCountries.end(), *it) == visitedCountries.end()) {
			// Could not find the country in the list of visited countries, so the graph is not connected
			throw UNCONNECTED_MAP_ERROR;
		}
	}
}

// Recursively visit the given country and its neighbors, adding them to the list of visited countries
void MapDriver::visitCountry(Map* map, int countryId, vector<Country*>* visitedCountries)
{
	Country* country = map->getCountry(countryId);
	if (std::find(visitedCountries->begin(), visitedCountries->end(), country) != visitedCountries->end()) {
		// Country has already been visited (base case)
		return;
	}
	// Country has not already been visited (recursive case)
	// Add it to the visited countries, then visit its neighbors
	visitedCountries->push_back(country);
	vector<int>* borders = country->getBorders();
	for (vector<int>::iterator it = borders->begin(); it != borders->end(); ++it) {
		visitCountry(map, *it, visitedCountries);
	}
}

void MapDriver::checkContinentsAreConnectedSubgraphs(Map* map)
{
}

void MapDriver::checkCountriesBelongToExactlyOneContinent(Map* map)
{
}
