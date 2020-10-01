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

private:
	std::string* fileName;
	bool checkContinents(std::string continent);
	bool checkCountries(std::string country);
	bool checkBorders(std::string border);
};