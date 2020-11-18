#include "GameObserversDriver.h"
#include "GameObservers.h"
#include <vector>


int GameObserversDriver::main() {

	PhaseObserver* phaseObserver = new PhaseObserver();

	StatsObserver* gameStatisticsObserver = new StatsObserver();

	Observable* subject = new Observable(); 

	subject->attach(phaseObserver);
	subject->attach(gameStatisticsObserver);

	subject->notify();

	subject->detach(gameStatisticsObserver);
	subject->notify();

	return 0;
}

