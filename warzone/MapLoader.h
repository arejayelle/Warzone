#pragma once
#include "Map.h"
#include <string>
#include <vector>

class MapLoader {
public:
	MapLoader();
	MapLoader(std::string fileName);
	~MapLoader();
	bool validateMap();
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