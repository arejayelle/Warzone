#include "OrdersDriver.h"
#include <iostream>


int OrdersDriver::main() {
	// Create an order list and player.
	OrdersList list1 = new OrdersList();
	Player* player1 = new Player();
	Player* player2 = new Player();

	// Orders can be added to the orders list with the add method.
	Order* regOrd1 = new Order(player1);

	cout << "Adding an order to the list." << endl;
	list1.add(regOrd1);
	cout << "List size is now " << list1.size() << ".\n\n";

	list1.print();

	// New orders added to the end of the list by default.
	Order* regOrd2 = new Order(player2);

	cout << "\nAdding an order to the list." << endl;
	list1.add(regOrd2);
	cout << "List size is now " << list1.size() << ".\n\n";

	list1.print();

	// Orders can be removed from the orders list with the remove method.
	cout << "\nRemoving an order from the list." << endl;
	list1.remove(0);
	cout << "List size is now " << list1.size() << ".\n\n";

	list1.print();
	
	// Can't remove from list at an invalid index.
	cout << "\nAttempting to remove an order at an invalid index." << endl;
	list1.remove(100);
	cout << "List size is now " << list1.size() << ".\n\n";

	// Remove the last one.
	cout << "Removing an order from the list." << endl;
	list1.remove(0);
	cout << "List size is now " << list1.size() << ".\n\n";

	// OrdersList can contain orders of all types.
	cout << "Adding each type of order to the list." << endl;
	
	list1.add(regOrd2);

	DeployOrder* depOrd1 = new DeployOrder(player1);
	list1.add(depOrd1);

	AdvanceOrder* advOrd1 = new AdvanceOrder(player1);
	list1.add(advOrd1);

	BombOrder* bmbOrd1 = new BombOrder(player1);
	list1.add(bmbOrd1);

	BlockadeOrder* blkOrd1 = new BlockadeOrder(player1);
	list1.add(blkOrd1);

	AirliftOrder* alfOrd1 = new AirliftOrder(player1);
	list1.add(alfOrd1);

	NegotiateOrder* ngtOrd1 = new NegotiateOrder(player1);
	list1.add(ngtOrd1);

	cout << "List size is now " << list1.size() << ".\n\n";

	list1.print();

	// Can use the validate method to make sure an order is valid.
	Order* regOrd3 = new Order(player1);
	Order* regOrd4 = new Order();

	cout << "\nResult of validating a valid order: " << regOrd3->validate() << endl;
	cout << "Result of validating an invalid order: " << regOrd4->validate() << endl;

	// Execute method will first attempt to validate and then execute.
	cout << "\nOutput of executing a valid order:" << endl;
	regOrd3->execute();

	cout << "\nOutput of executing an invalid order:" << endl;
	regOrd4->execute();

	// The move method can be used to rearrange orders in the OrdersList.
	cout << "\nBefore applying move: ";
	list1.print();

	cout << "\nMoving the order at index 0 to index 4." << endl;
	list1.move(0, 4);
	
	cout << "\nAfter applying move: ";
	list1.print();

	// There is a method executeAll for attempting to execute each order in the list, beginning at 0 and moving to the end.
	cout << "\nExecuting all orders in the list." << endl;
	list1.executeAll();

	// Stream insertion operators for Orders and OrdersList.
	cout << "\nDemonstration of Orders stream insertion operator: " << *regOrd1 << endl;
	cout << "Demonstration of OrdersList stream insertion operator: " << list1 << endl << endl;

	return 0;
}
