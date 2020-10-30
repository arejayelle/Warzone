#pragma once

#include <vector>
#include <string>
#include "Player.h"
#include <iostream>

class Continent;
class Player;

class Territory {
public:
	Territory(std::string name, Continent* continent, int x, int y);
	Territory(Territory* other);
	~Territory();
	Territory* operator= (const Territory& territory);

	void addBorders(std::vector<Territory*>* borders);
	const std::vector<Territory*>* getBorders();
	void addArmies(int amount);
	void removeArmies(int amount);
	Continent* getContinent();
	Player* getOwner();
	void setOwner(Player* player);
	int getArmies();
	friend std::ostream& operator<< (std::ostream& out, const Territory& territory);

private:
	std::string name;
	Continent* continent;
	Player* owner;
	int armies;
	int x;
	int y;
	std::vector<Territory*> borders;
};

class Continent {
public:
	Continent(std::string name, std::string colour, int value);
	Continent(Continent* other);
	~Continent();
	Continent* operator= (const Continent& continent);

	void addTerritory(Territory* territory);
	const std::vector<Territory*>* getTerritories();
	friend std::ostream& operator<< (std::ostream& out, const Continent& continent);

	Player* getContinentOwner();

private:
	std::string name;
	std::string colour;
	int value; // The number of bonus troops a player earns for controlling the continent
	std::vector<Territory*> territories;
};

class Map {
public:
	Map();
	Map(Map* other);
	~Map();
	Map* operator= (const Map& map);

	void addContinent(Continent* continent);
	void addTerritory(Territory* territory);
	void addBorder(int territory, std::vector<Territory*>* neighbors);

	Continent* getContinent(int continentId);
	Territory* getTerritory(int territoryId);

	const std::vector<Continent*>* getContinents();
	const std::vector<Territory*>* getTerritories();

	void validate();
	void checkMapIsConnectedGraph();
	void checkContinentsAreConnectedSubgraphs();
	void checkTerritoriesBelongToExactlyOneContinent();

	friend std::ostream& operator<< (std::ostream& out, const Map& map);

	static const std::string UNCONNECTED_MAP_ERROR;
	static const std::string UNCONNECTED_CONTINENT_ERROR;
	static const std::string TERRITORY_IN_TWO_CONTINENTS_ERROR;
	static const std::string TERRITORY_IN_ZERO_CONTINENTS_ERROR;

private:
	std::vector<Continent*> continents;
	std::vector<Territory*> territories;

	void visitTerritory(Territory* territoryId, std::vector<Territory*>* visitedTerritories);
	void visitTerritoryInContinent(Territory* territory, Continent* continent, std::vector<Territory*>* visitedTerritories);
};