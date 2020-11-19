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
	std::cout << "\n\n\n\n\n\n\n\n\n";
}

void PhaseObserver::update(std::string output){
	std::cout << output;
	
}

StatsObserver::StatsObserver() {
	std::cout << "Hello, I am the stats observer\n";
}

StatsObserver::~StatsObserver() {

}

void StatsObserver::update() {
	std::cout << "\n\n\n\n\n\n\n\n\n";
}

void StatsObserver::update(std::string output){
	std::cout << output;
}



PhaseObservable::PhaseObservable() {
	this->myPhaseObservers = new std::list<PhaseObserver*>();
}

PhaseObservable::~PhaseObservable() {
	delete myPhaseObservers;
}

void PhaseObservable::attach(PhaseObserver* observer){
	this->myPhaseObservers->push_back(observer);
}

void PhaseObservable::detach(PhaseObserver* observer){
	this->myPhaseObservers->remove(observer);
}

void PhaseObservable::notify(std::string textToPrint) {
	std::list<PhaseObserver*>::iterator it = myPhaseObservers->begin();
	for (; it != myPhaseObservers->end(); ++it) {
		(*it)->update(textToPrint);
	}
}


StatsObservable::StatsObservable() {
	this->myStatsObservers = new std::list<StatsObserver*>();
}

StatsObservable::~StatsObservable() {
	delete myStatsObservers;
}

void StatsObservable::attach(StatsObserver* observer){
	this->myStatsObservers->push_back(observer);
}

void StatsObservable::detach(StatsObserver* observer){
	this->myStatsObservers->remove(observer);
}

void StatsObservable::notify(std::string textToPrint){
	std::list<StatsObserver*>::iterator it = myStatsObservers->begin();
	for (; it != myStatsObservers->end(); ++it) {
		(*it)->update(textToPrint);
	}
}
