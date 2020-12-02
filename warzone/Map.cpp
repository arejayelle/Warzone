#include "Map.h"

// Creates a Territory with the given name and position, and belonging to the given Continent.
Territory::Territory(std::string name, Continent* continent, int x, int y)
	: name{ name }, armies{ 0 }, x{ x }, y{ y }, borders{}, continent{ continent }, owner{ nullptr }, incomingArmies{ 0 }
{

}

// Copy constructor of Territory
Territory::Territory(Territory* other)
	: name{ other->name }, armies{ other->armies }, x{ other->x }, y{ other->y }, borders{ other->borders }, continent{ other->continent }, owner{ other->owner }, incomingArmies{ other->incomingArmies }
{

}

// Destructor for Territory. Territory does not own its neighboring countries or its continent (they are owned by Map) and does not own its Player, so it does not destroy them.
Territory::~Territory() {

}

// Assignment operator for Territory
Territory* Territory::operator=(const Territory& territory)
{
	return new Territory(territory);
}

std::string Territory::getName()
{
	return this->name;
}

// Add borders between this country and all countries in the provided borders vector
void Territory::addBorders(std::vector<Territory*>* borders) {
	for (std::vector<Territory*>::iterator it = borders->begin(); it != borders->end(); ++it) {
		this->borders.push_back(*it);
	}
}

// Add a certain number of armies to the territory.
void Territory::addArmies(int amount) {
	this->armies += amount;
}

void Territory::removeArmies(int amount) {
	this->armies -= amount;
}

// Get a read-only vector of all territories bordering this one
const std::vector<Territory*>* Territory::getBorders()
{
	return &borders;
}

// Get the continent in which this territory is located
Continent* Territory::getContinent() {
	return this->continent;
}

void Territory::setOwner(Player* player)
{
	this->owner = player;
}

Player* Territory::getOwner() {
	return this->owner;
}

int Territory::getArmies() {
	return this->armies;
}

void Territory::setIncomingArmies(int armies)
{
	incomingArmies = armies;
}

int Territory::getIncomingArmies()
{
	return incomingArmies;
}

// Stream insertion operator for Territory
std::ostream& operator<<(std::ostream& out, const Territory& territory)
{
	out << territory.name <<  " owned by " << territory.owner << " holding " << territory.armies << " armies.";
	return out;
}

// Constructor to create an empty Continent with the given name, colour and value
Continent::Continent(std::string name, std::string colour, int value)
	: name{ name }, colour{ colour }, value{ value }, territories{ }
{

}

// Copy constructor for Continent
Continent::Continent(Continent* continent)
	: name{ continent->name }, colour{ continent->colour }, value{ continent->value }, territories{ continent->territories }
{

}

// Destructor for Continent. Continent does not own its territories (they are owned by Map) so it does not destroy them
Continent::~Continent() {

}

// Assignment operator for Continent
Continent* Continent::operator=(const Continent& continent)
{
	return new Continent(continent);
}

// Add a territory to this continent
void Continent::addTerritory(Territory* territory)
{
	territories.push_back(territory);
}

// Get a read-only vector of all territories in the continent
const std::vector<Territory*>* Continent::getTerritories() {
	return &territories;
}

// Stream insertion operator for Continent
std::ostream& operator<<(std::ostream& out, const Continent& continent)
{
	out << continent.name << " " << continent.value;
	return out;
}

int Continent::getValue() {
	return value;
}

std::string Continent::getName()
{
	return this->name;
}

/**
 * Check if someone owns all territories in a continent. If so, returns the owner of the continent.
 * 
 * \return The owner of the continent. Returns nullptr if nobody owns the entire continent.
 */
Player* Continent::getContinentOwner() {
	Player* owner = territories.at(0)->getOwner();
	for (std::vector<Territory*>::iterator it = territories.begin(); it != territories.end(); it++) {
		if ((**it).getOwner() != owner) {
			return nullptr;
		}
	}
	return owner;
}

// Construct an empty Map
Map::Map()
	: territories{}, continents{}
{

}

// Copy constructor for Map
Map::Map(Map* other)
{
	territories = {};
	for (std::vector<Territory*>::const_iterator it = other->getTerritories()->begin(); it != other->getTerritories()->end(); it++) {
		territories.push_back(new Territory(**it));
	}

	continents = {};
	for (std::vector<Continent*>::const_iterator it = other->getContinents()->begin(); it != other->getContinents()->end(); it++) {
		continents.push_back(new Continent(**it));
	}
}

// Destructor for Map. Map owns all of its continents and territories, so it must destroy them when it is destroyed
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

// Assignment operator for map
Map* Map::operator=(const Map& map)
{
	return new Map(map);
}

// Add a continent to the map
void Map::addContinent(Continent* continent)
{
	continents.push_back(continent);
}

// Add a territory to the map
void Map::addTerritory(Territory* territory)
{
	territories.push_back(territory);
	territory->getContinent()->addTerritory(territory);
}

// Given the ID of a territory, add borders between it and all given neighbors
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

Territory* Map::getTerritory(std::string territoryName)
{
	const std::vector<Territory*>* listOfTerritories = getTerritories();
	for (int i = 0; i < listOfTerritories->size(); i++) {
		if (listOfTerritories->at(i)->getName() == territoryName) {
			return listOfTerritories->at(i);
		}
	}

	return nullptr;
}

int Map::getTerritoryID(std::string territoryName)
{
	const std::vector<Territory*>* listOfTerritories = getTerritories();
	for (int i = 0; i < listOfTerritories->size(); i++) {
		if (listOfTerritories->at(i)->getName() == territoryName) {
			return i;
		}
	}

	return 0;
}

// Get a read-only vector of the continents in the map
const std::vector<Continent*>* Map::getContinents()
{
	return &continents;
}

Continent* Map::getContinent(std::string continentName)
{
	const std::vector<Continent*>* listOfContinents = getContinents();
	for (int i = 0; i < listOfContinents->size(); i++) {
		if (listOfContinents->at(i)->getName() == continentName) {
			return listOfContinents->at(i);
		}
	}

	return nullptr;
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
Checks that the graph is connected. Throws an exception if validation fails.
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
Checks that each continent is a connected subgraph. Throws an exception if validation fails.
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

// Validates that each territory in the map belongs to exactly one continent. Throws an exception if validation fails.
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

// Stream insertion operator for Map.
std::ostream& operator<<(std::ostream& out, const Map& map)
{
	out << "Map:" << std::endl;

	out << "Continents:" << std::endl;
	for (std::vector<Continent*>::const_iterator it = map.continents.begin(); it != map.continents.end(); it++) {
		out << **it << std::endl;
	}

	out << "Territories:" << std::endl;
	for (std::vector<Territory*>::const_iterator it = map.territories.begin(); it != map.territories.end(); it++) {
		out << **it << std::endl;
	}

	return out;
}

// Error messages generated when validating maps
const std::string Map::UNCONNECTED_MAP_ERROR = "Map is not a connected graph.";
const std::string Map::UNCONNECTED_CONTINENT_ERROR = "Continent is not a connected subgraph";
const std::string Map::TERRITORY_IN_TWO_CONTINENTS_ERROR = "Territory is in two different continents";
const std::string Map::TERRITORY_IN_ZERO_CONTINENTS_ERROR = "Territory is in zero continents";