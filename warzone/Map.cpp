#include "Map.h"

Country::Country(std::string name, Continent* continent, int x, int y)
{
	this->name = new std::string(name);
	this->continent = continent;
	this->x = new int(x);
	this->y = new int(y);
	this->borders = new std::vector<Country*>();
}

Country::Country(Country* other) {
	name = new std::string(*other->name);
	continent = other->continent;
	x = new int(*other->x);
	y = new int(*other->y);
	this->borders = new std::vector<Country*>(*other->borders);
}

Country::~Country() {
	delete name;
	delete continent;
	delete x;
	delete y;
	borders->clear();
	delete borders;
}

void Country::addBorders(std::vector<Country*>* borders) {
	for (std::vector<Country*>::iterator it = borders->begin(); it != borders->end(); ++it) {
		this->borders->push_back(*it);
	}
}

const std::vector<Country*>* Country::getBorders()
{
	return borders;
}

Continent* Country::getContinent() {
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
	country->getContinent()->addCountry(country);
}

void Map::addBorder(int countryId, std::vector<Country*>* neighbors)
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
