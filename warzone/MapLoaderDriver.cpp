#pragma once
#include "MapLoader.h"
#include "MapLoaderDriver.h"

int MapLoaderDriver::main() {
	cout << "Using original reader to read Domination map files:" << endl;

	MapLoader* mapL = new MapLoader("bigeurope.map");
	if (mapL->validateMapFormatML()) {
		Map* map1 = mapL->convertFileToMap();
		map1->validate();
	}
	
	cout << "Using Conquest file reader to read map files:" << endl;

	ConquestFileReader* conq = new ConquestFileReader("Africa.map");
	if (conq->validateMapFormatCQ()) {
		Map* map2 = conq->convertFileToMap();
		map2->validate();
	}

	cout << "Using Conquest adapter to read map files:" << endl;

	ConquestFileReaderAdapter* adpt = new ConquestFileReaderAdapter(conq);
	if (adpt->validateMapFormatML()) {
		Map* map3 = adpt->convertFileToMap();
		map3->validate();
	}

	return 0;
}