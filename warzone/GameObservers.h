#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "Player.h"

class Player;


class Observer {
public:
	~Observer();
	virtual void update() = 0;
protected:
	Observer();
};

class Observable {
public:
	Observable();
	~Observable();
	virtual void attach(Observer* observer);
	virtual void detach(Observer* observer);
	virtual void notify();
private:
	std::list<Observer*>* myObservers;
};


class PhaseObserver: public Observer {
public:
	PhaseObserver();
	~PhaseObserver();
	void update() override;
	void update(std::string output);
};

class StatsObserver : public Observer {
public:
	StatsObserver();
	~StatsObserver();
	void update() override;
	void update(std::string output);
};

class PhaseObservable : public Observable {
public:
	PhaseObservable();
	~PhaseObservable();
	void attach(PhaseObserver* observer);
	void detach(PhaseObserver* observer);
	void notify(std::string textToPrint);
private:
	std::list<PhaseObserver*>* myPhaseObservers;
};

class StatsObservable : public Observable {
public:
	StatsObservable();
	~StatsObservable();
	void attach(StatsObserver* observer);
	void detach(StatsObserver* observer);
	void notify(std::string textToPrint);
private:
	std::list<StatsObserver*>* myStatsObservers;
};