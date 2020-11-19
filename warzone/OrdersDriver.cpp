#include "OrdersDriver.h"
#include <iostream>


int OrdersDriver::main() {
	// Create continents, territories, players to test with.
	Deck* d = new Deck();
	BombCard* b = new BombCard();
	d->add(b);

	OrdersList* l1 = new OrdersList();
	OrdersList* l2 = new OrdersList();

	Continent* c = new Continent("Candy Land", "Pink", 10);

	Territory* t1 = new Territory("Lollypop Woods", c, 0, 0);
	Territory* t2 = new Territory("Gummy Hills", c, 5, 5);
	Territory* t3 = new Territory("Chocolate Mountain", c, 10, 10);
	Territory* t4 = new Territory("Licorice Lagoon", c, 15, 15);

	vector<Territory*>* p1Territories = new vector<Territory*>();
	p1Territories->push_back(t1);
	p1Territories->push_back(t2);
	vector<Territory*>* p2Territories = new vector<Territory*>();
	p2Territories->push_back(t3);
	p2Territories->push_back(t4);

	Player* p1 = new Player("Bert", p1Territories, l1, d);
	p1->addReinforcements(1000);

	Player* p2 = new Player("Ernie", p2Territories, l2, d);
	p2->addReinforcements(1000);

	// DEPLOY ORDER.

	cout << "Demonstrating invalid DeployOrder." << endl;
	cout << "Territory t1 currently has " << t1->getArmies() << " armies." << endl;
	cout << "DeployOrder with another player's territory as target:" << endl;

	DeployOrder* o1 = new DeployOrder(p1, 10, t3);
	o1->execute();

	cout << "execute() method called." << endl;
	cout << "Territory t1 now has " << t1->getArmies() << " armies." << endl;
	
	cout << "\n-----\n" << endl;

	cout << "Demonstrating valid DeployOrder." << endl;
	cout << "Territory t1 currently has " << t1->getArmies() << " armies." << endl;
	cout << "DeployOrder with player's own territory as target, deploying 10 armies:" << endl;

	DeployOrder* o2 = new DeployOrder(p1, 10, t1);
	o2->execute();

	cout << "execute() called." << endl;
	cout << "Territory t1 now has " << t1->getArmies() << " armies." << endl;

	cout << "\n-----\n" << endl;

	// ADANCE ORDER.

	cout << "Demonstrating invalid AdvanceOrder." << endl;
	cout << "Territory t2 currently has " << t2->getArmies() << " armies." << endl;
	cout << "AdvanceOrder with another player's territory as source:" << endl;

	AdvanceOrder* o3 = new AdvanceOrder(p1, 10, t3, t2);
	o3->execute();

	cout << "execute() called." << endl;
	cout << "Territory t2 now has " << t2->getArmies() << " armies." << endl;

	cout << "\n-----\n" << endl;

	cout << "Demonstrating valid AdvanceOrder with 2 territories owned by the same player." << endl;
	cout << "Territory t1 currently has " << t1->getArmies() << " armies." << endl;
	cout << "Territory t2 currently has " << t2->getArmies() << " armies." << endl;
	cout << "AdvanceOrder with source and target belonging to the same player, advancing 5 armies:" << endl;

	AdvanceOrder* o4 = new AdvanceOrder(p1, 5, t1, t2);
	o4->execute();

	cout << "execute() called." << endl;
	cout << "Territory t1 now has " << t1->getArmies() << " armies." << endl;
	cout << "Territory t2 now has " << t2->getArmies() << " armies." << endl;

	cout << "\n-----\n" << endl;

	// Make sure t3 has some armies.
	t3->addArmies(3);

	cout << "Demonstrating valid AdvanceOrder between territories owned by different players." << endl;
	cout << "Territory t1 currently has " << t1->getArmies() << " armies." << endl;
	cout << "Territory t1 currently belongs to player " << t1->getOwner()->getName() << endl;
	cout << "p1 currently has " << p1->getHand()->getNumberOfCardsInHand() << " cards in hand." << endl;
	cout << "Territory t3 currently has " << t3->getArmies() << " armies." << endl;
	cout << "Territory t3 currently belongs to player " << t3->getOwner()->getName() << endl;
	cout << "p2 currently has " << p2->getHand()->getNumberOfCardsInHand() << " cards in hand." << endl;
	cout << "AdvanceOrder with source and target belonging to different players, advancing 5 armies: " << endl;

	AdvanceOrder* o5 = new AdvanceOrder(p1, 5, t1, t3);
	o5->execute();

	cout << "execute() called." << endl;
	cout << "Territory t1 now has " << t1->getArmies() << " armies." << endl;
	cout << "Territory t1 now belongs to player " << t1->getOwner()->getName() << endl;
	cout << "p1 now has " << p1->getHand()->getNumberOfCardsInHand() << " cards in hand" << endl;
	cout << "Territory t3 now has " << t3->getArmies() << " armies." << endl;
	cout << "Territory t3 now belongs to player " << t3->getOwner()->getName() << endl;
	cout << "p2 now has " << p2->getHand()->getNumberOfCardsInHand() << " cards in hand" << endl;
	
	cout << "\n-----\n" << endl;

	// AIRLIFT ORDER.

	// Make sure t1 has some armies.
	t1->addArmies(10);

	cout << "Demonstrating invalid AirliftOrder." << endl;
	cout << "Territory t1 currently has " << t1->getArmies() << " armies." << endl;
	cout << "Territory t4 currently has " << t4->getArmies() << " armies." << endl;
	cout << "AirliftOrder with another player's territory as source, airlifting 10 armies:" << endl;

	AirliftOrder* o6 = new AirliftOrder(p1, 10, t4, t1);
	o6->execute();
	
	cout << "execute() called." << endl;
	cout << "Territory t1 now has " << t1->getArmies() << " armies." << endl;
	cout << "Territory t4 now has " << t4->getArmies() << " armies." << endl;

	cout << "\n-----\n" << endl;

	cout << "Demonstrating valid AirliftOrder." << endl;
	cout << "Territory t1 currently has " << t1->getArmies() << " armies." << endl;
	cout << "Territory t2 currently has " << t2->getArmies() << " armies." << endl;
	cout << "AirliftOrder with own player's territory as source, airlifting 10 armies:" << endl;

	AirliftOrder* o7 = new AirliftOrder(p1, 10, t1, t2);
	o7->execute();

	cout << "execute() called." << endl;
	cout << "Territory t1 now has " << t1->getArmies() << " armies." << endl;
	cout << "Territory t2 now has " << t2->getArmies() << " armies." << endl;

	cout << "\n-----\n" << endl;

	// BOMB ORDER.

	// Make sure t1 has some armies.
	t1->addArmies(10);

	cout << "Demonstrating invalid BombOrder." << endl;
	cout << "Territory t1 currently has " << t1->getArmies() << " armies." << endl;
	cout << "BombOrder with own player's territory as target:" << endl;

	BombOrder* o8 = new BombOrder(p1, t1);
	o8->execute();

	cout << "execute() called." << endl;
	cout << "Territory t1 now has " << t1->getArmies() << " armies." << endl;

	cout << "\n-----\n" << endl;

	// Make sure t4 has some armies.
	t4->addArmies(20);

	cout << "Demonstrating valid BombOrder." << endl;
	cout << "Territory t4 currently has " << t4->getArmies() << " armies." << endl;
	cout << "BombOrder with other player's territory as target:" << endl;

	BombOrder* o9 = new BombOrder(p1, t4);
	o9->execute();

	cout << "execute() called." << endl;
	cout << "Territory t4 now has " << t4->getArmies() << " armies." << endl;

	cout << "\n-----\n" << endl;

	// BLOCKADE ORDER.

	cout << "Demonstrating invalid BlockadeOrder." << endl;
	cout << "Territory t4 currently has " << t4->getArmies() << " armies." << endl;
	cout << "Territory t4 currently belongs to player " << t4->getOwner()->getName() << endl;
	cout << "BlockadeOrder with other player's territory as target:" << endl;

	BlockadeOrder* o10 = new BlockadeOrder(p1, t4);
	o10->execute();

	cout << "execute() called." << endl;
	cout << "Territory t4 now has " << t4->getArmies() << " armies." << endl;
	cout << "Territory t4 now owned by player " << t4->getOwner()->getName() << endl;

	cout << "\n-----\n" << endl;

	cout << "Demonstrating valid BlockadeOrder." << endl;
	cout << "Territory t2 currently has " << t2->getArmies() << " armies." << endl;
	cout << "Territory t2 currently belongs to player p1 " << t2->getOwner()->getName() << endl;
	cout << "BlockadeOrder with own player's territory as target:" << endl;

	BlockadeOrder* o11 = new BlockadeOrder(p1, t2);
	o11->execute();

	cout << "execute() called." << endl;
	cout << "Territory t2 now has " << t2->getArmies() << " armies." << endl;
	cout << "Territory t2 now belongs to player neutral (" << t2->getOwner() << ")" << endl;

	cout << "\n-----\n" << endl;

	// NEGOTIATE ORDER.

	cout << "Demonstrating invalid NegotiateOrder." << endl;
	cout << "NegotiateOrder with own player as target, from p1 to p1:" << endl;
	
	NegotiateOrder* o12 = new NegotiateOrder(p1, p1);
	o12->execute();

	cout << "execute() called." << endl;
	cout << "Player p1 is now in negotiation with Player p1 is " << p1->isInNegotiationWithPlayer(p1) << endl;
	
	cout << "\n-----\n" << endl;

	cout << "Demonstrating valid NegotiationOrder." << endl;
	cout << "NegotiateOrder with other player as target, from p1 to p2:" << endl;

	NegotiateOrder* o13 = new NegotiateOrder(p1, p2);
	o13->execute();

	cout << "execute() called." << endl;
	cout << "Player p1 is now in negotiation with Player p2 is " << p1->isInNegotiationWithPlayer(p2) << endl;
	cout << "Territory t1 currently has " << t1->getArmies() << " armies." << endl;
	cout << "Territory t1 currently belongs to player p1 " << t1->getOwner()->getName() << endl;
	cout << "Territory t4 currently has " << t4->getArmies() << " armies." << endl;
	cout << "Territory t4 currently belongs to player p2 " << t4->getOwner()->getName() << endl;
	cout << "AdvanceOrder with source t1 and target t2, advancing 5 armies" << endl;

	AdvanceOrder* o14 = new AdvanceOrder(p1, 5, t1, t4);
	o14->execute();

	cout << "Territory t1 now has " << t1->getArmies() << " armies." << endl;
	cout << "Territory t1 now belongs to player p1 " << t1->getOwner()->getName() << endl;
	cout << "Territory t4 now has " << t4->getArmies() << " armies." << endl;
	cout << "Territory t4 now belongs to player p2 " << t4->getOwner()->getName() << endl;

	return 0;
}
