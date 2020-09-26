#pragma once

#include <vector>
#include <string>

class Continent;

class Territory {
public:
	Territory(std::string name, Continent* continent, int x, int y);
	Territory(Territory* other);

	~Territory();

	void addBorders(std::vector<Territory*>* borders);
	const std::vector<Territory*>* getBorders();
	Continent* getContinent();
	
private:
	std::string* name;
	Continent* continent;
	int* x;
	int* y;
	std::vector<Territory*>* borders;
};

class Continent {
public:
	Continent(std::string name, std::string colour, int value);
	Continent(Continent* other);
	~Continent();
	void addTerritory(Territory* territory);
	const std::vector<Territory*>* getTerritories();

private:
	std::string* name;
	std::string* colour;
	int* value; // The number of bonus troops a player earns for controlling the continent
	std::vector<Territory*>* territories;
};

class Map {
public:
	Map();
	~Map();

	void addContinent(Continent* continent);
	void addTerritory(Territory* territory);
	void addBorder(int territory, std::vector<Territory*>* neighbors);

	Continent* getContinent(int continentId);
	Territory* getTerritory(int territoryId);

	const std::vector<Continent*>* getContinents();
	const std::vector<Territory*>* getTerritories();

private:
	std::vector<Continent*>* continents;
	std::vector<Territory*>* territories;
};