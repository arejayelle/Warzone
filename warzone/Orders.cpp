#include "Orders.h"


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
	cout << "Attempting to execute order...";

	if(!this->validate()) {
		cout << "Cannot execute order because it is invalid." << endl;
		return false;
	}

	// TODO: Do actions once we have more details.
	cout << "Order executed." << endl;
	return true;
}

ostream& operator<<(ostream& outStream, const Order& order) {
	return outStream;
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
	cout << "Attempting to execute deploy order...";

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
	cout << "Attempting to execute advance order...";

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
	cout << "Attempting to execute bomb order...";

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
	cout << "Attempting to execute blockade order...";

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
	cout << "Attempting to execute airlift order...";

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
	cout << "Attempting to execute negotiate order...";

	if (!this->validate()) {
		cout << "Cannot execute negotiate order because it is invalid." << endl;
		return false;
	}

	// TODO: Do actions once we have more details.
	cout << "Negotiate order executed." << endl;
	return true;
}


OrdersList::OrdersList(Player* player) {
	this->player = player;
	this->orders = {};
}

OrdersList::OrdersList(OrdersList* other) {
	this->player = other->player;
	this->orders = other->orders;
}

OrdersList::~OrdersList() {
	delete player;
	orders->clear();
	delete orders;
}

// The new order is added to the back of the list.
void OrdersList::add(Order* newOrder) {
	this->orders->push_back(newOrder);
}

// Deletes the order at the specified index. Indexes begin at 0.
void OrdersList::remove(int index) {
	if (index > this->orders->size() - 1 || index < 0) {
		cout << "Can't delete this order. Invalid index." << endl;
		return;
	}

	this->orders->erase(this->orders->begin() + index);
}

// Allows the player to rearrange orders by removing an order at oldIndex and inserting it at newIndex.
void OrdersList::move(int oldIndex, int newIndex) {
	if (oldIndex > this->orders->size() - 1 || oldIndex < 0) {
		cout << "Can't move. Invalid starting index." << endl;
		return;
	}
	else if (newIndex > this->orders->size() - 1 || newIndex < 0) {
		cout << "Can't move. Invalid destination index." << endl;
		return;
	}
	
	Order theOrder = this->orders->at(oldIndex);
	this->remove(oldIndex);
	this->orders->insert(this->orders->begin() + newIndex, theOrder);
}

// Prints all orders for debugging purposes.
void OrdersList::print() {
	for (int i = 0; i < this->orders->size(); i++) {
		cout << orders->at(i) << ", ";
	}
}
