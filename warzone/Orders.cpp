#include "Orders.h"
#include <sstream>
#include <ctime>

using namespace std;


// Generic order abstract class.
// Default constructor.
Order::Order() {
	this->player = nullptr;
}

// Parameterized constructor.
Order::Order(Player* player) {
	this->player = player;
}

// Copy constructor.
Order::Order(Order* other) {
	this->player = other->player;
}

// Destructor.
Order::~Order() { }

// Ensure there are no issues with the creation of the order.
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

// To get the priority of an order according to the instructions.
int Order::getPriority() {
	throw "Cannot determine the priority of an order in base Order class";
}

// Stream insertion operator, uses toString method to display order information.
ostream& operator<<(ostream &strm, const Order &o) {
	return strm << o.toString();
}

// Assignment operator which uses the class' copy constructor.
Order& Order::operator=(const Order &o) {
	player = o.player;
	return *this;
}


// Deploy order subclass.
// Parameterized constructor.
DeployOrder::DeployOrder(Player* player, int numArmies, Territory* target) : Order(player) , numArmies(numArmies), target(target) { }

// Copy constructor.
DeployOrder::DeployOrder(DeployOrder* other) : Order(other), numArmies(other->numArmies), target(other->target) { }

// Destructor.
DeployOrder::~DeployOrder() { }

// Check validity of creator, number of armies deployed, and that the target territory belongs to the player.
bool DeployOrder::validate() {
	return(
		(this->player != nullptr) &&
		(this->numArmies > 0) &&
		(this->player == this->target->getOwner())
		);
}

// Validate order and then add the armies to the territory.
bool DeployOrder::execute() {
	if (!this->validate()) {
		return false;
	}

	// Add the armies to the territory.
	this->target->addArmies(this->numArmies);
	return true;
}

// Used to print information about the order.
string DeployOrder::toString() const {
	// TODO make nicer (all classes)
	ostringstream strm;
	strm << "Deploy order made by player " << this->player << " deploying " << this->numArmies << " troops to " << this->target->getName();
	return strm.str();
}

int DeployOrder::getPriority() {
	// Deploy order has highest priority
	return 3;
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

StatsObservable* AdvanceOrder::statsObservable = new StatsObservable();

// Advance order subclass.
// Parameterized constructor.
AdvanceOrder::AdvanceOrder(Player* player, int numArmies, Territory* source, Territory* target) : 
	Order(player), numArmies(numArmies), source(source), target(target) { }

// Copy constructor.
AdvanceOrder::AdvanceOrder(AdvanceOrder* other) : Order(other), numArmies(other->numArmies), source(other->source), target(other->target) { }

// Destructor.
AdvanceOrder::~AdvanceOrder() { }

// Verify that player is valid, that no one is blocked by negotiations, that the source belongs to the player who created the order, 
// and that source contains enough armies.
bool AdvanceOrder::validate() {
	return(
		(this->player != nullptr) &&
		(this->numArmies <= this->source->getArmies()) &&
		(this->player == this->source->getOwner()) &&
		!(this->player->isInNegotiationWithPlayer(this->target->getOwner())) // Makes order invalid if the source and target owners are in negotiation with each other.
		);
}

// Validate order and then perform operations depending on the owner of the source and target.
bool AdvanceOrder::execute() {
	if (!this->validate()) {
		return false;
	}

	// Actions for when the source and target territories belong to the same player. Move them from one territory to the other.
	if (this->source->getOwner() == this->target->getOwner()) {
		this->source->removeArmies(numArmies);
		this->target->addArmies(numArmies);
	}
	// Execute battle simulation sequence if the territories belong to different players.
	else {
		this->battle();
	}

	return true;
}

// Decides which armies kill each other and, depending on the outcome, add card to attacker's hand.
void AdvanceOrder::battle() {
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
		statsObservable->notify("Territory " + target->getName() + " was taken from " + target->getOwner()->getName() + " by " + source->getOwner()->getName());

		// Place remaining armies on the new territory.
		this->source->removeArmies(numArmies);
		this->target->addArmies(numArmies);

		// Remove territory from losing player's vector of territories and transfer ownership of territory to the winning player.
		this->target->getOwner()->removeTerritory(this->target);
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
	strm << "Advance order made by player " << this->player << " sending " << this->numArmies << " troops from " << this->source->getName() << " to " << this->target->getName();
	return strm.str();
}

int AdvanceOrder::getPriority() {
	// AdvanceOrder has no particular priority
	return 0;
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
// Parameterized constructor.
BombOrder::BombOrder(Player* player, Territory* target) : Order(player), target(target) { }

// Copy constructor taking a pointer to another BombOrder object.
BombOrder::BombOrder(BombOrder* other) : Order(other), target(other->target) { }

// Destructor.
BombOrder::~BombOrder() { }

// Makes sure the creator is valid and that the creator doesn't bomb themselves.
bool BombOrder::validate() {
	return(
		(this->player != nullptr) &&
		(this->target->getOwner() != this->player)
		);
}

// Validate and remove half the armies from the territory if valid.
bool BombOrder::execute() {
	if (!this->validate()) {
		return false;
	}

	// Remove half the armies in the target territory.
	this->target->removeArmies(this->target->getArmies() / 2);
	return true;
}

// Used to print information about the order.
string BombOrder::toString() const {
	ostringstream strm;
	strm << "Bomb order made by player " << this->player << " targeting " << this->target->getName();
	return strm.str();
}

int BombOrder::getPriority() {
	// BombOrder has no particular priority
	return 0;
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
// Parameterized constructor.
BlockadeOrder::BlockadeOrder(Player* player, Territory* target) : Order(player), target(target) { }

// Copy constructor.
BlockadeOrder::BlockadeOrder(BlockadeOrder* other) : Order(other), target(other->target) { }

// Destructor.
BlockadeOrder::~BlockadeOrder() { }

// Make sure creator is valid and that blockade can only apply to own territory.
bool BlockadeOrder::validate() {
	return(
		(this->player != nullptr) &&
		(this->target->getOwner() == this->player)
		);
}

// Validate and execute order.
bool BlockadeOrder::execute() {
	if (!this->validate()) {
		return false;
	}

	// Double the number of armies on the territory and transfer ownership to neutral player.
	this->target->addArmies(this->target->getArmies());
	this->target->setOwner(nullptr);
	return true;
}

// Used to print information about the order.
string BlockadeOrder::toString() const {
	ostringstream strm;
	strm << "Blockade order made by player " << this->player << " targeting territory " << this->target->getName();
	return strm.str();
}

int BlockadeOrder::getPriority() {
	// BlockadeOrder has less priority than DeployOrder or AirliftOrder, but more priority than other orders.
	return 1;
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
// Parameterized constructor.
AirliftOrder::AirliftOrder(Player* player, int numArmies, Territory* source, Territory* target) : 
	Order(player), numArmies(numArmies), source(source), target(target) { }

// Copy constructor.
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
	if (!this->validate()) {
		return false;
	}

	// Move armies from source to target.
	this->source->removeArmies(numArmies);
	this->target->addArmies(numArmies);
	return true;
}

// Used to print information about the order.
string AirliftOrder::toString() const {
	ostringstream strm;
	strm << "Airlift order made by player " << this->player << " moving " << this->numArmies << " from " << this->source->getName() << " to " << this->target->getName();
	return strm.str();
}

int AirliftOrder::getPriority() {
	// AirliftOrder has less priority than DeployOrder, but higher priority than BlockadeOrder and other orders
	return 1;
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
// Parameterized constructor.
NegotiateOrder::NegotiateOrder(Player* player, Player* targeted) : Order(player), targeted(targeted) { }

// Copy constructor taking a pointer to another NegotiateOrder object.
NegotiateOrder::NegotiateOrder(NegotiateOrder* other) : Order(other), targeted(other->targeted) { }

// Destructor.
NegotiateOrder::~NegotiateOrder() { }

// Ensure the creator is valid and does not target themselves.
bool NegotiateOrder::validate() {
	return(
		(this->player != nullptr) &&
		(this->player != this->targeted)
		);
}

// Validates order and then adds the targeted player to list of players negotiating with.
bool NegotiateOrder::execute() {
	if (!this->validate()) {
		return false;
	}

	// Executing a NegotiateOrder involves adding these players to each others' inNegotiationWith vectors.
	this->player->addPlayerInNegotiationWith(this->targeted);
	this->targeted->addPlayerInNegotiationWith(this->player);

	return true;
}

// Used to print information about the order.
string NegotiateOrder::toString() const {
	ostringstream strm;
	strm << "Negotiate order made by player " << this->player;
	return strm.str();
}

int NegotiateOrder::getPriority() {
	// NegotiateOrder has no particular priority
	return 0;
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

// Comparison function for orders required for making the orders list a priority queue
bool compareOrders(Order* order1, Order* order2) {
	return order1->getPriority() < order2->getPriority();
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
	// make_heap organizes the element in the vector to respect the heap property (highest priority first)
	make_heap(newOrders.begin(), newOrders.end(), compareOrders);
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
	// push_heap assumes we have just pushed an element to the end of the vector, and will rearrange the vector to insert
	// the new element at the right spot based on the compare function.
	push_heap(orders.begin(), orders.end(), compareOrders);
}

Order* OrdersList::peek()
{
	if (orders.empty()) {
		throw "Cannot peek at an empty OrdersList";
	}
	return orders.at(0);
}

Order* OrdersList::pop()
{
	// pop_heap will move the highest priority element in the orders list to the last position in the vector so that we can remove it
	pop_heap(orders.begin(), orders.end(), compareOrders);

	// pop_back removes the last element but doesn't actually return it which is why we have to call vector::back first
	Order* order = orders.back();
	orders.pop_back();
	return order;
}

// Deletes the order at the specified index. Indexes begin at 0. Returns true if successfully removed, false otherwise.
Order* OrdersList::remove(int index) {
	// Verifies that the specified index is within range.
	if (index > this->orders.size() - 1 || index < 0) {
		cout << "Can't delete this order. Invalid index." << endl;
		throw "Index out of bounds for removing order";
	}

	Order* order = this->orders.at(index);
	this->orders.erase(this->orders.begin() + index);
	// rearrange the vector so it is in priority order after the remove happened
	make_heap(orders.begin(), orders.end(), compareOrders);
	return order;
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
	// rearrange the vector so it is still ordered by priority
	make_heap(orders.begin(), orders.end(), compareOrders);
	return true;
}

// Prints all information about orders in the orders list for debugging/demonstration purposes.
void OrdersList::print() {
	cout << "List contents are:\n[";
	for (int i = 0; i < this->orders.size(); i++) {
		cout << *(this->orders.at(i)) << ", " << endl;
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
