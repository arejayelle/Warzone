#include "GameObservers.h"



Observer::Observer() {

}

Observer::~Observer() {

}

void Observer::update() {

}

Observable::Observable() {
	this->myObservers = new std::list<Observer*>();
}

//Destructor for Subject
Observable::~Observable() {
	delete myObservers;
}


void Observable::attach(Observer* observer){
	this->myObservers->push_back(observer);
}

void Observable::detach(Observer* observer){
	this->myObservers->remove(observer);
}

void Observable::notify(){
	std::list<Observer*>::iterator it = myObservers->begin();
	for (; it != myObservers->end(); ++it) {
		(*it)->update();
	}
}

PhaseObserver::PhaseObserver(){
	std::cout << "Hello, I am the phase observer\n";
}

PhaseObserver::~PhaseObserver(){

}

void PhaseObserver::update(){
	std::cout << "I have been notified\n";
	
}

StatsObserver::StatsObserver() {
	std::cout << "Hello, I am the stats observer\n";
}

StatsObserver::~StatsObserver() {

}

void StatsObserver::update() {

}
