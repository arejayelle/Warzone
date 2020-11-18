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
protected:
	std::list<Observer*>* myObservers;
};

class PhaseObserver: public Observer {
public:
	PhaseObserver();
	//PhaseObserver(GameEngine* ge);
	~PhaseObserver();
	void update() override;
private:
	//Gameengine* _subject;
};

class StatsObserver : public Observer {
public:
	StatsObserver();
	StatsObserver(Player player);
	~StatsObserver();
	void update() override;
};