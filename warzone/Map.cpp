#include "Map.h"

Territory::Territory(std::string name, Continent* continent, int x, int y)
{
	this->name = new std::string(name);
	this->continent = continent;
	this->x = new int(x);
	this->y = new int(y);
	this->borders = new std::vector<Territory*>();
}

Territory::Territory(Territory* other) {
	name = new std::string(*other->name);
	continent = other->continent;
	x = new int(*other->x);
	y = new int(*other->y);
	this->borders = new std::vector<Territory*>(*other->borders);
}

Territory::~Territory() {
	delete name;
	delete continent;
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
