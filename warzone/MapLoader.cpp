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
					break;
				}
			}
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
					break;
				}
			}
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
					break;
				}
			}
		}

		
	}

	std::cout << "VALIDE?:" << valideMap << "\n";

	// Close the file
	myReadFile.close();
	return false;
}


bool MapLoader::checkContinents(std::string continent) {
	unsigned int numberOfWords = 0;
	numberOfWords = std::count(continent.cbegin(), continent.cend(), ' ') + 1;

	if (numberOfWords != 3) {
		std::cout << "WRONG LINE" << continent;
		return false;
	}
	else {
		std::cout << continent << "\n";
		return true;
	}	
}

bool MapLoader::checkCountries(std::string country) {
	unsigned int numberOfWords = 0;
	numberOfWords = std::count(country.cbegin(), country.cend(), ' ') + 1;

	if (numberOfWords != 5) {
		return false;
	}
	else {
		std::cout << country << "\n";
		return true;
	}
}

bool MapLoader::checkBorders(std::string border) {
	unsigned int numberOfWords = 0;
	numberOfWords = std::count(border.cbegin(), border.cend(), ' ') + 1;

	if (numberOfWords < 2) {
		return false;
	}
	else {
		std::cout << border << "\n";
		return true;
	}
}