#pragma once
#include "GameEngine.h"
#include "MapDriver.h"
namespace GameLoopDriver
{
	int main();
	void reinforcements(GameEngine* gameEngine);
	void issueOrdersPhase(GameEngine* gameEngine);
	void executeOrdersPhase(GameEngine* gameEngine);
};

