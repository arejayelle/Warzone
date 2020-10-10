#pragma once
#include "MapLoader.h"

/*int main() {
	//Valide Map
	MapLoader* mapL = new MapLoader("bigeurope.map");
	mapL->validateMapFormat();
	Map* myMap = mapL->convertFileToMap();
	myMap->validate();

	//Wrong formatted map, continent not valid
	MapLoader* mapL2 = new MapLoader("bigeuropewrong.map");
	mapL2->validateMapFormat();
	Map* myMap2 = mapL2->convertFileToMap();
	myMap2->validate();

	//Random text, territory format should be not valid
	MapLoader* mapL3 = new MapLoader("randomText.txt");
	mapL3->validateMapFormat();
	Map* myMap3 = mapL3->convertFileToMap();
	myMap3->validate();


}*/