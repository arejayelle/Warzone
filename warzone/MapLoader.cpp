#include "MapLoader.h"
#include <fstream>
#include <iostream>



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

}