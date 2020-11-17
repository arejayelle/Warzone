#include "GameObservers.h"



Observer::Observer() {

}

Observer::~Observer() {

}

void Observer::update() {

}



Subject::Subject() {
	this->myObservers = new std::vector<Observer*>();
}

//Destructor for Subject
Subject::~Subject() {
	// Delete each pointer in myObservers.
	for (size_t i = 0; i < myObservers->size(); i++) {
		delete myObservers->at(i);
	}
}


void Subject::attach(Observer* observer){
	this->myObservers->push_back(observer);
}

void Subject::detach(Observer* observer){
	std::vector<Observer*>::iterator it;

	it = find(myObservers->begin(), myObservers->end(), observer);
	if (it != myObservers->end()) {
		this->myObservers->erase(it);
	}
	else {
		std::cout << "Element not found in myObservers\n";
	}	
}

void Subject::notify(){
	std::vector<Observer*>::iterator it;
	for (this->myObservers->begin(); it != myObservers->end(); ++it) {
		(*it)->update();
	}
}

ConcreteObserver::ConcreteObserver(){
}

ConcreteObserver::~ConcreteObserver(){
}

void ConcreteObserver::update(){
}
