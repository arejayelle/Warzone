#pragma once
#include "MapLoader.h"

/*int main() {
	//Valide Map
	MapLoader* mapL = new MapLoader("bigeurope.map");
	mapL->validateMapFormat();
	Map* myMap = mapL->convertFileToMap();
	myMap->validate();

	//Wrong formatted map, continent not valid
	MapLoader* mapL = new MapLoader("bigeuropewrong.map");
	mapL->validateMapFormat();
	Map* myMap = mapL->convertFileToMap();
	myMap->validate();

	//Random text, territory format should be not valid
	MapLoader* mapL = new MapLoader("randomText.txt");
	mapL->validateMapFormat();
	Map* myMap = mapL->convertFileToMap();
	myMap->validate();
}*/