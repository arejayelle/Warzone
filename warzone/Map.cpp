#include "Map.h"

Territory::Territory(std::string name, Continent* continent, int x, int y)
	: name{ name }, armies{ 0 }, x{ x }, y{ y }, borders{}
{
	this->continent = continent;
	// At the time of creation of a map, it is not known who the territory belongs to, and territories may belong to noone.
	this->owner = nullptr;
}

Territory::Territory(Territory* other)
	: name{ other->name }, armies{ other->armies }, x{ other->x }, y{ other->y }, borders{ other->borders }
{
	continent = other->continent;
	this->owner = other->owner;
}

Territory::~Territory() {

}

Territory* Territory::operator=(const Territory& territory)
{
	return new Territory(territory);
}

void Territory::addBorders(std::vector<Territory*>* borders) {
	for (std::vector<Territory*>::iterator it = borders->begin(); it != borders->end(); ++it) {
		this->borders.push_back(*it);
	}
}

const std::vector<Territory*>* Territory::getBorders()
{
	return &borders;
}

Continent* Territory::getContinent() {
	return this->continent;
}

std::ostream& operator<<(std::ostream& out, const Territory& territory)
{
	out << territory.name;
	return out;
}

Continent::Continent(std::string name, std::string colour, int value)
	: name{ name }, colour{ colour }, value{ value }, territories{ }
{

}

Continent::Continent(Continent* continent)
	: name{ continent->name }, colour{ continent->colour }, value{ continent->value }, territories{ continent->territories }
{

}

Continent::~Continent() {

}

Continent* Continent::operator=(const Continent& continent)
{
	return new Continent(continent);
}

void Continent::addTerritory(Territory* territory)
{
	territories.push_back(territory);
}

const std::vector<Territory*>* Continent::getTerritories() {
	return &territories;
}

std::ostream& operator<<(std::ostream& out, const Continent& continent)
{
	out << continent.name;
	return out;
}

Map::Map()
	: territories{}, continents{}
{

}

Map::Map(Map* other)
	: territories{ other->territories }, continents{ other->continents }
{

}

Map::~Map() {
	for (std::vector<Territory*>::iterator it = territories.begin(); it != territories.end(); it++) {
		delete *it;
	}
	territories.clear();

	for (std::vector<Continent*>::iterator it = continents.begin(); it != continents.end(); it++) {
		delete* it;
	}
	continents.clear();
}

Map* Map::operator=(const Map& map)
{
	return new Map(map);
}

void Map::addContinent(Continent* continent)
{
	continents.push_back(continent);
}

void Map::addTerritory(Territory* territory)
{
	territories.push_back(territory);
	territory->getContinent()->addTerritory(territory);
}

void Map::addBorder(int territoryId, std::vector<Territory*>* neighbors)
{
	Territory* territory = territories.at(territoryId);
	territory->addBorders(neighbors);
}

// Get a continent in the map by its ID (its index in the array)
Continent* Map::getContinent(int continentId)
{
	return continents.at(continentId);
}

// Get a territory in the map by its ID (its index in the array)
Territory* Map::getTerritory(int territoryId)
{
	return territories.at(territoryId);
}

// Get a read-only vector of the continents in the map
const std::vector<Continent*>* Map::getContinents()
{
	return &continents;
}

// Get a read-only vector of the territories in the map
const std::vector<Territory*>* Map::getTerritories()
{
	return &territories;
}

// Validate that the map is correct
void Map::validate() {
	checkMapIsConnectedGraph();
	checkContinentsAreConnectedSubgraphs();
	checkTerritoriesBelongToExactlyOneContinent();
}

/*
Checks that the graph is connected.
Start at node 0. Perform a depth-first search of the graph, visiting every node that is connected to the starting node.
Mark each node as visited by adding it to a list. At the end of the search, if every node in the graph is in the list
of visited nodes, the graph is connected.
*/
void Map::checkMapIsConnectedGraph()
{
	std::vector<Territory*> visitedCountries = std::vector<Territory*>();
	visitTerritory(getTerritory(0), &visitedCountries);

	const std::vector<Territory*>* allCountries = getTerritories();
	for (std::vector<Territory*>::const_iterator it = allCountries->begin(); it != allCountries->end(); ++it) {
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
void Map::visitTerritory(Territory* territory, std::vector<Territory*>* visitedCountries)
{
	if (std::find(visitedCountries->begin(), visitedCountries->end(), territory) != visitedCountries->end()) {
		// Territory has already been visited (base case)
		return;
	}
	// Territory has not already been visited (recursive case)
	// Add it to the visited territories, then visit its neighbors
	visitedCountries->push_back(territory);
	const std::vector<Territory*>* borders = territory->getBorders();
	for (std::vector<Territory*>::const_iterator it = borders->begin(); it != borders->end(); ++it) {
		visitTerritory(*it, visitedCountries);
	}
}

/*
Checks that each continent is a connected subgraph.
For each continent, performs the same algorithm to check for a connected graph, but does not visit or recurse on territories
that are not in the continent.
*/
void Map::checkContinentsAreConnectedSubgraphs()
{
	const std::vector<Continent*>* continents = getContinents();

	for (std::vector<Continent*>::const_iterator it = continents->begin(); it != continents->end(); ++it) {
		std::vector<Territory*> visitedCountries = std::vector<Territory*>();
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
void Map::visitTerritoryInContinent(Territory* territory, Continent* continent, std::vector<Territory*>* visitedCountries) {
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
	const std::vector<Territory*>* borders = territory->getBorders();
	for (std::vector<Territory*>::const_iterator it = borders->begin(); it != borders->end(); ++it) {
		visitTerritoryInContinent(*it, continent, visitedCountries);
	}
}

void Map::checkTerritoriesBelongToExactlyOneContinent()
{
	const std::vector<Continent*>* continents = getContinents();

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

	const std::vector<Territory*>* territories = getTerritories();

	for (std::vector<Territory*>::const_iterator territoryIt = territories->begin(); territoryIt != territories->end(); territoryIt++) {
		if (std::find(visitedCountries.begin(), visitedCountries.end(), *territoryIt) == visitedCountries.end()) {
			// Could not find the territory in the list of visited territories, so it is not in any continent
			throw Map::TERRITORY_IN_ZERO_CONTINENTS_ERROR;
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Map& map)
{
	out << "Map:" << std::endl;

	out << "Continents:" << std::endl;
	for (std::vector<Continent*>::const_iterator it = map.continents.begin(); it != map.continents.end(); it++) {
		out << *it << std::endl;
	}

	out << "Territories:" << std::endl;
	for (std::vector<Territory*>::const_iterator it = map.territories.begin(); it != map.territories.end(); it++) {
		out << *it << std::endl;
	}

	return out;
}

const std::string Map::UNCONNECTED_MAP_ERROR = "Map is not a connected graph.";
const std::string Map::UNCONNECTED_CONTINENT_ERROR = "Continent is not a connected subgraph";
const std::string Map::TERRITORY_IN_TWO_CONTINENTS_ERROR = "Territory is in two different continents";
const std::string Map::TERRITORY_IN_ZERO_CONTINENTS_ERROR = "Territory is in zero continents";