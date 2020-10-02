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
			std::cout << "[continents]\n";
			getline(myReadFile, myLine);

			//Loop all the lines that are continents
			while (myLine != "[countries]") {
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

		//Check territory
		if (myLine == "[countries]") {
			std::cout << "[countries]\n";
			getline(myReadFile, myLine);

			//Loop all the lines that are territory
			while (myLine != "[borders]") {
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
			std::cout << "[borders]\n";
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
		std::cout << "Map is valid.\n";
		// Close the file
		myReadFile.close();
		delete(numberOfValidParts);
		return true;
	}
	else {
		std::cout << "Map is not valid, missing some components.\n";
		// Close the file
		myReadFile.close();
		delete(numberOfValidParts);
		return false;
	}

	
}

Map* MapLoader::convertFileToMap()
{
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

		//Check continents
		if (myLine == "[continents]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are continents
			while (myLine != "[countries]") {
				//Check if the continent is good, else exit
				createContinent(myLine);
				getline(myReadFile, myLine);
			}
		}

		//Check territory
		if (myLine == "[countries]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are territory
			while (myLine != "[borders]") {
				//Check if the territory is good, else exit
				createTerritory(myLine);
				getline(myReadFile, myLine);
			}
		}

		//Check borders
		if (myLine == "[borders]") {
			getline(myReadFile, myLine);

			//Loop all the lines that are borders
			while (!myLine.empty()) {
				//Check if the borders is good, else exit
				createBorder(myLine);
				getline(myReadFile, myLine);
			}
		}


	}

	return nullptr;
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
		std::cout << "Continents format is not Valid.";
		return false;
	}
	else {
		std::cout << line << "\n";
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
		std::cout << "Territory format is not Valid.";
		return false;
	}
	else {
		std::cout << line << "\n";
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
		std::cout << "Borders format is not Valid.";
		return false;
	}
	else {
		std::cout << line << "\n";
		return true;
	}
}

void MapLoader::createContinent(std::string continent)
{
}

void MapLoader::createTerritory(std::string country)
{
}

void MapLoader::createBorder(std::string border)
{
}
