#include "GameEngineDriver.h"

int GameEngineDriver::main()
{
	GameEngine* Game = new GameEngine();
	Game->startUpPhase();
	Game->~GameEngine();

	return 0;

}
