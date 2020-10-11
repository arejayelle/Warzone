#include "Player.h"

Player::Player() {  //default constructor
	this->playerTerritories = new vector<Territory*>();
	this->playerHand = new Cards::Hand();
	this->playerOrdersList = new OrdersList();
}


Player::Player(vector<Territory*>* territoriesToAdd, OrdersList* playerList, Cards::Deck* deckToTakeFrom) { //Constructor with all parameters
	this->playerTerritories = territoriesToAdd;
	this->playerOrdersList = playerList;
	this->playerHand = new Cards::Hand(deckToTakeFrom);
}

Player::~Player() {  //destructor 
	delete playerTerritories;
	delete playerHand;
	delete playerOrdersList;
}

Player& Player::operator=(const Player& one)  //assignment operator
{
	delete playerHand;
	this->playerHand = one.playerHand;
	delete playerTerritories;
	this->playerTerritories = one.playerTerritories;
	delete playerOrdersList;
	this->playerOrdersList = one.playerOrdersList;
	return *this;
}

Player::Player(const Player& player)  //copy constructor
{
	for (Territory* t : *player.playerTerritories)
	{
		Territory temp = new Territory(t);
		this->playerTerritories->push_back(t);    //copies each territory in the incoming player's territories 
	}
	this->playerOrdersList = new OrdersList(*player.playerOrdersList);
	this->playerHand = new Cards::Hand(*player.playerHand);
}

const vector<Territory*>* Player::toDefend()   //returns territories the player can defend
{
	vector<Territory*>* toDefend = new vector<Territory*>();
	if (toDefend->empty())
		cout << "Player has nothing to defend" << endl; //checks if the player has no territories to defend. if so, print that they have none
	return toDefend;
}

const vector<Territory*>* Player::toAttack()   //returns territories the player can attack
{
	vector<Territory*>* toAttack = new vector<Territory*>();
	if (toAttack->empty())
		cout << "Player has nothing to attack" << endl; //checks if the player has no territories to attack. if so, print that they have none
	return toAttack;
}

void Player::issueOrder(Order* newOrder)  //allows player to issue an order
{
	Order* playerOrder = new Order(*newOrder);
	playerOrdersList->add(playerOrder);
}

const vector<Territory*>* Player::getTerritories()  //returns all the player's territories 
{
	if (playerTerritories->empty())
		cout << "Player has no territories" << endl;  //checks if the player's territories are empty. if so, print that they have none
	return playerTerritories;
}

const OrdersList* Player::getOrdersList()   //returns the player's order list
{
	if (playerOrdersList->size() == 0)
		cout << "Player's Order List is Empty" << endl; //checks if the player's order list is empty. if so, print that they have none
	return playerOrdersList;
}

const Cards::Hand* Player::getHand()  //returns the cards in the player's hand
{
	return playerHand;
}

void const Player::setTerritories(vector<Territory*>* territoriesToAdd) //sets all the player's territories 
{
	this->playerTerritories = territoriesToAdd;
}

void Player::setOrdersList(OrdersList* ordersList) //sets the player's order list
{
	this->playerOrdersList = ordersList;
}

void Player::setHand(Cards::Hand* handToAdd)  //sets the cards in the player's hand
{
	this->playerHand = handToAdd;
}

ostream& operator<<(ostream& output, const Player& player)  //output stream
{
	output << "Player Information:" << endl;
	output << "Hand: " << player.playerHand << endl;
	output << "Territories: " << player.playerTerritories<< endl;
	output << "Orders list: " << player.playerOrdersList << endl;
	return output;
}