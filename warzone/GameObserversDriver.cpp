#include "GameObserversDriver.h"
#include "GameObservers.h"
#include <vector>


int GameObserversDriver::main() {

	PhaseObserver* phaseObserver = new PhaseObserver();

	StatsObserver* gameStatisticsObserver = new StatsObserver();

	PhaseObservable* subject = new PhaseObservable();

	subject->attach(phaseObserver);

	subject->notify("PLayer 1: Phase 2");

	return 0;
}

