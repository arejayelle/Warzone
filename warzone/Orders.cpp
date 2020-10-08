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
	if (this->player != NULL) {
		return true;
	} 
	return false;
}

bool Order::execute() {
	if(!this->validate()) {
		cout << "Cannot execute order because it is invalid.";
		return false;
	}

	cout << "Order executed.";
}

ostream& operator<<(ostream& outStream, const Order& order) {
	return outStream;
}


DeployOrder::DeployOrder(Player* player) : Order(player) { }

DeployOrder::DeployOrder(DeployOrder* other) : Order(other) { }

DeployOrder::~DeployOrder() {
	delete player;
}


AdvanceOrder::AdvanceOrder(Player* player) : Order(player) { }

AdvanceOrder::AdvanceOrder(AdvanceOrder* other) : Order(other) { }

AdvanceOrder::~AdvanceOrder() {
	delete player;
}


BombOrder::BombOrder(Player* player) : Order(player) { }

BombOrder::BombOrder(BombOrder* other) : Order(other) { }

BombOrder::~BombOrder() {
	delete player;
}


BlockadeOrder::BlockadeOrder(Player* player) : Order(player) { }

BlockadeOrder::BlockadeOrder(BlockadeOrder* other) : Order(other) { }

BlockadeOrder::~BlockadeOrder() {
	delete player;
}


AirliftOrder::AirliftOrder(Player* player) : Order(player) { }

AirliftOrder::AirliftOrder(AirliftOrder* other) : Order(other) { }

AirliftOrder::~AirliftOrder() {
	delete player;
}


NegotiateOrder::NegotiateOrder(Player* player) : Order(player) { }

NegotiateOrder::NegotiateOrder(NegotiateOrder* other) : Order(other) { }

NegotiateOrder::~NegotiateOrder() {
	delete player;
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

void OrdersList::print() {
	for (int i = 0; i < this->orders->size(); i++) {
		cout << orders->at(i) << ", ";
	}
}
