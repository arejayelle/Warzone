#include "MapLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>


// MapLoader default constructor
MapLoader::MapLoader() {
	fileName = std::string();
}

//MapLoader Copy Constructor
MapLoader::MapLoader(MapLoader* mapL)
{
	this->fileName = mapL->fileName;
}

//MapLoader Constructor
MapLoader::MapLoader(std::string fileName)
{
	this->fileName = fileName;
}

//MapLoader Destructor
MapLoader::~MapLoader() { }

//Assignment operator
MapLoader* MapLoader::operator=(const MapLoader& mapLoader)
{
	return new MapLoader(mapLoader);
}


//Stream insertion operator
std::ostream& operator<<(std::ostream& out, const MapLoader& mapLoader)
{
	std::string fileName = (std::string)mapLoader.fileName;
	out << fileName;
	return out;
}

bool MapLoader::validateMapFormatML() 
{
	std::string myLine;
	bool valideMap = true;

	int numberOfValidParts = 0;

	std::cout << "[DOMINATION] Loading file: " << fileName << std::endl;

	// Read from file
	std::ifstream myReadFile(fileName);

	if (!myReadFile) {
		std::cerr << "Could not open file\n";
		return false;
	}

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(myReadFile, myLine)) {

		//Check continents
		if (myLine == "[continents]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are continents
			while (myLine != "[countries]" && !myLine.empty()) {
				//Check if the continent is good, else exit
				if (checkContinents(myLine)) {
					getline(myReadFile, myLine);
				}
				else {
					valideMap = false;
					throw std::string("Continent not valid");
				}
			}
			//Confirm that the continent part is good
			++ numberOfValidParts;
		}

		//Check territory/Countries
		if (myLine == "[countries]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are territory
			while (myLine != "[borders]" && !myLine.empty()) {
				//Check if the territory is good, else exit
				if (checkTerritory(myLine)) {
					getline(myReadFile, myLine);
				}
				else {
					valideMap = false;
					throw std::string("Territory not valid");
				}
			}
			//Confirm that the territory part is good
			++ numberOfValidParts;
		}

		//Check borders
		if (myLine == "[borders]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are borders
			while (!myLine.empty()) {
				//Check if the borders is good, else exit
				if (checkBorders(myLine)) {
					getline(myReadFile, myLine);
				}
				else {
					valideMap = false;
					throw std::string("Borders not valid");
				}
			}
			//Confirm that the borders part is good
			++ numberOfValidParts;
		}
	}

	//Check if all 3 components are valid
	if (valideMap && numberOfValidParts == 3) {
		std::cout << "Map is valid.\n\n";
		// Close the file
		myReadFile.close();
		return true;
	}
	else {
		std::cout << "Not a valid Domination map.\n";
		// Close the file
		myReadFile.close();
		return false;
	}
}

Map* MapLoader::convertFileToMap()
{
	Map* map = new Map();
	std::string myLine;

	// Read from file
	std::ifstream myReadFile(fileName);

	if (!myReadFile) {
		std::cerr << "Could not open file\n";
		return nullptr;
	}

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(myReadFile, myLine)) {

		//Create the continents
		if (myLine == "[continents]") {
			getline(myReadFile, myLine);
			
			//Loop all the lines that are continents
			while (myLine != "[countries]" && !myLine.empty()) {
				//Call the createContinent method which returns a Continent* and then adds it to the map
				map->addContinent(createContinent(myLine));
				getline(myReadFile, myLine);
			}
		}

		//Create the territories
		if (myLine == "[countries]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are territory
			while (myLine != "[borders]" && !myLine.empty()) {
				//Call the createTerritory method which returns a Territory* and then adds it to the map
				map->addTerritory(createTerritory(myLine, map));
				getline(myReadFile, myLine);
			}
		}

		//Check borders
		if (myLine == "[borders]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are borders
			while (!myLine.empty()) {
				//Call the createBorder method which returns nothing. It adds to the map in the method, as it requires an id and a vector of territory
				createBorder(myLine, map);
				getline(myReadFile, myLine);
			}
		}
	}

	return map;
}

//Verify if the continent is good
bool MapLoader::checkContinents(std::string line) 
{
	//Counts the number of inputs in the line
	size_t numberOfInputs = line.empty() || line.back() == ' ' ? 0 : 1;
	for (size_t s = line.size(); s > 0; --s)
		if (line[s] == ' ' && line[s - 1] != ' ') ++numberOfInputs;

	//Check if its not a good line or an empty line
	if (!(numberOfInputs == 3 || numberOfInputs == 0)) {
		return false;
	}
	else {
		return true;
	}	
}

//Verify if the territory is good
bool MapLoader::checkTerritory(std::string line)
{
	//Counts the number of inputs in the line
	size_t numberOfInputs = line.empty() || line.back() == ' ' ? 0 : 1;
	for (size_t s = line.size(); s > 0; --s)
		if (line[s] == ' ' && line[s - 1] != ' ') ++numberOfInputs;

	//Check if its not a good line or an empty line
	if (!(numberOfInputs == 5 || numberOfInputs == 0)) {
		return false;
	}
	else {
		return true;
	}
}

//Verify if the Borders is good
bool MapLoader::checkBorders(std::string line)
{
	//Counts the number of inputs in the line
	size_t numberOfInputs = line.empty() || line.back() == ' ' ? 0 : 1;
	for (size_t s = line.size(); s > 0; --s)
		if (line[s] == ' ' && line[s - 1] != ' ') ++numberOfInputs;

	//Check if its not a good line
	if (numberOfInputs < 2) {
		return false;
	}
	else {
		return true;
	}
}

Continent* MapLoader::createContinent(std::string continent)
{
	//Declare variables that will be used to store the calues from ss
	std::string name;
	std::string colour;
	unsigned int value;

	//Put each input into the right variable. The syntax is always the same, thus we can do that
	std::stringstream ss(continent);
	ss >> name;
	ss >> value;
	ss >> colour;
	ss.clear();

	Continent* myContinent = new Continent(name, colour, value);
	return myContinent;
}

Territory* MapLoader::createTerritory(std::string territory, Map* map)
{
	// Declare variables that will be used to store the calues from ss
	unsigned int territoryId;
	std::string name;
	unsigned int continentNumber;
	Continent* continent;
	unsigned int x;
	unsigned int y;

	//Put each input into the right variable. The syntax is always the same, thus we can do that
	std::stringstream ss(territory);
	ss >> territoryId;
	ss >> name;
	ss >> continentNumber;
	ss >> x;
	ss >> y;

	ss.clear();
	
	continent = map->getContinent(--continentNumber);

	Territory* myTerritory = new Territory(name, continent, x, y);

	return myTerritory;
}

void MapLoader::createBorder(std::string border, Map* map)
{
	//Declare variables that will be used to store the values from ss
	unsigned int territoryNumber;
	unsigned int currentTerritoryId;
	std::vector<Territory*> neighbors;
	Territory* territory;

	//Store the current border id, which is the first input
	std::stringstream ss(border);
	ss >> currentTerritoryId;

	//Loop trought all the borders, 
	while (ss >> territoryNumber) {
		territory = map->getTerritory(--territoryNumber);
		neighbors.push_back(territory);
	}

	//Add the border to the map
	map->addBorder(--currentTerritoryId, &neighbors);
}

ConquestFileReader::ConquestFileReader(ConquestFileReader* mapL)
{
	this->fileName = std::string(mapL->fileName);
}

ConquestFileReader::ConquestFileReader(std::string fileName){
	this->fileName = std::string(fileName);
}

ConquestFileReader::~ConquestFileReader() { }

ConquestFileReader& ConquestFileReader::operator=(const ConquestFileReader& reader)
{
	this->fileName = reader.fileName;
	return *this;
}

bool ConquestFileReader::validateMapFormatCQ()
{
	std::string myLine;
	bool valideMap = true;

	int numberOfValidParts = 0;

	std::cout << "[CONQUEST] Loading file: " << fileName << std::endl;

	// Read from file
	std::ifstream myReadFile(fileName);

	if (!myReadFile) {
		std::cerr << "Could not open file\n";
		return false;
	}

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(myReadFile, myLine)) {

		//Check continents
		if (myLine == "[Continents]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are continents
			while (myLine != "[Territories]" && !myLine.empty()) {
				//Check if the continent is good, else exit
				if (checkContinents(myLine)) {
					getline(myReadFile, myLine);
				}
				else {
					valideMap = false;
					throw std::string("Continent not valid");
				}
			}
			//Confirm that the continent part is good
			++ numberOfValidParts;
		}

		//Check territory/Countries
		if (myLine == "[Territories]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are territory
			while (myLine != "[borders]" && !myLine.empty()) {
				//Check if the territory is good, else exit
				if (checkTerritory(myLine)) {
					getline(myReadFile, myLine);
				}
				else {
					valideMap = false;
					std::cout << "Territory not valid";
					return false;
				}
			}
			//Confirm that the territory part is good
			++ numberOfValidParts;
		}
	}

	//Check if all 3 components are valid
	if (valideMap && numberOfValidParts == 2) {
		std::cout << "Map is valid.\n\n";
		// Close the file
		myReadFile.close();
		return true;
	}
	else {
		std::cout << "Not a valid Conquest map.\n";
		// Close the file
		myReadFile.close();
		return false;
	}
}

Map* ConquestFileReader::convertFileToMap()
{
	Map* map = new Map();
	std::string myLine;

	// Read from file
	std::ifstream myReadFile(fileName);

	if (!myReadFile) {
		std::cerr << "Could not open file\n";
		return nullptr;
	}

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(myReadFile, myLine)) {

		//Create the continents
		if (myLine == "[Continents]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are continents
			while (myLine != "[Territories]" && !myLine.empty()) {
				//Call the createContinent method which returns a Continent* and then adds it to the map
				map->addContinent(createContinent(myLine));
				getline(myReadFile, myLine);
			}
		}

		//Create the territories
		if (myLine == "[Territories]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are territory
			while (!myReadFile.eof()) {
				if (!myLine.empty()) {
					//Call the createTerritory method which returns a Territory* and then adds it to the map
					map->addTerritory(createTerritory(myLine, map));
					
				}
				getline(myReadFile, myLine);
			}

		}
	}
	
	myReadFile.clear();
	myReadFile.seekg(0, myReadFile.beg);

	//Call method to rereead the file
	std::ifstream myReadFile2(fileName);

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(myReadFile, myLine)) {
		//Create the territories
		if (myLine == "[Territories]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are territory
			while (!myReadFile.eof()) {
				if (!myLine.empty()) {
					//Call the createTerritory method which returns a Territory* and then adds it to the map
					createBorder(myLine, map);
				}
				getline(myReadFile, myLine);
			}

		}
	}
	myReadFile.close();
	return map;
}

bool ConquestFileReader::checkContinents(std::string line)
{
	//Check if theres an = sign and the last char is a digit
	if (line.find('=') != -1 && isdigit(line.back())) 
	{
		return true;
	}
	else {
		return false;
	}
}

//Check if the format of the territory is fine
bool ConquestFileReader::checkTerritory(std::string line)
{
	std::stringstream ss(line);
	std::vector<std::string> result;

	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ',');
		result.push_back(substr);
	}
	ss.clear();

	if (!isdigit(result.at(1).back()) || !isdigit(result.at(2).back())) {

		return false;
	}

	if (result.size() >= 5 && result.size() <= 14) {
		return true;
	}
	else {
		return false;
	}
}

Continent* ConquestFileReader::createContinent(std::string continent)
{
	//Declare variables that will be used to store the calues from ss
	std::string name;
	std::string colour = "White";
	unsigned int value = 0;

	
	name = continent.substr(0, continent.find('='));
	value = continent.back() - '0'; //NOICE
	Continent* myContinent = new Continent(name, colour, value);
	return myContinent;
}

Territory* ConquestFileReader::createTerritory(std::string territory, Map* map)
{
	// Declare variables that will be used to store the calues from ss
	std::string name;
	Continent* continent;
	unsigned int x;
	unsigned int y;

	std::stringstream ss(territory);
	std::vector<std::string> result;

	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ',');
		result.push_back(substr);
	}
	ss.clear();

	//Put each input into the right variable. The syntax is always the same, thus we can do that
	name = result.at(0);
	x = std::stoul(result.at(1));
	y = std::stoul(result.at(2));
	continent = map->getContinent(result.at(3));

	Territory* myTerritory = new Territory(name, continent, x, y);

	return myTerritory;
}

void ConquestFileReader::createBorder(std::string border, Map* map){
	// Declare variables that will be used to store the calues from ss
	std::string name;
	std::vector<Territory*> neighbors;
	Territory* territory;

	std::stringstream ss(border);
	std::vector<std::string> result;

	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ',');
		result.push_back(substr);
	}
	ss.clear();

	name = result.at(0);

	//Find the pointer to territory
	territory = map->getTerritory(name);

	for (int i = 4; i < result.size(); i++) {
		neighbors.push_back(map->getTerritory(result.at(i)));
	}

	int index = map->getTerritoryID(name);

	//Add the border to the map
	map->addBorder(index, &neighbors);
}

// Copy constructor.
ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReaderAdapter* adapter)
{
	this->fileName = std::string(adapter->fileName);
	this->conquestMapLoader = new ConquestFileReader(adapter->conquestMapLoader);
}

// Param constructor.
ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader* cfr) : MapLoader(fileName), conquestMapLoader(cfr) { }

// Destructor.
ConquestFileReaderAdapter::~ConquestFileReaderAdapter()
{
	delete conquestMapLoader;
}

// Assignment operator.
ConquestFileReaderAdapter& ConquestFileReaderAdapter::operator=(const ConquestFileReaderAdapter& other)
{
	this->fileName = std::string(other.fileName);
	this->conquestMapLoader = new ConquestFileReader("");
	return *this;
}

std::ostream& operator<<(std::ostream& out, const ConquestFileReader& reader)
{
	out << "File name is " << reader.fileName;
	return out;
}

// Stream insertion operator.
std::ostream& operator<<(std::ostream& out, const ConquestFileReaderAdapter& reader)
{
	out << "File name is " << reader.fileName;
	return out;
}

bool ConquestFileReaderAdapter::validateMapFormatML()
{
	return conquestMapLoader->validateMapFormatCQ();
}

Map* ConquestFileReaderAdapter::convertFileToMap()
{
	return conquestMapLoader->convertFileToMap();
}
