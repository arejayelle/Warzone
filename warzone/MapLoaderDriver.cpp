#pragma once
#include "MapLoader.h"
#include "MapLoaderDriver.h"

int MapLoaderDriver::main() {

	/*MapLoader* mapL = new MapLoader("bigeurope.map");
	mapL->validateMapFormatML();*/

	ConquestFileReader* conq = new ConquestFileReader("Africa.map");
	//ConquestFileReader* conq = new ConquestFileReader("bigeurope.map");
	conq->validateMapFormatCQ();
	Map* myMap = conq->convertFileToMap();
	myMap->validate();
	cout << "MAP is valid";

	/*ConquestFileReaderAdapter* adpt = new ConquestFileReaderAdapter(conq);
	adpt->validateMapFormatML();*/

	//Valide Map
	/*MapLoader* mapL = new MapLoader("bigeurope.map");
	mapL->validateMapFormat();
	Map* myMap = mapL->convertFileToMap();
	myMap->validate();

	//Wrong formatted map, continent not valid
	MapLoader* mapL2 = new MapLoader("bigeuropewrong.map");
	try {
		mapL2->validateMapFormat();
	}
	catch (std::string exception) {
		std::cout << "Error occurred, as expected, when loading bigeuropewrong.map: " << exception << std::endl;
	}
	
	//Random text, territory format should be not valid
	MapLoader* mapL3 = new MapLoader("randomText.txt");
	try {
		mapL3->validateMapFormat();
	}
	catch (std::string exception) {
		std::cout << "Error occurred, as expected, when loading randomText.txt: " << exception << std::endl;
	}*/

	return 0;
}