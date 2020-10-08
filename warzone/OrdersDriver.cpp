#include "OrdersDriver.h"
#include <iostream>


int OrdersDriver::main() {
	// Create an order list and player.
	OrdersList list1 = new OrdersList();
	Player* player1 = new Player();

	// Orders can be added to the orders list with the add method.
	Order* regOrd1 = new Order(player1);

	cout << endl << endl << *regOrd1 << endl << endl;

	cout << "Adding an order to the list." << endl;
	list1.add(regOrd1);
	cout << "List size is now " << list1.size() << "." << endl << endl;

	// Orders can be removed from the orders list with the remove method.
	cout << "Removing an order from the list." << endl;
	list1.remove(0);
	cout << "List size is now " << list1.size() << "." << endl << endl;


	DeployOrder* depOrd1 = new DeployOrder(player1);
	list1.add(depOrd1);

	cout << *depOrd1 << endl;
	
	AdvanceOrder* advOrd1 = new AdvanceOrder(player1);
	list1.add(advOrd1);

	cout << *advOrd1 << endl;

	BombOrder* bmbOrd1 = new BombOrder(player1);
	list1.add(bmbOrd1);

	cout << *bmbOrd1 << endl;

	BlockadeOrder* blkOrd1 = new BlockadeOrder(player1);
	list1.add(blkOrd1);

	cout << *blkOrd1 << endl;

	AirliftOrder* alfOrd1 = new AirliftOrder(player1);
	list1.add(alfOrd1);

	cout << *alfOrd1 << endl;

	NegotiateOrder* ngtOrd1 = new NegotiateOrder(player1);
	list1.add(ngtOrd1);

	cout << *ngtOrd1 << endl;

	list1.executeAll();

	return 0;
}

int main() {
	return OrdersDriver::main();
}

// For demonstration purposes, creates an order of each type belonging to thePlayer and adds it to theList.
void populateList(OrdersList theList, Player thePlayer) {
	/*DeployOrder* depOrd1 = new DeployOrder(thePlayer);
	theList.add(depOrd1);

	AdvanceOrder* advOrd1 = new AdvanceOrder(thePlayer);
	theList.add(advOrd1);

	BombOrder* bmbOrd1 = new BombOrder(thePlayer);
	theList.add(bmbOrd1);

	BlockadeOrder* blkOrd1 = new BlockadeOrder(thePlayer);
	theList.add(blkOrd1);

	AirliftOrder* alfOrd1 = new AirliftOrder(thePlayer);
	theList.add(alfOrd1);

	NegotiateOrder* ngtOrd1 = new NegotiateOrder(thePlayer);
	theList.add(ngtOrd1);*/
}
