#include "MapLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>


MapLoader::MapLoader() {
	this->fileName = NULL;
}

MapLoader::MapLoader(std::string fileName) {
	this->fileName = new std::string(fileName);
}

MapLoader::~MapLoader() {
	delete	fileName;
}


bool MapLoader::validateMap() {
	std::string myLine;
	bool valideMap = true;

	int* numberOfValidComponent = new int();

	std::cout << "Loading file:  " << *fileName << std::endl;

	// Read from file
	std::ifstream myReadFile(*fileName);

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(myReadFile, myLine)) {

		if (myLine == "[continents]") {
			std::cout << "[continents]\n";
			getline(myReadFile, myLine);
			while (myLine != "[countries]") {
				if (checkContinents(myLine)) {
					getline(myReadFile, myLine);
				}
				else {
					valideMap = false;
					exit(1);
				}
			}
			++* numberOfValidComponent;
		}

		if (myLine == "[countries]") {
			std::cout << "[countries]\n";
			getline(myReadFile, myLine);
			while (myLine != "[borders]") {
				if (checkCountries(myLine)) {
					getline(myReadFile, myLine);
				}
				else {
					valideMap = false;
					exit(1);
				}
			}
			++* numberOfValidComponent;
		}

		if (myLine == "[borders]") {
			std::cout << "[borders]\n";
			getline(myReadFile, myLine);
			while (!myLine.empty()) {
				if (checkBorders(myLine)) {
					getline(myReadFile, myLine);
				}
				else {
					valideMap = false;
					exit(1);
				}
			}
			++* numberOfValidComponent;
		}

		
	}

	if (valideMap && *numberOfValidComponent == 3) {
		std::cout << "Map is valid.\n";
		// Close the file
		myReadFile.close();
		delete(numberOfValidComponent);
		return true;
	}
	else {
		std::cout << "Map is not valid, missing some components.\n";
		// Close the file
		myReadFile.close();
		delete(numberOfValidComponent);
		return false;
	}

	
}


bool MapLoader::checkContinents(std::string line) {

	size_t numberOfWords = line.empty() || line.back() == ' ' ? 0 : 1;
	for (size_t s = line.size(); s > 0; --s)
		if (line[s] == ' ' && line[s - 1] != ' ') ++numberOfWords;

	if (!(numberOfWords == 3 || numberOfWords == 0)) {
		std::cout << "Continents format is not Valid.";
		return false;
	}
	else {
		std::cout << line << "\n";
		return true;
	}	
}

bool MapLoader::checkCountries(std::string line) {
	size_t numberOfWords = line.empty() || line.back() == ' ' ? 0 : 1;
	for (size_t s = line.size(); s > 0; --s)
		if (line[s] == ' ' && line[s - 1] != ' ') ++numberOfWords;

	if (!(numberOfWords == 5 || numberOfWords == 0)) {
		std::cout << "Countries format is not Valid.";
		return false;
	}
	else {
		std::cout << line << "\n";
		return true;
	}
}

bool MapLoader::checkBorders(std::string line) {
	size_t numberOfWords = line.empty() || line.back() == ' ' ? 0 : 1;
	for (size_t s = line.size(); s > 0; --s)
		if (line[s] == ' ' && line[s - 1] != ' ') ++numberOfWords;

	if (numberOfWords < 2) {
		std::cout << "Borders format is not Valid.";
		return false;
	}
	else {
		std::cout << line << "\n";
		return true;
	}
}