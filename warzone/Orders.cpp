#include "Orders.h"
#include <sstream>
#include <ctime>

using namespace std;

// TODO comments everywhere

// Generic order abstract class.
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
	if (this->player != NULL) {
		return true;
	} 
	return false;
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
Order& Order::operator=(const Order &o) {
	// TODO why is the new way better? (all classes)
	// return new Order(o);
	player = o.player;
	return *this;
}


// Deploy order subclass.
// Constructor which takes a pointer to a Player object.
DeployOrder::DeployOrder(Player* player, int numArmies, Territory* target) : Order(player) , numArmies(numArmies), target(target) { }

// Copy constructor taking a pointer to another DeployOrder object.
DeployOrder::DeployOrder(DeployOrder* other) : Order(other), numArmies(other->numArmies), target(other->target) { }

// Destructor.
DeployOrder::~DeployOrder() { }

// This verifies that there are no problems with the order. Returns true if valid, false otherwise.
bool DeployOrder::validate() {
	// Check validity of player, number of armies deployed, and that the target territory belongs to the player.
	return(
		(this->player != nullptr) &&
		(this->numArmies <= this->player->getReinforcements()) &&
		(this->player == this->target->getOwner())
		);
}

// First uses the validate method and then executes the order and displays the status.
bool DeployOrder::execute() {
	cout << "Attempting to execute deploy order... ";

	if (!this->validate()) {
		cout << "Cannot execute deploy order because it is invalid." << endl;
		return false;
	}

	// Add the armies to the territory.
	this->target->addArmies(this->numArmies);
	cout << "Deploy order executed." << endl;
	return true;
}

// Used to print information about the order.
string DeployOrder::toString() const {
	// TODO make nicer (all classes)
	ostringstream strm;
	strm << "Deploy order made by player " << this->player;
	return strm.str();
}

// Stream insertion operator, uses toString method to display order information.
ostream& operator<<(ostream& strm, const DeployOrder& o) {
	return strm << o.toString();
}

// Assignment operator which uses the class' copy constructor.
DeployOrder& DeployOrder::operator=(const DeployOrder& o) {
	Order::operator=(o);
	return *this;
}


// Advance order subclass.
// Constructor which takes a pointer to a Player object.
AdvanceOrder::AdvanceOrder(Player* player, int numArmies, Territory* source, Territory* target) : 
	Order(player), numArmies(numArmies), source(source), target(target) { }

// Copy constructor taking a pointer to another AdvanceOrder object.
AdvanceOrder::AdvanceOrder(AdvanceOrder* other) : Order(other), numArmies(other->numArmies), source(other->source), target(other->target) { }

// Destructor.
AdvanceOrder::~AdvanceOrder() { }

// This verifies that there are no problems with the order. Returns true if valid, false otherwise.
bool AdvanceOrder::validate() {
	// Verify that player is valid, that the source belongs to the player who created the order, and that source contains enough armies.
	return(
		(this->player != nullptr) &&
		(this->numArmies <= this->source->getArmies()) &&
		(this->player == this->source->getOwner())
		);
}

// First uses the validate method and then executes the order and displays the status.
bool AdvanceOrder::execute() {
	cout << "Attempting to execute advance order... ";

	if (!this->validate()) {
		cout << "Cannot execute advance order because it is invalid." << endl;
		return false;
	}

	// Actions for when the source and target territories belong to the same player.
	if (this->source->getOwner() == this->target->getOwner()) {
		this->source->removeArmies(numArmies);
		this->target->addArmies(numArmies);
	}
	// Execute battle simulation sequence.
	else {
		this->battle();
	}

	cout << "Advance order executed." << endl;
	return true;
}

void AdvanceOrder::battle() {
	// Seed the random number generator.
	// TODO Probably better if this occurs once at the top of main().
	srand(time(0));

	while (this->source->getArmies() > 0 && this->target->getArmies() > 0) {
		// Attacker has 60% chance of killing defender.
		if ((1 + rand() % 100) < 60) { 
			this->target->removeArmies(1); 
		}
		// Defender has 70% chance of killing attacker.
		if ((1 + rand() % 100) < 70) {
			this->source->removeArmies(1);
		}
	}

	// When attacker wins, the survivors occupy the territory.
	if (this->source->getArmies() > this->target->getArmies()) {
		int numArmies = this->source->getArmies();

		// Place remaining armies on the new territory.
		this->source->removeArmies(numArmies);
		this->target->addArmies(numArmies);

		// Transfer ownership of territory to the winning player.
		this->target->setOwner(this->source->getOwner());

		// Add the new territory to the player's list of territories.
		this->player->addTerritory(this->target);

		// Take the card on the top of the deck and add it to the player's hand.
		this->player->getHand()->drawCardFromDeck();
	}
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
AdvanceOrder& AdvanceOrder::operator=(const AdvanceOrder& o) {
	player = o.player;
	return *this;
}


// BombOrder subclass.
// Constructor which takes a pointer to a Player object.
BombOrder::BombOrder(Player* player, Territory* target) : Order(player), target(target) { }

// Copy constructor taking a pointer to another BombOrder object.
BombOrder::BombOrder(BombOrder* other) : Order(other), target(other->target) { }

// Destructor.
BombOrder::~BombOrder() { }

// This verifies that there are no problems with the order. Returns true if valid, false otherwise.
bool BombOrder::validate() {
	return(
		(this->player != nullptr) &&
		(this->target->getOwner() != this->player)
		);
}

// First uses the validate method and then executes the order and displays the status.
bool BombOrder::execute() {
	cout << "Attempting to execute bomb order... ";

	if (!this->validate()) {
		cout << "Cannot execute bomb order because it is invalid." << endl;
		return false;
	}

	// Remove half the armies in the target territory.
	this->target->removeArmies(this->target->getArmies() / 2);
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
BombOrder& BombOrder::operator=(const BombOrder& o) {
	player = o.player;
	return *this;
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
BlockadeOrder& BlockadeOrder::operator=(const BlockadeOrder& o) {
	player = o.player;
	return *this;
}


// Airlift order subclass.
// Constructor which takes a pointer to a Player object.
AirliftOrder::AirliftOrder(Player* player, int numArmies, Territory* source, Territory* target) : 
	Order(player), numArmies(numArmies), source(source), target(target) { }

// Copy constructor taking a pointer to another AirliftOrder object.
AirliftOrder::AirliftOrder(AirliftOrder* other) : Order(other), numArmies(other->numArmies), source(other->source), target(other->source) { }

// Destructor.
AirliftOrder::~AirliftOrder() { }

// Verify that the source and target belong to the player who created the order and that player and number of armies is valid.
bool AirliftOrder::validate() {
	return(
		(this->player != nullptr) &&
		(this->numArmies <= this->source->getArmies()) &&
		(this->player == this->source->getOwner()) &&
		(this->player == this->target->getOwner())
		);
}

// First uses the validate method and then executes the order and displays the status.
// Actions take place according to the Warzone rules; that is, the source and target belong to the player.
bool AirliftOrder::execute() {
	cout << "Attempting to execute airlift order... ";

	if (!this->validate()) {
		cout << "Cannot execute airlift order because it is invalid." << endl;
		return false;
	}

	this->source->removeArmies(numArmies);
	this->target->addArmies(numArmies);

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
AirliftOrder& AirliftOrder::operator=(const AirliftOrder& o) {
	player = o.player;
	return *this;
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
NegotiateOrder& NegotiateOrder::operator=(const NegotiateOrder& o) {
	player = o.player;
	return *this;
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
		// TODO
		// newOrders.push_back(new Order(other->orders.at(i)));
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
	return (int) this->orders.size();
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
