#include "Orders.h"
#include <iostream>
#include <string>
#include <sstream>


Order::Order() {
	this->player = nullptr;
}

Order::Order(Player* player) {
	this->player = player;
}

Order::Order(Order* other) {
	this->player = other->player;
}

Order::~Order() { }

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

string Order::toString() const {
	ostringstream strm;
	strm << "Order made by player " << this->player;
	return strm.str();
}

ostream& operator<<(ostream &strm, const Order &o) {
	return strm << o.toString();
}

Order* Order::operator=(const Order &o) {
	return new Order(o);
}


DeployOrder::DeployOrder(Player* player) : Order(player) { }

DeployOrder::DeployOrder(DeployOrder* other) : Order(other) { }

DeployOrder::~DeployOrder() { }

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

string DeployOrder::toString() const {
	ostringstream strm;
	strm << "Deploy order made by player " << this->player;
	return strm.str();
}

ostream& operator<<(ostream& strm, const DeployOrder& o) {
	return strm << o.toString();
}

DeployOrder* DeployOrder::operator=(const DeployOrder& o) {
	return new DeployOrder(o);
}


AdvanceOrder::AdvanceOrder(Player* player) : Order(player) { }

AdvanceOrder::AdvanceOrder(AdvanceOrder* other) : Order(other) { }

AdvanceOrder::~AdvanceOrder() { }

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

string AdvanceOrder::toString() const {
	ostringstream strm;
	strm << "Advance order made by player " << this->player;
	return strm.str();
}

ostream& operator<<(ostream& strm, const AdvanceOrder& o) {
	return strm << o.toString();
}

AdvanceOrder* AdvanceOrder::operator=(const AdvanceOrder& o) {
	return new AdvanceOrder(o);
}


BombOrder::BombOrder(Player* player) : Order(player) { }

BombOrder::BombOrder(BombOrder* other) : Order(other) { }

BombOrder::~BombOrder() { }

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

string BombOrder::toString() const {
	ostringstream strm;
	strm << "Bomb order made by player " << this->player;
	return strm.str();
}

ostream& operator<<(ostream& strm, const BombOrder& o) {
	return strm << o.toString();
}

BombOrder* BombOrder::operator=(const BombOrder& o) {
	return new BombOrder(o);
}


BlockadeOrder::BlockadeOrder(Player* player) : Order(player) { }

BlockadeOrder::BlockadeOrder(BlockadeOrder* other) : Order(other) { }

BlockadeOrder::~BlockadeOrder() { }

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

string BlockadeOrder::toString() const {
	ostringstream strm;
	strm << "Blockade order made by player " << this->player;
	return strm.str();
}

ostream& operator<<(ostream& strm, const BlockadeOrder& o) {
	return strm << o.toString();
}

BlockadeOrder* BlockadeOrder::operator=(const BlockadeOrder& o) {
	return new BlockadeOrder(o);
}


AirliftOrder::AirliftOrder(Player* player) : Order(player) { }

AirliftOrder::AirliftOrder(AirliftOrder* other) : Order(other) { }

AirliftOrder::~AirliftOrder() { }

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

string AirliftOrder::toString() const {
	ostringstream strm;
	strm << "Airlift order made by player " << this->player;
	return strm.str();
}

ostream& operator<<(ostream& strm, const AirliftOrder& o) {
	return strm << o.toString();
}

AirliftOrder* AirliftOrder::operator=(const AirliftOrder& o) {
	return new AirliftOrder(o);
}


NegotiateOrder::NegotiateOrder(Player* player) : Order(player) { }

NegotiateOrder::NegotiateOrder(NegotiateOrder* other) : Order(other) { }

NegotiateOrder::~NegotiateOrder() { }

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

string NegotiateOrder::toString() const {
	ostringstream strm;
	strm << "Negotiate order made by player " << this->player;
	return strm.str();
}

ostream& operator<<(ostream& strm, const NegotiateOrder& o) {
	return strm << o.toString();
}

NegotiateOrder* NegotiateOrder::operator=(const NegotiateOrder& o) {
	return new NegotiateOrder(o);
}


OrdersList::OrdersList() {
	this->orders = vector<Order*>();
}

OrdersList::OrdersList(OrdersList* other) {
	vector<Order*> newOrders = vector<Order*>();
	for (int i = 0; i < other->orders.size(); i++) {
		newOrders.push_back(new Order(other->orders.at(i)));
	}
	this->orders = newOrders;
}

OrdersList::~OrdersList() {
	// Delete each pointer in orders.
	for (int i = 0; i < orders.size(); i++) {
		delete orders.at(i);
	}
}

int OrdersList::size() {
	return this->orders.size();
}

// The new order is added to the back of the list.
void OrdersList::add(Order* newOrder) {
	this->orders.push_back(newOrder);
}

// Deletes the order at the specified index. Indexes begin at 0.
bool OrdersList::remove(int index) {
	if (index > this->orders.size() - 1 || index < 0) {
		cout << "Can't delete this order. Invalid index." << endl;
		return false;
	}

	this->orders.erase(this->orders.begin() + index);
	return true;
}

// Allows the player to rearrange orders by removing an order at oldIndex and inserting it at newIndex.
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

// Prints all orders for debugging purposes.
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

	for (int i = 0; i < this->orders.size(); i++) {
		if (!this->orders.at(i)->execute()) {
			allExecuted = false;
		}
	}

	return allExecuted;
}

ostream& operator<<(ostream& strm, const OrdersList& o) {
	return strm << "OrdersList containing " << o.orders.size() << " orders.";
}

OrdersList* OrdersList::operator=(const OrdersList& o) {
	return new OrdersList(o);
}
