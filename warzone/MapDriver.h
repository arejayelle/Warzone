#pragma once
#include "Map.h"
#include <string>

namespace MapDriver {
	int main();

	Map* getValidMap();
	Map* getMapUnconnected();
	Map* getMapUnconnectedContinent();
	Map* getMapCountryInNoContinents();
	Map* getMapCountryInTwoContinents();
	
	void validateMap(Map* map);
	void checkMapIsConnectedGraph(Map* map);
	void visitCountry(Country* countryId, std::vector<Country*>* visitedCountries);
	void checkContinentsAreConnectedSubgraphs(Map* map);
	void visitCountryInContinent(Country* country, Continent* continent, std::vector<Country*>* visitedCountries);
	void checkCountriesBelongToExactlyOneContinent(Map* map);

	static const std::string UNCONNECTED_MAP_ERROR = "Map is not a connected graph.";
	static const std::string UNCONNECTED_CONTINENT_ERROR = "Continent is not a connected subgraph";
	static const std::string COUNTRY_IN_TWO_CONTINENTS_ERROR = "Country is in two different continents";
	static const std::string COUNTRY_IN_ZERO_CONTINENTS_ERROR = "Country is in zero continents";
}