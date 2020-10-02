#pragma once
#include "MapLoader.h"
#include <fstream>
#include <iostream>

int main() {
	MapLoader* mapL = new MapLoader("bigeurope.map");
	mapL->validateMap();
	mapL->convertFileToMap();
}