#include "Map.h"

Country::Country(std::string name, int continent, int x, int y)
{
	this->name = new std::string(name);
	this->continent = new int(continent);
	this->x = new int(x);
	this->y = new int(y);
	this->borders = new std::vector<int>();
}

Country::Country(Country* other) {
	name = new std::string(*other->name);
	continent = new int(*other->continent);
	x = new int(*other->x);
	y = new int(*other->y);
	this->borders = new std::vector<int>(*other->borders);
}

Country::~Country() {
	delete name;
	delete continent;
	delete x;
	delete y;
	borders->clear();
	delete borders;
}

void Country::addBorders(std::vector<int>* borders) {
	for (std::vector<int>::iterator it = borders->begin(); it != borders->end(); ++it) {
		this->borders->push_back(*it);
	}
}

std::vector<int>* Country::getBorders()
{
	return borders;
}

int* Country::getContinent() {
	return this->continent;
}

Continent::Continent(std::string name, std::string colour, int value) {
	this->name = new std::string(name);
	this->colour = new std::string(colour);
	this->value = new int(value);
	this->countries = new std::vector<Country*>();
}

Continent::~Continent() {
	delete name;
	delete colour;
	delete value;
	delete countries;
}

void Continent::addCountry(Country* country)
{
	this->countries->push_back(country);
}

Map::Map()
{
	countries = new std::vector<Country*>();
	continents = new std::vector<Continent*>();
}

Map::~Map() {
	countries->clear();
	delete countries;

	continents->clear();
	delete continents;
}

void Map::addContinent(Continent* continent)
{
	continents->push_back(continent);
}

void Map::addCountry(Country* country)
{
	countries->push_back(country);
	
	int* continentId = country->getContinent();
	Continent* continent = continents->at(*continentId);
	continent->addCountry(country);
}

void Map::addBorder(int countryId, std::vector<int>* neighbors)
{
	Country* country = countries->at(countryId);
	country->addBorders(neighbors);
}

Continent* Map::getContinent(int continentId)
{
	return continents->at(continentId);
}

Country* Map::getCountry(int countryId)
{
	return countries->at(countryId);
}

const std::vector<Country*>* Map::getCountries()
{
	return countries;
}
