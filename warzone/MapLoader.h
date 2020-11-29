#pragma once
#include "Map.h"
#include <string>
#include <vector>
#include <iostream>

class MapLoader { // Target; reads Domination map files.
public:
	MapLoader();
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

class ConquestFileReader { // Adaptee; reads Conquest map files.
public:
	ConquestFileReader(ConquestFileReader* mapL);
	ConquestFileReader(std::string fileName);
	~ConquestFileReader();
	ConquestFileReader* operator= (const ConquestFileReader& reader);
	friend std::ostream& operator<< (std::ostream& out, const ConquestFileReader& reader);
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

class ConquestFileReaderAdapter : public MapLoader { // Adapter; adapts (target) Domination map reading to (adaptee) Conquest map reading.
public:
	ConquestFileReaderAdapter(ConquestFileReaderAdapter* adapter);
	ConquestFileReaderAdapter(std::string fileName, ConquestFileReader* cfr);
	~ConquestFileReaderAdapter();
	ConquestFileReaderAdapter& operator=(const ConquestFileReaderAdapter& other);
	friend std::ostream& operator<<(std::ostream& out, const ConquestFileReaderAdapter& reader);
	//void conquestToDomination(std::string fileName);
	bool validateMapFormat();
	Map* convertFileToMap();
private:
	std::string fileName;
	ConquestFileReader* conquestMapLoader;
};
