#pragma once
#include "Map.h"
#include <string>

namespace MapDriver {
	int main();

	Map* getValidMap();

	Map* getUnconnectedMap();
	
	void validateMap(Map* map);
	void checkMapIsConnectedGraph(Map* map);
	void visitCountry(Map* map, Country* countryId, std::vector<Country*>* visitedCountries);
	void checkContinentsAreConnectedSubgraphs(Map* map);
	void checkCountriesBelongToExactlyOneContinent(Map* map);

	static const std::string UNCONNECTED_MAP_ERROR = "Map is not a connected graph.";
}