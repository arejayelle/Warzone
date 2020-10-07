#include "Orders.h"

Order::Order() {
	this->player = NULL;
}

Order::Order(Player* player) {
	this->player = player;
}

Order::Order(Order* other) {
	this->player = other->player
}

Order::~Order() {
	delete player;
}

bool Order::validate() {
	if (this->player != NULL) {
		cout << "Fuck"
		return true;
	} 
	return false;
}

bool Order::execute() {
	if!(this->validate()) {
		cout << "Cannot execute order because it is invalid.";
		return false;
	}

	cout << "Order executed."
}

ostream& operator<<(ostream& outStream, const Order& order) {
	// TODO: insert return statement here
}


