#include "Map.h"

Territory::Territory(std::string name, Continent* continent, int x, int y)
{
	this->name = new std::string(name);
	this->continent = continent;
	// At the time of creation of a map, it is not known who the territory belongs to, and territories may belong to noone.
	this->owner = nullptr;
	this->armies = new int(0);
	this->x = new int(x);
	this->y = new int(y);
	this->borders = new std::vector<Territory*>();
}

Territory::Territory(Territory* other) {
	name = new std::string(*other->name);
	continent = other->continent;
	this->owner = other->owner;
	this->armies = new int(*other->armies);
	x = new int(*other->x);
	y = new int(*other->y);
	this->borders = new std::vector<Territory*>(*other->borders);
}

Territory::~Territory() {
	delete name;
	delete continent;
	delete armies;
	delete x;
	delete y;
	borders->clear();
	delete borders;
}

void Territory::addBorders(std::vector<Territory*>* borders) {
	for (std::vector<Territory*>::iterator it = borders->begin(); it != borders->end(); ++it) {
		this->borders->push_back(*it);
	}
}

const std::vector<Territory*>* Territory::getBorders()
{
	return borders;
}

Continent* Territory::getContinent() {
	return this->continent;
}

Continent::Continent(std::string name, std::string colour, int value) {
	this->name = new std::string(name);
	this->colour = new std::string(colour);
	this->value = new int(value);
	this->territories = new std::vector<Territory*>();
}

Continent::Continent(Continent* continent) {
	name = new std::string(*continent->name);
	colour = new std::string(*continent->name);
	this->value = new int(*continent->value);
	this->territories = new std::vector<Territory*>(*continent->territories);
}

Continent::~Continent() {
	delete name;
	delete colour;
	delete value;
	delete territories;
}

void Continent::addTerritory(Territory* territory)
{
	territories->push_back(territory);
}

const std::vector<Territory*>* Continent::getTerritories() {
	return territories;
}

Map::Map()
{
	territories = new std::vector<Territory*>();
	continents = new std::vector<Continent*>();
}

Map::Map(Map* other)
{
	territories = new std::vector<Territory*>(*other->territories);
	continents = new std::vector<Continent*>(*other->continents);
}

Map::~Map() {
	territories->clear();
	delete territories;

	continents->clear();
	delete continents;
}

void Map::addContinent(Continent* continent)
{
	continents->push_back(continent);
}

void Map::addTerritory(Territory* territory)
{
	territories->push_back(territory);
	territory->getContinent()->addTerritory(territory);
}

void Map::addBorder(int territoryId, std::vector<Territory*>* neighbors)
{
	Territory* territory = territories->at(territoryId);
	territory->addBorders(neighbors);
}

Continent* Map::getContinent(int continentId)
{
	return continents->at(continentId);
}

Territory* Map::getTerritory(int territoryId)
{
	return territories->at(territoryId);
}

const std::vector<Continent*>* Map::getContinents()
{
	return continents;
}

const std::vector<Territory*>* Map::getTerritories()
{
	return territories;
}


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

const std::string Map::UNCONNECTED_MAP_ERROR = "Map is not a connected graph.";
const std::string Map::UNCONNECTED_CONTINENT_ERROR = "Continent is not a connected subgraph";
const std::string Map::TERRITORY_IN_TWO_CONTINENTS_ERROR = "Territory is in two different continents";
const std::string Map::TERRITORY_IN_ZERO_CONTINENTS_ERROR = "Territory is in zero continents";