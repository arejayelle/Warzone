#include "Main.h"


int main()
{
	srand((unsigned int)time(NULL));

	return MapLoaderDriver::main();
	// return OrdersDriver::main();
	// return GameEngineDriver::main();
	// return GameObserversDriver::main();
	// return GameLoopDriver::main();
	GameEngine* engine = new GameEngine();
	engine->startUpPhase();
	engine->mainGameLoop();
}
