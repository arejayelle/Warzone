#include "Orders.h"
#include <iostream>
#include <string>
#include <sstream>


// Generic order base class.
// Default constructor.
Order::Order() {
	this->player = nullptr;
}

// Constructor which takes a pointer to a Player object.
Order::Order(Player* player) {
	this->player = player;
}

// Copy constructor taking a pointer to another Order object.
Order::Order(Order* other) {
	this->player = other->player;
}

// Destructor.
Order::~Order() { }

// This verifies that there are no problems with the order. Returns true if valid, false otherwise.
bool Order::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	} 
	return false;
}

// First uses the validate method and then executes the order and displays the status.
bool Order::execute() {
	cout << "Attempting to execute order... ";

	if(!this->validate()) {
		cout << "Cannot execute order because it is invalid." << endl;
		return false;
	}

	// TODO: Do actions once we have more details.
	cout << "Order executed." << endl;
	return true;
}

// Used to print information about the order.
string Order::toString() const {
	ostringstream strm;
	strm << "Order made by player " << this->player;
	return strm.str();
}

// Stream insertion operator, uses toString method to display order information.
ostream& operator<<(ostream &strm, const Order &o) {
	return strm << o.toString();
}

// Assignment operator which uses the class' copy constructor.
Order* Order::operator=(const Order &o) {
	return new Order(o);
}


// Deploy order subclass.
// Constructor which takes a pointer to a Player object.
DeployOrder::DeployOrder(Player* player) : Order(player) { }

// Copy constructor taking a pointer to another DeployOrder object.
DeployOrder::DeployOrder(DeployOrder* other) : Order(other) { }

// Destructor.
DeployOrder::~DeployOrder() { }

// This verifies that there are no problems with the order. Returns true if valid, false otherwise.
bool DeployOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

// First uses the validate method and then executes the order and displays the status.
bool DeployOrder::execute() {
	cout << "Attempting to execute deploy order... ";

	if (!this->validate()) {
		cout << "Cannot execute deploy order because it is invalid." << endl;
		return false;
	}

	// TODO: Do actions once we have more details.
	cout << "Deploy order executed." << endl;
	return true;
}

// Used to print information about the order.
string DeployOrder::toString() const {
	ostringstream strm;
	strm << "Deploy order made by player " << this->player;
	return strm.str();
}

// Stream insertion operator, uses toString method to display order information.
ostream& operator<<(ostream& strm, const DeployOrder& o) {
	return strm << o.toString();
}

// Assignment operator which uses the class' copy constructor.
DeployOrder* DeployOrder::operator=(const DeployOrder& o) {
	return new DeployOrder(o);
}


// Advance order subclass.
// Constructor which takes a pointer to a Player object.
AdvanceOrder::AdvanceOrder(Player* player) : Order(player) { }

// Copy constructor taking a pointer to another AdvanceOrder object.
AdvanceOrder::AdvanceOrder(AdvanceOrder* other) : Order(other) { }

// Destructor.
AdvanceOrder::~AdvanceOrder() { }

// This verifies that there are no problems with the order. Returns true if valid, false otherwise.
bool AdvanceOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

// First uses the validate method and then executes the order and displays the status.
bool AdvanceOrder::execute() {
	cout << "Attempting to execute advance order... ";

	if (!this->validate()) {
		cout << "Cannot execute advance order because it is invalid." << endl;
		return false;
	}

	// TODO: Do actions once we have more details.
	cout << "Advance order executed." << endl;
	return true;
}

// Used to print information about the order.
string AdvanceOrder::toString() const {
	ostringstream strm;
	strm << "Advance order made by player " << this->player;
	return strm.str();
}

// Stream insertion operator, uses toString method to display order information.
ostream& operator<<(ostream& strm, const AdvanceOrder& o) {
	return strm << o.toString();
}

// Assignment operator which uses the class' copy constructor.
AdvanceOrder* AdvanceOrder::operator=(const AdvanceOrder& o) {
	return new AdvanceOrder(o);
}


// BombOrder subclass.
// Constructor which takes a pointer to a Player object.
BombOrder::BombOrder(Player* player) : Order(player) { }

// Copy constructor taking a pointer to another BombOrder object.
BombOrder::BombOrder(BombOrder* other) : Order(other) { }

// Destructor.
BombOrder::~BombOrder() { }

// This verifies that there are no problems with the order. Returns true if valid, false otherwise.
bool BombOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

// First uses the validate method and then executes the order and displays the status.
bool BombOrder::execute() {
	cout << "Attempting to execute bomb order... ";

	if (!this->validate()) {
		cout << "Cannot execute bomb order because it is invalid." << endl;
		return false;
	}

	// TODO: Do actions once we have more details.
	cout << "Bomb order executed." << endl;
	return true;
}

// Used to print information about the order.
string BombOrder::toString() const {
	ostringstream strm;
	strm << "Bomb order made by player " << this->player;
	return strm.str();
}

// Stream insertion operator, uses toString method to display order information.
ostream& operator<<(ostream& strm, const BombOrder& o) {
	return strm << o.toString();
}

// Assignment operator which uses the class' copy constructor.
BombOrder* BombOrder::operator=(const BombOrder& o) {
	return new BombOrder(o);
}


// Blockade order subclass.
// Constructor which takes a pointer to a Player object.
BlockadeOrder::BlockadeOrder(Player* player) : Order(player) { }

// Copy constructor taking a pointer to another BlockadeOrder object.
BlockadeOrder::BlockadeOrder(BlockadeOrder* other) : Order(other) { }

// Destructor.
BlockadeOrder::~BlockadeOrder() { }

// This verifies that there are no problems with the order. Returns true if valid, false otherwise.
bool BlockadeOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

// First uses the validate method and then executes the order and displays the status.
bool BlockadeOrder::execute() {
	cout << "Attempting to execute blockade order... ";

	if (!this->validate()) {
		cout << "Cannot execute blockade order because it is invalid." << endl;
		return false;
	}

	// TODO: Do actions once we have more details.
	cout << "Blockade order executed." << endl;
	return true;
}

// Used to print information about the order.
string BlockadeOrder::toString() const {
	ostringstream strm;
	strm << "Blockade order made by player " << this->player;
	return strm.str();
}

// Stream insertion operator, uses toString method to display order information.
ostream& operator<<(ostream& strm, const BlockadeOrder& o) {
	return strm << o.toString();
}

// Assignment operator which uses the class' copy constructor.
BlockadeOrder* BlockadeOrder::operator=(const BlockadeOrder& o) {
	return new BlockadeOrder(o);
}


// Airlift order subclass.
// Constructor which takes a pointer to a Player object.
AirliftOrder::AirliftOrder(Player* player) : Order(player) { }

// Copy constructor taking a pointer to another AirliftOrder object.
AirliftOrder::AirliftOrder(AirliftOrder* other) : Order(other) { }

// Destructor.
AirliftOrder::~AirliftOrder() { }

// This verifies that there are no problems with the order. Returns true if valid, false otherwise.
bool AirliftOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

// First uses the validate method and then executes the order and displays the status.
bool AirliftOrder::execute() {
	cout << "Attempting to execute airlift order... ";

	if (!this->validate()) {
		cout << "Cannot execute airlift order because it is invalid." << endl;
		return false;
	}

	// TODO: Do actions once we have more details.
	cout << "Airlift order executed." << endl;
	return true;
}

// Used to print information about the order.
string AirliftOrder::toString() const {
	ostringstream strm;
	strm << "Airlift order made by player " << this->player;
	return strm.str();
}

// Stream insertion operator, uses toString method to display order information.
ostream& operator<<(ostream& strm, const AirliftOrder& o) {
	return strm << o.toString();
}

// Assignment operator which uses the class' copy constructor.
AirliftOrder* AirliftOrder::operator=(const AirliftOrder& o) {
	return new AirliftOrder(o);
}


// Negotiate order subclass.
// Constructor which takes a pointer to a Player object.
NegotiateOrder::NegotiateOrder(Player* player) : Order(player) { }

// Copy constructor taking a pointer to another NegotiateOrder object.
NegotiateOrder::NegotiateOrder(NegotiateOrder* other) : Order(other) { }

// Destructor.
NegotiateOrder::~NegotiateOrder() { }

// This verifies that there are no problems with the order. Returns true if valid, false otherwise.
bool NegotiateOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

// First uses the validate method and then executes the order and displays the status.
bool NegotiateOrder::execute() {
	cout << "Attempting to execute negotiate order... ";

	if (!this->validate()) {
		cout << "Cannot execute negotiate order because it is invalid." << endl;
		return false;
	}

	// TODO: Do actions once we have more details.
	cout << "Negotiate order executed." << endl;
	return true;
}

// Used to print information about the order.
string NegotiateOrder::toString() const {
	ostringstream strm;
	strm << "Negotiate order made by player " << this->player;
	return strm.str();
}

// Stream insertion operator, uses toString method to display order information.
ostream& operator<<(ostream& strm, const NegotiateOrder& o) {
	return strm << o.toString();
}

// Assignment operator which uses the class' copy constructor.
NegotiateOrder* NegotiateOrder::operator=(const NegotiateOrder& o) {
	return new NegotiateOrder(o);
}


// OrdersList class. Stores pointers to Order objects in a vector.
// Constructor for making an empty list.
OrdersList::OrdersList() {
	this->orders = vector<Order*>();
}

// Copy constructor to make a new orders list.
OrdersList::OrdersList(OrdersList* other) {
	// We make a new vector with pointers to new Order objects.
	vector<Order*> newOrders = vector<Order*>();
	for (int i = 0; i < other->orders.size(); i++) {
		newOrders.push_back(new Order(other->orders.at(i)));
	}
	this->orders = newOrders;
}

// Destructor, properly takes care of vector of pointers.
OrdersList::~OrdersList() {
	// Delete each pointer in orders.
	for (int i = 0; i < orders.size(); i++) {
		delete orders.at(i);
	}
}

// Returns an int representing how many orders are in the vector.
int OrdersList::size() {
	return this->orders.size();
}

// To add a new order to the list. The new order is added to the back of the list.
void OrdersList::add(Order* newOrder) {
	this->orders.push_back(newOrder);
}

// Deletes the order at the specified index. Indexes begin at 0. Returns true if successfully removed, false otherwise.
bool OrdersList::remove(int index) {
	// Verifies that the specified index is within range.
	if (index > this->orders.size() - 1 || index < 0) {
		cout << "Can't delete this order. Invalid index." << endl;
		return false;
	}

	this->orders.erase(this->orders.begin() + index);
	return true;
}

// Allows the player to rearrange orders by removing an order at oldIndex and inserting it at newIndex. Returns true if insertion is successful, otherwise false.
bool OrdersList::move(int oldIndex, int newIndex) {
	// Check if the indices make sense.
	if (oldIndex > this->orders.size() - 1 || oldIndex < 0) {
		cout << "Can't move. Invalid starting index." << endl;
		return false;
	}
	else if (newIndex > this->orders.size() - 1 || newIndex < 0) {
		cout << "Can't move. Invalid destination index." << endl;
		return false;
	}

	// Get and remove the item at oldIndex.
	Order* theOrder = this->orders.at(oldIndex);
	this->remove(oldIndex);

	// The last index may have changed after removal, if invalid just add it to the back of the list.
	if (newIndex > this->orders.size() - 1) {
		this->orders.push_back(theOrder);
		return true;
	}

	// Regular case, just insert it at the index.
	this->orders.insert(this->orders.begin() + newIndex, theOrder);
	return true;
}

// Prints all information about orders in the orders list for debugging/demonstration purposes.
void OrdersList::print() {
	cout << "List contents are:\n[";
	for (int i = 0; i < this->orders.size(); i++) {
		cout << *(this->orders.at(i)) << ", ";
	}
	cout << "]\nEnd of list contents." << endl;
}

// Attempts to execute all orders in the list. Returns true if successful, returns false if at least one order could not be executed.
bool OrdersList::executeAll() {
	bool allExecuted = true;

	// Move through orders list attempting to execute all orders. Mark allExecuted as false if we come across one that cannot execute.
	for (int i = 0; i < this->orders.size(); i++) {
		if (!this->orders.at(i)->execute()) {
			allExecuted = false;
		}
	}

	return allExecuted;
}

// Used to display information about the orders list.
ostream& operator<<(ostream& strm, const OrdersList& o) {
	return strm << "OrdersList containing " << o.orders.size() << " orders.";
}

// Uses copy constructor for use with assignment operator.
OrdersList* OrdersList::operator=(const OrdersList& o) {
	return new OrdersList(o);
}
