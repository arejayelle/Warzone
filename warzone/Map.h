#pragma once

#include <vector>
#include <string>

class Country {
public:
	Country(std::string name, int continent, int x, int y);
	Country(Country* other);

	~Country();

	void addBorders(std::vector<int>* borders);
	std::vector<int>* getBorders();
	int* getContinent();
	
private:
	std::string* name;
	int* continent;
	int* x;
	int* y;
	std::vector<int>* borders;
};

class Continent {
public:
	Continent(std::string name, std::string colour, int value);
	~Continent();
	void addCountry(Country* country);

private:
	std::string* name;
	std::string* colour;
	int* value; // The number of bonus troops a player earns for controlling the continent
	std::vector<Country*>* countries;
};

class Map {
public:
	Map();
	~Map();

	void addContinent(Continent* continent);
	void addCountry(Country* country);
	void addBorder(int country, std::vector<int>* neighbors);

	Continent* getContinent(int continentId);
	Country* getCountry(int countryId);

	const std::vector<Country*>* getCountries();

private:
	std::vector<Continent*>* continents;
	std::vector<Country*>* countries;
};