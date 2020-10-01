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
	bool checkContinents();
	bool checkCountries();
	bool checkBorders();
};