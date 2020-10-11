#include "PlayerDriver.h"
#include "Orders.h"


int PlayerDriver::main() {
	Player* p1 = new Player();

	cout << "Player can defend: " << endl;  //returns territories the player can defend
	p1->toDefend();

	cout << "Player can attack: " << endl; //returns territories the player can attack
	p1->toAttack();

	cout << "Player has following orders: " << endl;  //returns the player's order list
	p1->getOrdersList(); 

	cout << "Player deployed following order: " << endl;
	Order* playerOrder = new Order();
	p1->issueOrder(playerOrder);  //issuing an order

	cout << p1;  //output opperator 

	return 0;
}