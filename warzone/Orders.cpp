#include "Orders.h"
#include <iostream>

Order::Order() {
	this->player = NULL;
}

Order::Order(Player* player) {
	this->player = player;
}

Order::Order(Order* other) {
	this->player = other->player;
}

Order::~Order() {
	delete player;
}

bool Order::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	} 
	return false;
}

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

ostream& operator<<(ostream &strm, const Order &o) {
	return strm << "Order made by " << o.*player;
	// TODO: insert return statement here
}


DeployOrder::DeployOrder(Player* player) : Order(player) { }

DeployOrder::DeployOrder(DeployOrder* other) : Order(other) { }

DeployOrder::~DeployOrder() {
	delete player;
}

bool DeployOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

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


AdvanceOrder::AdvanceOrder(Player* player) : Order(player) { }

AdvanceOrder::AdvanceOrder(AdvanceOrder* other) : Order(other) { }

AdvanceOrder::~AdvanceOrder() {
	delete player;
}

bool AdvanceOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

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


BombOrder::BombOrder(Player* player) : Order(player) { }

BombOrder::BombOrder(BombOrder* other) : Order(other) { }

BombOrder::~BombOrder() {
	delete player;
}

bool BombOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

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


BlockadeOrder::BlockadeOrder(Player* player) : Order(player) { }

BlockadeOrder::BlockadeOrder(BlockadeOrder* other) : Order(other) { }

BlockadeOrder::~BlockadeOrder() {
	delete player;
}

bool BlockadeOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

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


AirliftOrder::AirliftOrder(Player* player) : Order(player) { }

AirliftOrder::AirliftOrder(AirliftOrder* other) : Order(other) { }

AirliftOrder::~AirliftOrder() {
	delete player;
}

bool AirliftOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

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


NegotiateOrder::NegotiateOrder(Player* player) : Order(player) { }

NegotiateOrder::NegotiateOrder(NegotiateOrder* other) : Order(other) { }

NegotiateOrder::~NegotiateOrder() {
	delete player;
}

bool NegotiateOrder::validate() {
	// TODO: More checks once we have more details.
	if (this->player != NULL) {
		return true;
	}
	return false;
}

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


OrdersList::OrdersList() {
	this->orders = new vector<Order*>();
}

OrdersList::OrdersList(OrdersList* other) {
	this->orders = other->orders;
}

OrdersList::~OrdersList() {
	orders->clear();
	delete orders;
}

int OrdersList::size() {
	return this->orders->size();
}

// The new order is added to the back of the list.
void OrdersList::add(Order* newOrder) {
	this->orders->push_back(newOrder);
}

// Deletes the order at the specified index. Indexes begin at 0.
bool OrdersList::remove(int index) {
	if (index > this->orders->size() - 1 || index < 0) {
		cout << "Can't delete this order. Invalid index." << endl;
		return false;
	}

	this->orders->erase(this->orders->begin() + index);
	return true;
}

// Allows the player to rearrange orders by removing an order at oldIndex and inserting it at newIndex.
bool OrdersList::move(int oldIndex, int newIndex) {
	// Check if the indices make sense.
	if (oldIndex > this->orders->size() - 1 || oldIndex < 0) {
		cout << "Can't move. Invalid starting index." << endl;
		return false;
	}
	else if (newIndex > this->orders->size() - 1 || newIndex < 0) {
		cout << "Can't move. Invalid destination index." << endl;
		return false;
	}

	// Get and remove the item at oldIndex.
	Order* theOrder = this->orders->at(oldIndex);
	this->remove(oldIndex);

	// The last index may have changed after removal, if invalid just add it to the back of the list.
	if (newIndex > this->orders->size() - 1) {
		this->orders->push_back(theOrder);
		return true;
	}

	// Regular case, just insert it at the index.
	this->orders->insert(this->orders->begin() + newIndex, theOrder);
	return true;
}

// Prints all orders for debugging purposes.
void OrdersList::print() {
	for (int i = 0; i < this->orders->size(); i++) {
		auto ord = orders->at(i);
		cout << ord << ", ";
	}
}

// Attempts to execute all orders in the list. Returns true if successful, returns false if at least one could not be executed.
bool OrdersList::executeAll() {
	bool allExecuted = true;

	for (int i = 0; i < this->orders->size(); i++) {
		if (!this->orders->at(i)->execute()) {
			allExecuted = false;
		}
	}

	return allExecuted;
}
