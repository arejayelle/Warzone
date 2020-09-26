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
	
	void validateMap(Map* map);
	void checkMapIsConnectedGraph(Map* map);
	void visitTerritory(Territory* territoryId, std::vector<Territory*>* visitedTerritories);
	void checkContinentsAreConnectedSubgraphs(Map* map);
	void visitTerritoryInContinent(Territory* territory, Continent* continent, std::vector<Territory*>* visitedTerritories);
	void checkTerritoriesBelongToExactlyOneContinent(Map* map);

	static const std::string UNCONNECTED_MAP_ERROR = "Map is not a connected graph.";
	static const std::string UNCONNECTED_CONTINENT_ERROR = "Continent is not a connected subgraph";
	static const std::string TERRITORY_IN_TWO_CONTINENTS_ERROR = "Territory is in two different continents";
	static const std::string TERRITORY_IN_ZERO_CONTINENTS_ERROR = "Territory is in zero continents";
}