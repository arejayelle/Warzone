#pragma once
#include <iostream>
#include <vector>
#include <list>


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
protected:
	std::list<Observer*>* myObservers;
};

class PhaseObserver: public Observer {
public:
	PhaseObserver();
	~PhaseObserver();
	void update() override;
};

class StatsObserver : public Observer {
public:
	StatsObserver();
	~StatsObserver();
	void update() override;
};