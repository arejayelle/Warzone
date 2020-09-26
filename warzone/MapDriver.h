#pragma once
#include "Map.h"
#include <string>

namespace MapDriver {
	int main();

	Map* getValidMap();
	Map* getUnconnectedMap();
	Map* getUnconnectedContinentMap();
	
	void validateMap(Map* map);
	void checkMapIsConnectedGraph(Map* map);
	void visitCountry(Country* countryId, std::vector<Country*>* visitedCountries);
	void checkContinentsAreConnectedSubgraphs(Map* map);
	void visitCountryInContinent(Country* country, Continent* continent, std::vector<Country*>* visitedCountries);
	void checkCountriesBelongToExactlyOneContinent(Map* map);

	static const std::string UNCONNECTED_MAP_ERROR = "Map is not a connected graph.";
	static const std::string UNCONNECTED_CONTINENT_ERROR = "Continent is not a connected subgraph";
}