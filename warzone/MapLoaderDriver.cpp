#pragma once
#include "MapLoader.h"
#include <fstream>
#include <iostream>

int main() {
	MapLoader* mapL = new MapLoader("bigeuropewrong.map");
	mapL->validateMap();
	Map* myMap = mapL->convertFileToMap();
	myMap->validate();
}