#include "Orders.h"

// Order class.
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
	// TODO: insert return statement here
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

void OrdersList::add(Order* order) {

}

void OrdersList::remove(int index) {

}

void OrdersList::move(Order* order, int newIndex) {

}
