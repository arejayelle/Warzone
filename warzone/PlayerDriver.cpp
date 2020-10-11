#include "PlayerDriver.h"
#include "Orders.h"


int PlayerDriver::main() {
	Player* p1 = new Player();

	cout << "Player can defend: " << endl;  //returns territories the player can defend
	cout<<p1->toDefend()<< endl; //prints memory address of territory

	cout << "Player can attack: " << endl; //returns territories the player can attack
	cout<<p1->toAttack() << endl;

	cout << "Player has following orders: " << endl;  //returns the player's order list
	p1->getOrdersList()->print();

	cout << "Player deployed following order: ";
	Order* playerOrder = new Order();
	cout << playerOrder->toString()<<endl;
	p1->issueOrder(playerOrder);  //issuing an order

	p1->getOrdersList()->print();

	cout << &p1 << endl;  //output opperator 

	return 0;
}