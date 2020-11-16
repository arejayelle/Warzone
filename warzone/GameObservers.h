#pragma once
#include <iostream>
#include <vector>


class Observer {
public:
	virtual ~Observer() {};
	virtual void update();
};

class Subject {
public:
	virtual ~Subject() {};
	virtual void attach(Observer *observer);
	virtual void detach(Observer *observer);
	virtual void notify();
protected:
	std::vector<Observer*> myObservers;
};