#include "Map.h"

Country::Country(std::string* name, int* continent, int* x, int* y)
{
	this->name = name;
	this->continent = continent;
	this->x = x;
	this->y = y;
	this->borders = new std::vector<int>();
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

int* Country::getContinent() {
	return this->continent;
}

Continent::Continent(std::string* name, std::string* colour, int* value) {
	this->name = name;
	this->colour = colour;
	this->value = value;
	this->countries = new std::vector<Country*>();
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

void Map::addBorder(int* countryId, std::vector<int>* neighbors)
{
	Country* country = countries->at(*countryId);
	country->addBorders(neighbors);
}