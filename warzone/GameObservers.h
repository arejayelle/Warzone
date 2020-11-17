#pragma once
#include <iostream>
#include <vector>


class Observer {
public:
	~Observer();
	virtual void update() = 0;
protected:
	Observer();
};

class Subject {
public:
	Subject();
	~Subject();
	virtual void attach(Observer* observer);
	virtual void detach(Observer* observer);
	virtual void notify();
protected:
	std::vector<Observer*> *myObservers;
};

class ConcreteObserver {
public:
	ConcreteObserver();
	~ConcreteObserver();
	void update();
};