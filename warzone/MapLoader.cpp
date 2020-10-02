#include "MapLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>


MapLoader::MapLoader()
{
	this->fileName = NULL;
}

MapLoader::MapLoader(std::string fileName)
{
	this->fileName = new std::string(fileName);
}

MapLoader::~MapLoader() 
{
	delete	fileName;
}


bool MapLoader::validateMap() 
{
	std::string myLine;
	bool valideMap = true;

	int* numberOfValidParts = new int();

	std::cout << "Loading file:  " << *fileName << std::endl;

	// Read from file
	std::ifstream myReadFile(*fileName);

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
					exit(1);
				}
			}
			//Confirm that the continent part is good
			++* numberOfValidParts;
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
					exit(1);
				}
			}
			//Confirm that the territory part is good
			++* numberOfValidParts;
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
					exit(1);
				}
			}
			//Confirm that the borders part is good
			++* numberOfValidParts;
		}

		
	}

	//Check if all 3 components are valid
	if (valideMap && *numberOfValidParts == 3) {
		std::cout << "Map is valid.\n\n";
		// Close the file
		myReadFile.close();
		delete(numberOfValidParts);
		return true;
	}
	else {
		std::cout << "Map is not valid, missing either the continents, countries or borders. Please verify the syntax is correct\n";
		// Close the file
		myReadFile.close();
		delete(numberOfValidParts);
		return false;
	}

	
}

Map* MapLoader::convertFileToMap()
{
	Map* map = new Map();
	std::string myLine;
	std::cout << "Loading file:  " << *fileName << std::endl;


	// Read from file
	std::ifstream myReadFile(*fileName);

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

	//Counts the number of words in the line
	size_t numberOfWords = line.empty() || line.back() == ' ' ? 0 : 1;
	for (size_t s = line.size(); s > 0; --s)
		if (line[s] == ' ' && line[s - 1] != ' ') ++numberOfWords;

	//Check if its not a good line or an empty line
	if (!(numberOfWords == 3 || numberOfWords == 0)) {
		std::cout << "Continents format is not Valid.\n";
		return false;
	}
	else {
		return true;
	}	
}

//Verify if the territory is good
bool MapLoader::checkTerritory(std::string line)
{

	//Counts the number of words in the line
	size_t numberOfWords = line.empty() || line.back() == ' ' ? 0 : 1;
	for (size_t s = line.size(); s > 0; --s)
		if (line[s] == ' ' && line[s - 1] != ' ') ++numberOfWords;

	//Check if its not a good line or an empty line
	if (!(numberOfWords == 5 || numberOfWords == 0)) {
		std::cout << "Territory format is not Valid.\n";
		return false;
	}
	else {
		return true;
	}
}

//Verify if the Borders is good
bool MapLoader::checkBorders(std::string line)
{

	//Counts the number of words in the line
	size_t numberOfWords = line.empty() || line.back() == ' ' ? 0 : 1;
	for (size_t s = line.size(); s > 0; --s)
		if (line[s] == ' ' && line[s - 1] != ' ') ++numberOfWords;

	//Check if its not a good line
	if (numberOfWords < 2) {
		std::cout << "Borders format is not Valid.\n";
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
	//Declare variables that will be used to store the calues from ss
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

