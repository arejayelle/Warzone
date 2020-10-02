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
	void createContinent(std::string continent);
	void createTerritory(std::string country);
	void createBorder(std::string border);
};