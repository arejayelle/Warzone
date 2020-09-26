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

	Map* mapWithCountryInNoContinents = getMapCountryInNoContinents();
	try {
		checkCountriesBelongToExactlyOneContinent(mapWithCountryInNoContinents);
	}
	catch (std::string exception) {
		assert(exception.compare(COUNTRY_IN_ZERO_CONTINENTS_ERROR) == 0);
	}

	Map* mapWithCountryInTwoContinents = getMapCountryInTwoContinents();
	try {
		checkCountriesBelongToExactlyOneContinent(mapWithCountryInTwoContinents);
	}
	catch (std::string exception) {
		assert(exception.compare(COUNTRY_IN_TWO_CONTINENTS_ERROR) == 0);
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

Map* MapDriver::getMapUnconnected() {
	Map* map = getValidMap();

	Country* unconnectedCountry = new Country("Unconnected", map->getContinent(0), 1000, 1000);
	map->addCountry(unconnectedCountry);

	return map;
}

Map* MapDriver::getMapUnconnectedContinent() {
	Map* map = getValidMap();

	Country* unconnectedCountry = new Country("Unconnected", map->getContinent(0), 1000, 1000);
	map->addCountry(unconnectedCountry);

	Country* neighbor = map->getCountry(6);
	vector<Country*> borders = { neighbor };
	vector<Country*> neighborBorders = { unconnectedCountry };
	unconnectedCountry->addBorders(&borders);
	neighbor->addBorders(&neighborBorders);

	return map;
}

Map* MapDriver::getMapCountryInNoContinents() {
	Map* map = getValidMap();
	
	Continent* fakeContinent = new Continent("Fake", "colour", 5);
	Country* countryNotInContinent = new Country("NoContinentCountry", fakeContinent, 1000, 1000);
	map->addCountry(countryNotInContinent);
	delete(fakeContinent);

	Country* neighbor = map->getCountry(6);
	vector<Country*> borders = { neighbor };
	vector<Country*> neighborBorders{ countryNotInContinent };
	countryNotInContinent->addBorders(&borders);
	neighbor->addBorders(&neighborBorders);

	return map;
}

Map* MapDriver::getMapCountryInTwoContinents() {
	Map* map = getValidMap();

	Continent* continentOne = map->getContinent(0);
	Continent* continentTwo = map->getContinent(1);
	Country* countryInTwoContinents = new Country("TwoContinentCountry", continentOne, 1000, 1000);
	map->addCountry(countryInTwoContinents);
	continentTwo->addCountry(countryInTwoContinents);

	Country* neighborFromContinentOne = map->getCountry(1);
	Country* neighborFromContinentTwo = map->getCountry(3);
	vector<Country*> borders = { neighborFromContinentOne, neighborFromContinentTwo };
	vector<Country*> neighborBorders{ countryInTwoContinents };
	countryInTwoContinents->addBorders(&borders);
	neighborFromContinentOne->addBorders(&neighborBorders);
	neighborFromContinentTwo->addBorders(&neighborBorders);

	return map;
}

void MapDriver::validateMap(Map* map) {
	checkMapIsConnectedGraph(map);
	checkContinentsAreConnectedSubgraphs(map);
	checkCountriesBelongToExactlyOneContinent(map);
}

/*
Checks that the graph is connected.
Start at node 0. Perform a depth-first search of the graph, visiting every node that is connected to the starting node. 
Mark each node as visited by adding it to a list. At the end of the search, if every node in the graph is in the list 
of visited nodes, the graph is connected.
*/
void MapDriver::checkMapIsConnectedGraph(Map* map)
{
	vector<Country*> visitedCountries = vector<Country*>();
	visitCountry(map->getCountry(0), &visitedCountries);
	
	const vector<Country*>* allCountries = map->getCountries();
	for (vector<Country*>::const_iterator it = allCountries->begin(); it != allCountries->end(); ++it) {
		if (std::find(visitedCountries.begin(), visitedCountries.end(), *it) == visitedCountries.end()) {
			// Could not find the country in the list of visited countries, so the graph is not connected
			throw UNCONNECTED_MAP_ERROR;
		}
	}
}

/*
Performs a depth-first search recursively from the given country. If it is not visited, add it to the list
of visited countries. Then, call this method on each of its neighbors.
*/
void MapDriver::visitCountry(Country* country, vector<Country*>* visitedCountries)
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
		visitCountry(*it, visitedCountries);
	}
}

/*
Checks that each continent is a connected subgraph.
For each continent, performs the same algorithm to check for a connected graph, but does not visit or recurse on countries
that are not in the continent.
*/
void MapDriver::checkContinentsAreConnectedSubgraphs(Map* map)
{
	const std::vector<Continent*>* continents = map->getContinents();

	for (std::vector<Continent*>::const_iterator it = continents->begin(); it != continents->end(); ++it) {
		vector<Country*> visitedCountries = vector<Country*>();
		Continent* continent = *it;
		const std::vector<Country*>* countriesInContinent = continent->getCountries();

		visitCountryInContinent(continent->getCountries()->at(0), continent, &visitedCountries);

		for (std::vector<Country*>::const_iterator it = countriesInContinent->begin(); it != countriesInContinent->end(); ++it) {
			if (std::find(visitedCountries.begin(), visitedCountries.end(), *it) == visitedCountries.end()) {
				// Could not find the country in the list of visited countries, so the continent is not connected
				throw UNCONNECTED_CONTINENT_ERROR;
			}
		}
	}
}

/*
Performs a depth-first search visiting all reachable countries in the same continent.
*/
void MapDriver::visitCountryInContinent(Country* country, Continent* continent, vector<Country*>* visitedCountries) {
	if (country->getContinent() != continent) {
		// Country is not in continent (base case)
		return;
	}
	
	if (std::find(visitedCountries->begin(), visitedCountries->end(), country) != visitedCountries->end()) {
		// Country has already been visited (base case)
		return;
	}

	// Country has not already been visited (recursive case)
	// Add it to the visited countries, then visit its neighbors
	visitedCountries->push_back(country);
	const vector<Country*>* borders = country->getBorders();
	for (vector<Country*>::const_iterator it = borders->begin(); it != borders->end(); ++it) {
		visitCountryInContinent(*it, continent, visitedCountries);
	}
}

void MapDriver::checkCountriesBelongToExactlyOneContinent(Map* map)
{
	const std::vector<Continent*>* continents = map->getContinents();
	
	std::vector<Country*> visitedCountries = std::vector<Country*>();

	for (std::vector<Continent*>::const_iterator continentIt = continents->begin(); continentIt != continents->end(); continentIt++) {
		const std::vector<Country*>* countriesInContinent = (*continentIt)->getCountries();
		
		for (std::vector<Country*>::const_iterator countryIt = countriesInContinent->begin(); countryIt != countriesInContinent->end(); countryIt++) {
			if (std::find(visitedCountries.begin(), visitedCountries.end(), *countryIt) != visitedCountries.end()) {
				//Country was already found in another continent
				throw COUNTRY_IN_TWO_CONTINENTS_ERROR;
			}
			else {
				visitedCountries.push_back(*countryIt);
			}
		}
	}

	const std::vector<Country*>* countries = map->getCountries();
	
	for (std::vector<Country*>::const_iterator countryIt = countries->begin(); countryIt != countries->end(); countryIt++) {
		if (std::find(visitedCountries.begin(), visitedCountries.end(), *countryIt) == visitedCountries.end()) {
			// Could not find the country in the list of visited countries, so it is not in any continent
			throw COUNTRY_IN_ZERO_CONTINENTS_ERROR;
		}
	}
}
