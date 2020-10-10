#pragma once
#include "Map.h"
#include <string>
#include <vector>
#include <iostream>

class MapLoader {
public:
	MapLoader(MapLoader* mapL);
	MapLoader(std::string fileName);
	~MapLoader();
	MapLoader* operator= (const MapLoader& mapLoader);
	friend std::ostream& operator<< (std::ostream& out, const MapLoader& mapLoader);
	bool validateMapFormat();
	Map* convertFileToMap();
	

private:
	std::string* fileName;
	bool checkContinents(std::string continent);
	bool checkTerritory(std::string country);
	bool checkBorders(std::string border);
	Continent* createContinent(std::string continent);
	Territory* createTerritory(std::string country, Map* map);
	void createBorder(std::string border, Map* map);
};